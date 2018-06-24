# ifndef HALL_RIGHT_SCENE
# define HALL_RIGHT_SCENE

# include "SharedDefines.hpp"
# include "Objects.hpp"
# include "RoomScene.hpp"

using namespace cocos2d;

class HallRightScene : public RoomScene
{
    public:
        HallRightScene();
        ~HallRightScene();

        CREATE_FUNC(HallRightScene);
        
        static Scene* createScene();

        bool init() override;

    private:
        void addPlayer() override;
        void addAreaTriggers() override;
        void addMedicalBoxes() override;
};

# endif