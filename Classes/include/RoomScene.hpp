# ifndef ROOM_SCENE_HPP
# define ROOM_SCENE_HPP

# include "SharedDefines.hpp"
# include "ShadowLayer.hpp"

using namespace cocos2d;

class RoomScene : public Layer
{
    public:
        RoomScene(const std::string & bgName) : backgroundName(bgName) {}
        ~RoomScene() {};

    protected:
        void addHealthBar();
        void addBackground();
        
        virtual void addPlayer() = 0;
        virtual void addMedicalBoxes() = 0;
        virtual void addAreaTriggers() = 0;

        void addButtonForUseAreaTriggers();
        void handleButton(bool /**/);

        RefPtr<ui::LoadingBar> healthBar;
        RefPtr<ShadowLayer> shadowLayer;
        bool isOnDoor;

        std::string backgroundName;
};

# endif