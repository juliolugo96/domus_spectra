# include "EntranceScene.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Objects.hpp"

Entrance::Entrance() : isOnDoor(false), shadowLayer(nullptr)
{}

Entrance::~Entrance()
{}

Scene* Entrance::createScene()
{
    RefPtr<Scene> main_screen = Scene::createWithPhysics();

    RefPtr<Layer> main_layer = Entrance::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_screen->addChild(main_layer);

    main_screen->setTag(SceneTags::Entrance);

    return main_screen;
}

bool Entrance::init()
{
    if (!Layer::init())
        return false;

    AddBackground();
    AddMedicalBox();
    AddPlayer();
    AddTriggerArea();
    AddBottonForUseDoor();
    addHealthBar();

    scheduleUpdate();

    return true;
}

void Entrance::update(float dt)
{
    Layer::update(dt);

    if (sPlayer == nullptr)
        return;

    if (shadowLayer != nullptr)
        shadowLayer->setLightPosition(sPlayer->getPosition());
    
    if (healthBar != nullptr)
        healthBar->setPercent(float(sPlayer->getLife()));

    if (triggerArea.containsPoint(sPlayer->getPosition())
        && sPlayer->getOrientation() == Orientation::North)
    {
        HandleButton(true);
        sPlayer->setOpenDoor(true);
    }
    else
    {
        sPlayer->setOpenDoor(false);
        HandleButton(false);
    }
}

void Entrance::AddBackground()
{
    RefPtr<Sprite> background = Sprite::create("entrance.png");

    if (background == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    shadowLayer = ShadowLayer::create();

    background->setPosition(CenterPos);
    background->addChild(shadowLayer);

    this->addChild(background);
}

void Entrance::AddPlayer()
{
    RefPtr<Player> player = sPlayer;

    if (player == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const playerPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height * 0.15f + Origin.y };

    player->setPosition(playerPos);

    shadowLayer->setLightPosition(playerPos);
    shadowLayer->setLightSize(0.7f + 100.f);

    this->addChild(player);
}

void Entrance::AddMedicalBox()
{
    RefPtr<Sprite> box = MedicalBox::create();

    if (box == nullptr)
        return;
    
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const spritePos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height * 0.45f + Origin.y };

    box->setPosition(spritePos);

    this->addChild(box);
}

void Entrance::AddTriggerArea()
{   
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const pos = { ScreenSize.width * 0.495f + Origin.x, 
                            ScreenSize.height * 0.845f + Origin.y };
    
    triggerArea = Rect(pos.x, pos.y, 100.f, 100.f);
}

void Entrance::AddBottonForUseDoor()
{
    RefPtr<DrawNode> button = DrawNode::create();
    RefPtr<Label> label = Label::createWithTTF("Open Door", "fonts/Marker Felt.ttf", 18);

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

void Entrance::addHealthBar()
{
  healthBar = ui::LoadingBar::create("playerHpBar.png", 100.f);
  RefPtr<ui::LoadingBar> healthBarBehind = ui::LoadingBar::create("healthBarBehind.png", 100.f);

  Size const ScreenSize = sDirector->getVisibleSize();
  Vec2 const Origin = sDirector->getVisibleOrigin();

  Vec2 const barPos = { ScreenSize.width * 0.15f + Origin.x, 
                          Origin.y + ScreenSize.height * 0.95f};

  healthBar->setPosition(barPos);
  healthBarBehind->setPosition(barPos);

  addChild(healthBar, 1);
  addChild(healthBarBehind, 0);
}

void Entrance::HandleButton(bool enable)
{
    Node* button = getChildByTag(100);
    Node* label = getChildByTag(101);

    if (button == nullptr || label == nullptr)
        return;

    if (isOnDoor == enable)
        return;
        
    isOnDoor = enable;

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