#ifndef FINAL_SCENE_HPP
#define FINAL_SCENE_HPP

# include "RoomScene.hpp"

using namespace cocos2d;

class FinalScene : public RoomScene
{
    public:
        FinalScene();
        ~FinalScene();
        CREATE_FUNC(FinalScene);

        static Scene* createScene();
        bool init() override;

    private:
        void addAudio();

        void addPlayer() override;
        void addAreaTriggers() override;
        void addMedicalBoxes() override;
};

# endif