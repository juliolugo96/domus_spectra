# include "HallScene.hpp"

HallScene::HallScene() : RoomScene("hall-front.png")
{

}

HallScene::~HallScene()
{

}

Scene* HallScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::createWithPhysics();

    RefPtr<Layer> main_layer = HallScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);

    main_screen->addChild(main_layer);

    main_screen->setTag(SceneTags::Hall);

    return main_screen;
}

bool HallScene::init()
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

void HallScene::addPlayer()
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

    Vec2 const initPos = { ScreenSize.width/2 + Origin.x, 
                            Origin.y - ScreenSize.height * 0.15f};

    player->setPosition(initPos);

    if (shadowLayer != nullptr)
    {
      shadowLayer->setLightPosition(initPos);
      shadowLayer->setLightSize(0.7f + 100.f);
    }

    this->addChild(player);
}

void HallScene::addMedicalBoxes()
{}

void HallScene::addAreaTriggers()
{   
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    float width = ScreenSize.width;
    float height = ScreenSize.height;

    using AtInfo = std::pair<Vec2, Orientation>;

    DynArray<AtInfo> centerOfAreas = 
    {
        AtInfo(Vec2(width * 0.90f + Origin.x, height * 0.36f + Origin.y), Orientation::East),
        AtInfo(Vec2(width * 0.05f + Origin.x, height * 0.36f + Origin.y), Orientation::West),
        AtInfo(Vec2(width * 0.48f + Origin.x, height * 0.95f + Origin.y), Orientation::North)
    };

    for (auto & it : centerOfAreas)
    {
        RefPtr<AreaTrigger> at = AreaTrigger::create();

        at->setPosition(it.first);
        at->setRect(it.first, 50.f, 50.f);
        at->setOrientation(it.second);

        areaTriggers.append(at);
    }

    auto lastPos = centerOfAreas.get_last().first;

    areaTriggers.get_last()->setRect(lastPos, 50.f, 25.f);

    for (RefPtr<AreaTrigger> & at : areaTriggers)
    {
        at->setOnObjectEnter(([this, &at] (Node*& object) -> void
        {
            if (object->getTag() != SpriteTags::PLAYER)
                return;
            
            sPlayer->setOpenDoor(true);
            this->handleButton(true);
        }));

        at->setOnObjectExit(([this] (Node*& object) -> void
        {
            if (object->getTag() != SpriteTags::PLAYER)
                return;
            
            sPlayer->setOpenDoor(false);
            this->handleButton(false);
        }));

        at->setOnCheckObject(([this, &at] (Node*& object, bool & isInside) -> void
        {
            if (object->getTag() != SpriteTags::PLAYER)
                return;
            
            if (!isInside)
                return;

            if (at->hasOrientation() && 
                at->getOrientation() != sPlayer->getOrientation())
                isInside = false;
            else
                isInside = true;
        }));

        this->addChild(at.get());
    }
}