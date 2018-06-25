#ifndef FINAL_SCENE_HPP
#define FINAL_SCENE_HPP

# include "SharedDefines.hpp"
# include "Boss.hpp"

using namespace cocos2d;

class FinalScene : public Layer
{
    public:
        FinalScene();
        ~FinalScene();
        CREATE_FUNC(FinalScene);

        static Scene* createScene();
        bool init() override;

    private:
        void AddAudio();
        void AddBackground();
        void AddPlayer();
        void AddBoss();
};

# endif