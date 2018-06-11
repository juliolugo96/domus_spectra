# include "MainMenuScene.hpp"

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
    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, ScreenSize.height/2 + Origin.y };

    background->setPosition(CenterPos);

    this->addChild(background);
}

void MainMenuScene::AddMenu()
{
    RefPtr<MenuItemImage> play_button = MenuItemImage::create("play.png", 
                                        "play.png", 
                                        CC_CALLBACK_1(Curr_Class::OnPlayPressed, 
                                        this));

    RefPtr<MenuItemImage> music_button = MenuItemImage::create("music-on.png", 
                                        "music-off.png", 
                                        CC_CALLBACK_1(Curr_Class::OnMusicPressed, 
                                        this));

    RefPtr<Menu> main_menu = Menu::create(play_button.get(), 
                                            music_button.get(), NULL);

    play_button->setPosition(Vec2(CenterPos.x - play_button->getContentSize().width/2, CenterPos.y - play_button->getContentSize().height/2));
    main_menu->setPosition(Vec2::ZERO);    
    this->addChild(main_menu);
}

void MainMenuScene::OnPlayPressed(Ref* /**/)
{

}

void MainMenuScene::OnMusicPressed(Ref* /**/)
{
    if (sAudioEngine->isBackgroundMusicPlaying())
        sAudioEngine->pauseBackgroundMusic();
    else
        sAudioEngine->resumeBackgroundMusic();
}