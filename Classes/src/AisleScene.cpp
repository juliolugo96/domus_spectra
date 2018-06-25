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
    addButtonForUseAreaTriggers();
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
{
   backArea = AreaTrigger::create();
   bossDoor = AreaTrigger::create();

   Size const ScreenSize = sDirector->getVisibleSize();
   Vec2 const Origin = sDirector->getVisibleOrigin();

   Vec2 const doorPos = { ScreenSize.width * 0.49f + Origin.x, 
                        Origin.y + ScreenSize.height * 0.88f };

   Vec2 const backAreaPos = { ScreenSize.width * 0.49f + Origin.x,
                              ScreenSize.height * 0.15f + Origin.y };

   backArea->setPosition(backAreaPos);
   backArea->setOrientation(Orientation::South);
   backArea->setRect(backAreaPos, 60.f, 50.f);

   bossDoor->setPosition(doorPos);
   bossDoor->setOrientation(Orientation::North);
   bossDoor->setRect(doorPos, 60.f, 50.f);

   backArea->setOnObjectEnter([this] (Node*& object) -> void
   {
      if (object == nullptr)
         return;
      
      if (object->getTag() != SpriteTags::PLAYER)
         return;

      sPlayer->setOpenDoor(true);
      sPlayer->setExitOfRoom(true);
      this->handleButton(true);
   });

   backArea->setOnObjectExit([this] (Node*& object) -> void
   {
      if (object == nullptr)
         return;
      
      if (object->getTag() != SpriteTags::PLAYER)
         return;

      sPlayer->setOpenDoor(false);
      sPlayer->setExitOfRoom(false);
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

   bossDoor->setOnObjectEnter([this] (Node*& object) -> void
   {
      if (object == nullptr)
         return;
      
      if (object->getTag() != SpriteTags::PLAYER)
         return;

      sPlayer->setOpenDoor(true);
      this->handleButton(true);
   });

   bossDoor->setOnObjectExit([this] (Node*& object) -> void
   {
      if (object == nullptr)
         return;
      
      if (object->getTag() != SpriteTags::PLAYER)
         return;

      sPlayer->setOpenDoor(false);
      this->handleButton(false);
   });

   bossDoor->setOnCheckObject([this] (Node*& object, bool & isInside) -> void
    {
        if (object == nullptr)
            return;

        if (object->getTag() != SpriteTags::PLAYER)
            return;

        if (!isInside)
            return;    

        if (bossDoor->hasOrientation() && 
            bossDoor->getOrientation() != sPlayer->getOrientation())
            isInside = false;
        else
            isInside = true;
    });

    addChild(backArea);
    addChild(bossDoor);

}
