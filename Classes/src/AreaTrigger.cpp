# include "AreaTrigger.hpp"

AreaTrigger::AreaTrigger() : Node()
{

}

AreaTrigger::~AreaTrigger()
{

}

void AreaTrigger::setRect(Vec2 const & pos, float width, float height)
{
    rectArea = Rect(pos.x, pos.y, width, height);

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

void AreaTrigger::update(float dt)
{
    Node::update(dt);

    Node* layer = getParent();

    if (layer == nullptr || layer->getTag() != SpriteTags::LAYER)
        return;

    
    for (Node*& child : layer->getChildren())
    {
        if (rectArea.containsPoint(child->getPosition()))
        {
            if (insideObjects.find(child) == insideObjects.end())
            {
                insideObjects.insert(child);
                
                if (onObjectEnter != nullptr)
                    onObjectEnter(child);
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