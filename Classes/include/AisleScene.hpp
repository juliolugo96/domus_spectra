# ifndef AISLE_SCENE_HPP
# define AISLE_SCENE_HPP

# include "SharedDefines.hpp"
# include "RoomScene.hpp"

using namespace cocos2d;


class AisleScene : public RoomScene
{
    public:
        AisleScene();
        ~AisleScene();

        CREATE_FUNC(AisleScene);
        
        static Scene* createScene();

        bool init() override;

    private:
        void addPlayer() override;
        void addAreaTriggers() override;
        void addMedicalBoxes() override;

        RefPtr<AreaTrigger> backArea;
        RefPtr<AreaTrigger> bossDoor;
};

# endif