# ifndef HALL_SCENE_HPP
# define HALL_SCENE_HPP

# include "SharedDefines.hpp"
# include "Objects.hpp"
# include <array.H>

using namespace cocos2d;

using AreaTrigger = std::pair<Rect, Orientation>;

class HallScene : public Layer
{
    public:
        HallScene();
        ~HallScene();

        CREATE_FUNC(HallScene);

        static Scene* createScene();

        bool init() override;
        void update(float /**/) override;

    private:

        bool isOnLastArea() const;

        void addBackground();
        void addPlayer();
        void addMedicalBoxes();
        void addAmmunition();
        void addAreaTriggers();
        void addButtonForUseEntrance();

        void handleButton(bool /**/);

        DynArray<AreaTrigger> areaTriggers;
        AreaTrigger* lastAreaVisited;
};

# endif