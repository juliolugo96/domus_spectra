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
    addButtonForUseAreaTriggers();
    addAreaTriggers();
    addHealthBar();

    scheduleUpdate();

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

    Vec2 const playerPos = { ScreenSize.width * 1.15f + Origin.x, 
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
{
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const backAreaPos = { ScreenSize.width * 0.95f + Origin.x, 
                            ScreenSize.height * 0.3f + Origin.y};

    backArea = AreaTrigger::create();

    backArea->setPosition(backAreaPos);
    backArea->setRect(backAreaPos, 50.f, 150.f);
    backArea->setOrientation(Orientation::East);

    backArea->setOnObjectEnter([this] (Node*& object) -> void
    {
        if (object == nullptr)
            return;

        if (object->getTag() != SpriteTags::PLAYER)
            return;

        sPlayer->setExitOfRoom(true);
        sPlayer->setOpenDoor(true);
        this->handleButton(true);
    });

    backArea->setOnObjectExit([this] (Node*& object) -> void
    {
        if (object == nullptr)
            return;

        if (object->getTag() != SpriteTags::PLAYER)
            return;
        
        sPlayer->setExitOfRoom(false);
        sPlayer->setOpenDoor(false);
        this->handleButton(false);
    });

    backArea->setOnCheckObject([this] (Node*& object, bool & isInside) -> void
    {
        if (object == nullptr)
            return;

        if (object->getTag() != SpriteTags::PLAYER)
            return;

        if (!isInside)
            return;    

        if (backArea->hasOrientation() && 
            backArea->getOrientation() != sPlayer->getOrientation())
            isInside = false;
        else
            isInside = true;
    });

    this->addChild(backArea);
}

void HallLeftScene::addMedicalBoxes()
{}