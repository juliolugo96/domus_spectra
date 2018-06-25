# include "FinalScene.hpp"
# include "Boss.hpp"

Scene* FinalScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::create();

    RefPtr<Layer> main_layer = FinalScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);
    
    main_screen->addChild(main_layer);

    main_screen->setTag(SceneTags::FinalStage);

    return main_screen;
}

FinalScene::FinalScene() : Layer()
{

}

FinalScene::~FinalScene()
{
    sAudioEngine->stopBackgroundMusic(true);
}

bool FinalScene::init()
{
    if (!Layer::init())
        return false;

    AddBackground();
    AddPlayer();
    AddAudio();
    AddBoss();

    return true;
}

void FinalScene::AddAudio()
{
    sAudioEngine->playBackgroundMusic("final-stage.mp3", true);
}

void FinalScene::AddBoss()
{
    auto boss = Boss::create();

    if(boss == nullptr)
        return;

    boss->setPosition(Vec2(512, 384));

    this -> addChild(boss);
}

void FinalScene::AddBackground()
{
    RefPtr<Sprite> background = Sprite::create("final_stage.png");

    if (background == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    background->setPosition(CenterPos);

    this->addChild(background);
}

void FinalScene::AddPlayer()
{
    RefPtr<Player> player = sPlayer;

    if (player == nullptr)
        return;

    if (player->isOnScene())
    {
        player->stopAllActions();
        player->removeFromParentAndCleanup(false);
    }

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 spritePos = { Origin.x - ScreenSize.width * 0.05f, 
                            ScreenSize.height * 0.42f + Origin.y };

    player->setPosition(spritePos);

    RefPtr<Sprite> boss = Boss::create();

    if (boss == nullptr)
        return;

    spritePos = { ScreenSize.width * 0.5f + Origin.x,
                  ScreenSize.height * 0.5f + Origin.y };

    boss->setPosition(spritePos);

    this->addChild(player);
    this->addChild(boss);
}