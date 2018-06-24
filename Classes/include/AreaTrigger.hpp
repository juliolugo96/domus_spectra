# ifndef AREATRIGGER_HPP
# define AREATRIGGER_HPP

# include "SharedDefines.hpp"

using namespace cocos2d;

class AreaTrigger : public Node
{
    public:
        AreaTrigger();
        ~AreaTrigger();

        CREATE_FUNC(AreaTrigger);

        bool isInside(Node*& object) const
        { 
            return rectArea.containsPoint(object->getPosition());
        }

        bool hasOrientation() const { return orientation != Orientation::Null; }

        Orientation getOrientation() const { return orientation; }

        void setOrientation(Orientation ori) { orientation = ori; }
        void setOnObjectEnter(std::function<void(Node*& /**/)> const &);
        void setOnObjectExit(std::function<void(Node*& /**/)> const &);
        void setOnCheckObject(std::function<void(Node*& /**/, bool & /**/)> const &);

        void update(float /**/) override;

        void setRect(Vec2 const & pos, float width, float height);

    private:
        
        std::function<void(Node*& /**/)> onObjectEnter;
        std::function<void(Node*& /**/)> onObjectExit;
        std::function<void(Node*& /**/, bool & /**/)> onCheckObject;

        Rect rectArea;
        Orientation orientation;
        std::set<Node*> insideObjects;
};

# endif