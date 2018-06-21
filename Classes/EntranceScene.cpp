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

    return true;
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

    player->setPosition(spritePos);

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

void Entrance::AddDoor()
{
    
}