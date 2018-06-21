# include "EntranceScene.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Objects.hpp"

Entrance::Entrance()
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

    scheduleUpdate();

    this -> scheduleUpdate();

    return true;
}

void Entrance::update(float dt)
{
    auto c = this -> getChildren().back();
    _shadowLayer->setLightPosition(c->getPosition());
    Layer::update(dt);

    Player* player = sPlayer;

    if (player == nullptr)
        return;

    if (triggerArea.containsPoint(player->getPosition())
        && player->getOrientation() == Orientation::North)
    {
        HandleButton(true);
        player->setOpenDoor(true);
    }
    else
    {
        player->setOpenDoor(false);
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

    background->setPosition(CenterPos);
    _shadowLayer = ShadowLayer::create();
    background->addChild(_shadowLayer);

    this->addChild(background);
}

void Entrance::AddPlayer()
{
    RefPtr<Player> player = sPlayer;

    if (player == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const spritePos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height * 0.15f + Origin.y };

    _shadowLayer->setLightPosition(spritePos);
    _shadowLayer->setLightSize(0.7f + 100);
    player->setPosition(spritePos);

    this->addChild(player, 0);


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
    
    triggerArea = Rect(pos.x, pos.y, 20.f, 20.f);
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