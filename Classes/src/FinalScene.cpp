# include "FinalScene.hpp"
# include "Boss.hpp"

Scene* FinalScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::createWithPhysics();

    RefPtr<Layer> main_layer = FinalScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);
    main_screen->setTag(SceneTags::FinalStage);
    
    main_screen->addChild(main_layer);


    return main_screen;
}

FinalScene::FinalScene() : RoomScene("final_stage.png")
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

    addBackground();
    addHealthBar();
    addPlayer();
    addAudio();

    scheduleUpdate();

    return true;
}

void FinalScene::addAudio()
{
    sAudioEngine->playBackgroundMusic("final-stage.mp3", true);
}

void FinalScene::addPlayer()
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
    player->setOrientation(Orientation::East);

    RefPtr<Sprite> boss = Boss::create();

    if (boss == nullptr)
        return;

    spritePos = { ScreenSize.width * 0.5f + Origin.x,
                  ScreenSize.height * 0.5f + Origin.y };

    boss->setPosition(spritePos);

    addChild(boss);
    addChild(player);
}

void FinalScene::addAreaTriggers()
{

}

void FinalScene::addMedicalBoxes()
{

}