# include "AisleScene.hpp"

AisleScene::AisleScene() : RoomScene("aisle.png")
{

}

AisleScene::~AisleScene()
{

}

Scene* AisleScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::createWithPhysics();

    RefPtr<Layer> main_layer = AisleScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);
    main_screen->setTag(SceneTags::Aisle);

    main_screen->addChild(main_layer);

    return main_screen;
}

bool AisleScene::init()
{
    if (!Layer::init())
        return false;

    addBackground();
    addPlayer();
   addAreaTriggers();

    scheduleUpdate();

    return true;
}

void AisleScene::addPlayer()
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

    Vec2 const playerPos = { ScreenSize.width * 0.5f + Origin.x, 
                             Origin.y - ScreenSize.height * 0.125f};

    player->setPosition(playerPos);

    if (shadowLayer != nullptr)
    {
      shadowLayer->setLightPosition(playerPos);
      shadowLayer->setLightSize(0.7f + 100.f);
    }

    this->addChild(player);
}

void AisleScene::addMedicalBoxes()
{}

void AisleScene::addAreaTriggers()
{}
