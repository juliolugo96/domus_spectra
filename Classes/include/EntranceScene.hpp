# ifndef ENTRANCE_SCENE_HPP
# define ENTRANCE_SCENE_HPP

# include "SharedDefines.hpp"
# include "RoomScene.hpp"
# include "AreaTrigger.hpp"
# include "ShadowLayer.hpp"

using namespace cocos2d;

class Entrance : public RoomScene
{
    public:
        Entrance();
        ~Entrance();
        CREATE_FUNC(Entrance);

        static Scene* createScene();

        using Curr_Class = Entrance;
        bool init() override;

    protected:
        void addPlayer() override;
        void addMedicalBoxes() override;
        void addAreaTriggers() override;

        RefPtr<AreaTrigger> areaTrigger;
};

# endif