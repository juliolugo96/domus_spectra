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

        inline bool isInside(Node*& object) const
        { 
            return rectArea.containsPoint(object->getPosition());
        }

        void setOnObjectEnter(std::function<void(Node*& /**/)> const &);
        void setOnObjectExit(std::function<void(Node*& /**/)> const &);

        void update(float /**/) override;

        void setRect(Vec2 const & pos, float width, float height);

    private:
        
        std::function<void(Node*& /**/)> onObjectEnter;
        std::function<void(Node*& /**/)> onObjectExit;

        Rect rectArea;

        std::set<Node*> insideObjects;
};

# endif