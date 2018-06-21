# include "AisleScene.hpp"

AisleScene::AisleScene()
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

    main_screen->addChild(main_layer);

    main_screen->setTag(SceneTags::Aisle);

    return main_screen;
}

bool AisleScene::init()
{
    if (!Layer::init())
        return false;

    Sprite* background = Sprite::create("aisle.png");

    if (background == nullptr)
        return false;
    
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    background->setPosition(CenterPos);

    this->addChild(background);

    return true;
}

void AisleScene::AddMedicalBoxes()
{}

void AisleScene::AddAmmunition()
{}
