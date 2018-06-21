# include "MainMenuScene.hpp"
# include "EntranceScene.hpp"

MainMenuScene::MainMenuScene() : Layer()
{
    /*Empty*/
}

MainMenuScene::~MainMenuScene()
{

}

Scene* MainMenuScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::create();

    RefPtr<Layer> main_layer = MainMenuScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    sAudioEngine->playBackgroundMusic("menu-theme.mp3", true);
    sAudioEngine->setBackgroundMusicVolume(0.5f);

    main_screen->addChild(main_layer);

    return main_screen;
}

bool MainMenuScene::init()
{
    if (!Layer::init())
        return false;
    
    AddBackground();
    AddMenu();

    return true;
}

void MainMenuScene::AddBackground()
{
    RefPtr<Sprite> background = Sprite::create("menu-background.png");

    if (background == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    background->setPosition(CenterPos);

    this->addChild(background);
}

void MainMenuScene::AddMenu()
{
    RefPtr<MenuItemImage> play = MenuItemImage::create("button-start.png", "button-start.png",
                                CC_CALLBACK_1(Curr_Class::OnPlayPressed, this));

    RefPtr<MenuItemImage> exit = MenuItemImage::create("button-back.png", "button-back.png",
                                CC_CALLBACK_1(Curr_Class::OnExitPressed, this));

    RefPtr<MenuItemImage> sound_On = MenuItemImage::create("music-on.png", 
                                        "music-off.png");

    RefPtr<MenuItemImage> sound_Off = MenuItemImage::create("music-off.png", 
                                        "music-off.png");

    RefPtr<MenuItemToggle> toggle = MenuItemToggle::createWithTarget(this, 
                                    menu_selector(Curr_Class::OnMusicPressed), 
                                    sound_On.get(), sound_Off.get(), NULL);

    RefPtr<Menu> main_menu = Menu::create(play.get(), exit.get(),
                                            toggle.get(), NULL);

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();
    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                             ScreenSize.height/2 + Origin.y };

    main_menu->setPosition(CenterPos);
    main_menu->alignItemsVerticallyWithPadding(1.5f);
     
    this->addChild(main_menu);
}

void MainMenuScene::OnPlayPressed(Ref* /**/)
{
    RefPtr<Scene> init_level = Entrance::createScene();

    sDirector->replaceScene(TransitionFlipAngular::create(2.f, init_level));
}

void MainMenuScene::OnExitPressed(Ref* /**/)
{
    sDirector->end();
}


void MainMenuScene::OnMusicPressed(Ref* /**/)
{
    if (sAudioEngine->isBackgroundMusicPlaying())
        sAudioEngine->pauseBackgroundMusic();
    else
        sAudioEngine->resumeBackgroundMusic();
}