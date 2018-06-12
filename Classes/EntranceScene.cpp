# include "EntranceScene.hpp"
# include "Player.hpp"

Entrance::Entrance()
{}

Entrance::~Entrance()
{}

Scene* Entrance::createScene()
{
    RefPtr<Scene> main_screen = Scene::create();

    RefPtr<Layer> main_layer = Entrance::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_screen->addChild(main_layer);

    return main_screen;
}

bool Entrance::init()
{
    if (!Layer::init())
        return false;

    AddBackground();

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