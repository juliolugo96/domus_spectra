# ifndef HALL_SCENE_HPP
# define HALL_SCENE_HPP

# include "SharedDefines.hpp"
# include "Objects.hpp"
# include "RoomScene.hpp"
# include "Enemy.hpp"
# include <array.H>

using namespace cocos2d;

class HallScene : public RoomScene
{
    public:
        HallScene();
        ~HallScene();

        CREATE_FUNC(HallScene);

        static Scene* createScene();

        bool init() override;

       // void update(float) override;

    private:
        void addAudio();
        void addEnemy();
        void addPlayer() override;
        void addMedicalBoxes() override;
        void addAreaTriggers() override;

        DynArray<RefPtr<AreaTrigger>> areaTriggers;
};

# endif