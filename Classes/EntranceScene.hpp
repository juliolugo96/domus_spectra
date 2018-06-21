# ifndef ENTRANCE_SCENE_HPP
# define ENTRANCE_SCENE_HPP

# include "SharedDefines.hpp"
# include "ShadowLayer.hpp" 

using namespace cocos2d;

class Entrance : public Layer
{
    public:
        Entrance();
        ~Entrance();
        ShadowLayer* _shadowLayer;
        CREATE_FUNC(Entrance);

        static Scene* createScene();

        using Curr_Class = Entrance;
        bool init() override;

        void update(float /**/) override;
    
    private:
        void AddBackground();
        void AddPlayer();
        void AddMedicalBox();
        void AddTriggerArea();
        void AddBottonForUseDoor();
        void HandleButton(bool /**/);

        Rect triggerArea;
        bool isOnDoor;
};

# endif