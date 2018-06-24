# include "AreaTrigger.hpp"

AreaTrigger::AreaTrigger() : Node(), orientation(Orientation::Null)
{

}

AreaTrigger::~AreaTrigger()
{

}

void AreaTrigger::setRect(Vec2 const & pos, float width, float height)
{
    Rect rect(0, 0, width, height);
    
    rectArea = RectApplyAffineTransform(rect, getNodeToParentAffineTransform());

    scheduleUpdate();
}

void AreaTrigger::setOnObjectEnter(std::function<void(Node*& /**/)> const & func)
{
    onObjectEnter = func;
}

void AreaTrigger::setOnObjectExit(std::function<void(Node*& /**/)> const & func)
{
    onObjectExit = func;
}

void AreaTrigger::setOnCheckObject(std::function<void(Node*& /**/, bool &)> const & func)
{
    onCheckObject = func;
}

void AreaTrigger::update(float dt)
{
    Node::update(dt);

    Node* layer = getParent();

    if (layer == nullptr || layer->getTag() != SpriteTags::LAYER)
        return;

    for (Node*& child : layer->getChildren())
    {
        bool inside = isInside(child);

        if (onCheckObject != nullptr)
            onCheckObject(child, inside);

        if (inside)
        {
            if (insideObjects.find(child) == insideObjects.end())
            {
                if (onObjectEnter != nullptr)
                    onObjectEnter(child);

                insideObjects.insert(child);
            }
        }
        else if (insideObjects.find(child) != insideObjects.end())
        {
            insideObjects.erase(child);
            
            if (onObjectExit != nullptr)
                onObjectExit(child);
        }
    }
}