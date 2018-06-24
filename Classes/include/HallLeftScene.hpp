# ifndef HALL_LEFT_HPP
# define HALL_LEFT_HPP

# include "SharedDefines.hpp"
# include "Objects.hpp"
# include "RoomScene.hpp"

using namespace cocos2d;

class HallLeftScene : public RoomScene
{
    public:
        HallLeftScene();
        ~HallLeftScene();

        CREATE_FUNC(HallLeftScene);
        
        static Scene* createScene();

        bool init() override;

    private:
        void addPlayer() override;
        void addAreaTriggers() override;
        void addMedicalBoxes() override;
};

# endif