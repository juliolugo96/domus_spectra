# include "EntranceScene.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Objects.hpp"

Entrance::Entrance() : RoomScene("entrance.png")
{}

Entrance::~Entrance()
{}

Scene* Entrance::createScene()
{
    RefPtr<Scene> main_screen = Scene::createWithPhysics();

    RefPtr<Layer> main_layer = Entrance::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);
    
    main_screen->addChild(main_layer);
    main_screen->setTag(SceneTags::Entrance);

    return main_screen;
}

bool Entrance::init()
{
    if (!Layer::init())
        return false;

    addBackground();
    addMedicalBoxes();
    addPlayer();
    addAreaTriggers();
    addButtonForUseAreaTriggers();
    addHealthBar();
    addAudio();
    scheduleUpdate();

    return true;
}

void Entrance::addAudio()
{
    sAudioEngine->playBackgroundMusic("hall-stage.mp3", true);
    sAudioEngine->setBackgroundMusicVolume(1.f);
}

void Entrance::addPlayer()
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

void Entrance::addMedicalBoxes()
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

void Entrance::addAreaTriggers()
{   
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const pos = { ScreenSize.width * 0.495f + Origin.x, 
                            ScreenSize.height * 0.845f + Origin.y };
    
    areaTrigger = AreaTrigger::create();

    areaTrigger->setPosition(pos);
    areaTrigger->setRect(pos, 20.f, 20.f);
    areaTrigger->setOrientation(Orientation::North);

    areaTrigger->setOnObjectEnter(([this] (Node*& object) -> void
    {
        if (object->getTag() != SpriteTags::PLAYER)
            return;

        sPlayer->setOpenDoor(true);
        this->handleButton(true);
    }));

    areaTrigger->setOnObjectExit(([this] (Node*& object) -> void
    {
        if (object->getTag() != SpriteTags::PLAYER)
            return;
        
        sPlayer->setOpenDoor(false);
        this->handleButton(false);
    }));

    areaTrigger->setOnCheckObject(([this] (Node*& object, bool & isInside) -> void
    {
        if (object->getTag() != SpriteTags::PLAYER)
            return;

        if (!isInside)
            return;    
        
        if (areaTrigger->hasOrientation() && 
            areaTrigger->getOrientation() != sPlayer->getOrientation())
            isInside = false;
        else
            isInside = true;
    }));

    this->addChild(areaTrigger);
}