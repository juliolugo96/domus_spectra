# include "HallLeftScene.hpp"

HallLeftScene::HallLeftScene() : RoomScene("hall-2.png")
{

}

HallLeftScene::~HallLeftScene()
{

}

Scene* HallLeftScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::createWithPhysics();

    RefPtr<Layer> main_layer = HallLeftScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);
    main_screen->setTag(SceneTags::HallLeft);

    main_screen->addChild(main_layer);

    return main_screen;
}

bool HallLeftScene::init()
{
    if (!Layer::init())
        return false;

    addBackground();
    addPlayer();
    addAreaTriggers();
    addHealthBar();

    return true;
}

void HallLeftScene::addPlayer()
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

    Vec2 const playerPos = { ScreenSize.width * 1.05f + Origin.x, 
                            ScreenSize.height * 0.5f + Origin.y};

    player->setPosition(playerPos);

    if (shadowLayer != nullptr)
    {
      shadowLayer->setLightPosition(playerPos);
      shadowLayer->setLightSize(0.7f + 100.f);
    }

    this->addChild(player);
}

void HallLeftScene::addAreaTriggers()
{}

void HallLeftScene::addMedicalBoxes()
{}