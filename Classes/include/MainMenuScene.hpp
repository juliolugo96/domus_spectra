# include "SharedDefines.hpp"

# ifndef MAIN_MENU_SCENE_HPP
# define MAIN_MENU_SCENE_HPP


using namespace cocos2d;

class MainMenuScene : public Layer
{
    public:
        MainMenuScene();
        ~MainMenuScene();

        CREATE_FUNC(MainMenuScene);

        static Scene* createScene();
        bool init() override;

        void onExit() override;

        using Curr_Class = MainMenuScene;

    private:
        void onPlayPressed(Ref* /**/);
        void onExitPressed(Ref * /**/);
        void onMusicPressed(Ref* /**/);
        void addMenu();
        void addAudio();
        void addBackground();
};


# endif