# include "HallRightScene.hpp"

HallRightScene::HallRightScene() : RoomScene("hall-3.png")
{

}

HallRightScene::~HallRightScene()
{

}

Scene* HallRightScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::createWithPhysics();

    RefPtr<Layer> main_layer = HallRightScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);
    main_screen->setTag(SceneTags::HallRight);

    main_screen->addChild(main_layer);

    return main_screen;
}

bool HallRightScene::init()
{
    if (!Layer::init())
        return false;

    addBackground();
    addPlayer();
    addAreaTriggers();
    addHealthBar();

    scheduleUpdate();

    return true;
}

void HallRightScene::addPlayer()
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

    Vec2 const playerPos = { Origin.x - ScreenSize.width * 0.1f, 
                            ScreenSize.height * 0.25f + Origin.y};

    player->setPosition(playerPos);

    if (shadowLayer != nullptr)
    {
      shadowLayer->setLightPosition(playerPos);
      shadowLayer->setLightSize(0.7f + 100.f);
    }

    this->addChild(player);
}

void HallRightScene::addAreaTriggers()
{}

void HallRightScene::addMedicalBoxes()
{}