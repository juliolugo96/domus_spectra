# include "RoomScene.hpp"

void RoomScene::addBackground()
{
    RefPtr<Sprite> background = Sprite::createWithSpriteFrameName(backgroundName.c_str());

    if (background == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    shadowLayer = ShadowLayer::create();

    background->setPosition(CenterPos);
    //background->addChild(shadowLayer);

    this->addChild(background);
}

void RoomScene::addButtonForUseAreaTriggers()
{
    RefPtr<DrawNode> button = DrawNode::create();
    RefPtr<Label> label = Label::createWithTTF("Go To Room", "fonts/Marker Felt.ttf", 18);

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

void RoomScene::handleButton(bool enable)
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

void RoomScene::addHealthBar()
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

void RoomScene::update(float dt)
{
    Layer::update(dt);

    if (sPlayer == nullptr)
        return;

    if (shadowLayer != nullptr)
        shadowLayer->setLightPosition(sPlayer->getPosition());
    
    if (healthBar != nullptr)
        healthBar->setPercent(float(sPlayer->getLife()));
}