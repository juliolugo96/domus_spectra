# include "HallScene.hpp"

HallScene::HallScene() : lastAreaVisited(nullptr)
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
    addButtonForUseEntrance();
    addAreaTriggers();
    addHealthBar();

    scheduleUpdate();

    return true;
}

bool HallScene::isOnLastArea() const
{
    if (lastAreaVisited == nullptr)
        return false;

    return lastAreaVisited->first.containsPoint(sPlayer->getPosition()) && 
            lastAreaVisited->second == sPlayer->getOrientation();
}

void HallScene::update(float dt)
{
    Layer::update(dt);

    if (shadowLayer != nullptr)
        shadowLayer->setLightPosition(sPlayer->getPosition());

    if (healthBar != nullptr)
      healthBar->setPercent(sPlayer->getLife());

    for (auto & it : areaTriggers)
    {
        if (it.first.containsPoint(sPlayer->getPosition()) && 
            it.second == sPlayer->getOrientation())
        {
            lastAreaVisited = &it;
            sPlayer->setOpenDoor(true);
            handleButton(true);
        }
        else
        {
            if (isOnLastArea())
                break;
            
            lastAreaVisited = nullptr;
            sPlayer->setOpenDoor(false);
            handleButton(false);
        }
    }
}

void HallScene::addBackground()
{
    RefPtr<Sprite> background = Sprite::create("hall-front.png");

    shadowLayer = ShadowLayer::create();

    if (background == nullptr || shadowLayer == nullptr)
        return;
    
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    background->setPosition(CenterPos);
    background->addChild(shadowLayer);

    this->addChild(background);
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

void HallScene::addHealthBar()
{
  healthBar = ui::LoadingBar::create("", 100.f);
  RefPtr<ui::LoadingBar> healthBarBehind = ui::LoadingBar::create("", 100.f);

  Size const ScreenSize = sDirector->getVisibleSize();
  Vec2 const Origin = sDirector->getVisibleOrigin();

  Vec2 const barPos = { ScreenSize.width * 0.125f + Origin.x, 
                          Origin.y + ScreenSize.height * 0.95f};

  healthBar->setPosition(barPos);
  healthBarBehind->setPosition(barPos);

  addChild(healthBar);
  addChild(healthBarBehind);
}

void HallScene::addAmmunition()
{}

void HallScene::addMedicalBoxes()
{}

void HallScene::addAreaTriggers()
{   
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    float width = ScreenSize.width;
    float height = ScreenSize.height;

    DynArray<std::pair<Vec2, Orientation>> centerOfAreas = 
    {
        { Vec2(width * 0.95f + Origin.x, height * 0.36f + Origin.y), Orientation::East },
        { Vec2(width * 0.05f + Origin.x, height * 0.36f + Origin.y), Orientation::West },
        { Vec2(width * 0.48f + Origin.x, height * 0.95f + Origin.y), Orientation::North},
    };

    for (auto & it : centerOfAreas)
    {
        Rect rect(it.first.x, it.first.y, 30.f, 100.f);
        areaTriggers.append(AreaTrigger(rect, it.second));
    }

    auto lastPos = centerOfAreas.get_last().first;

    areaTriggers.get_last().first = Rect(lastPos.x, lastPos.y, 20.f, 20.f);
}

void HallScene::addButtonForUseEntrance()
{
    RefPtr<DrawNode> button = DrawNode::create();
    RefPtr<Label> label = Label::createWithTTF("Go to the Room", "fonts/Marker Felt.ttf", 18);

    if (button == nullptr || label == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 pos = { ScreenSize.width * 0.95f + Origin.x, 
                            ScreenSize.height * 0.125f + Origin.y };
    
    button->drawDot(pos, 10.f, Color4F::RED);
    button->setVisible(false);
    button->setTag(100);

    pos = { ScreenSize.width * 0.95f + Origin.x, 
            ScreenSize.height * 0.10f + Origin.y };


    label->setPosition(pos);
    label->setVisible(false);
    label->setTag(101);

    addChild(label);
    addChild(button);
}

void HallScene::handleButton(bool enable)
{
    Node* button = getChildByTag(100);
    Node* label = getChildByTag(101);

    if (button == nullptr || label == nullptr)
        return;

    if (!button->isVisible() && enable)
    {
        button->setVisible(true);
        label->setVisible(true);
    }
    else
    {
        button->setVisible(false);
        label->setVisible(false);
    }
}
