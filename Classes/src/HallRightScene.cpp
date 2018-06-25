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
    addButtonForUseAreaTriggers();
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
{
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const backPos = { Origin.x + ScreenSize.width * 0.05f, 
                            ScreenSize.height * 0.32f + Origin.y};

    Vec2 const quizPos = { Origin.x + ScreenSize.width * 0.84f, 
                            ScreenSize.height * 0.29f + Origin.y};

    backArea = AreaTrigger::create();
    quizArea = AreaTrigger::create();

    quizArea->setPosition(quizPos);
    quizArea->setOrientation(Orientation::East);
    quizArea->setRect(quizPos, 20.f, 50.f);

    backArea->setPosition(backPos);
    backArea->setOrientation(Orientation::West);
    backArea->setRect(backPos, 20.f, 100.f);

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

    quizArea->setOnObjectEnter([this] (Node*& object) -> void
    {
        if (object == nullptr)
            return;

        if (object->getTag() != SpriteTags::PLAYER)
            return;

        sPlayer->setOpenDoor(true);
        this->handleButton(true);
    });

    quizArea->setOnObjectExit([this] (Node*& object) -> void
    {
        if (object == nullptr)
            return;

        if (object->getTag() != SpriteTags::PLAYER)
            return;

        sPlayer->setOpenDoor(false);
        this->handleButton(false);
    });

    quizArea->setOnCheckObject([this] (Node*& object, bool & isInside) -> void
    {
        if (object == nullptr)
            return;

        if (object->getTag() != SpriteTags::PLAYER)
            return;

        if (!isInside)
            return;    
        
        if (quizArea->hasOrientation() && 
            quizArea->getOrientation() != sPlayer->getOrientation())
            isInside = false;
        else
            isInside = true;
    });

    this->addChild(backArea);
    this->addChild(quizArea);
}

void HallRightScene::addMedicalBoxes()
{}