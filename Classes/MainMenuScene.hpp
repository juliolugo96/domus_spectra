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

        using Curr_Class = MainMenuScene;

    private:
        void OnPlayPressed(Ref* /**/);
        void OnMusicPressed(Ref* /**/);
        void AddMenu();
        void AddBackground();
};


# endif