# include "Player.hpp"

Player::Player() : Sprite(), score(0), life(100)
{

}

Player::~Player()
{

}

Player* Player::create()
{
    Player *sprite = new (std::nothrow) Player();
    if (sprite && sprite->initWithFile("main_character.png"))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool Player::initWithFile(const std::string & fileName)
{
    if (!Sprite::initWithFile(fileName))
        return false;

    RefPtr<EventListenerKeyboard> listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(Curr_Class::onKeyPressed, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Player::modHp(int8 const value)
{
    life += value;

    if (life <= 0)
        stopAllActions();
}

void Player::setOrientation(Orientation ori)
{
    orientation = ori;
}

Orientation Player::getOrientation() const
{
    return orientation;
}

void Player::moveToPoint(Vec2 const & tgt)
{
    runAction(MoveTo::create(1.25f, tgt));
}

void Player::shoot()
{
    RefPtr<Sprite> bullet = Sprite::create("bullet.png");
    
    Vec2 bullet_Pos;

    if (getOrientation() == Orientation::North)
    {
        bullet_Pos = Vec2(getPosition().x + 0,
                          getPosition().y);
    }
    else if (getOrientation() == Orientation::West)
    {
        bullet_Pos = Vec2(getPosition().x - 0,
                          getPosition().y);
    }

    bullet->setPosition(bullet_Pos);

    CallFuncN* dissappearOnLimit = CallFuncN::create(
                                        CC_CALLBACK_1(Curr_Class::removeBullet, 
                                                        this, true));
    
    MoveTo* moveToLimit = MoveTo::create(1.4, Vec2(bullet_Pos.x, 
                                        -bullet->getContentSize().height/2));

    this->addChild(bullet);

    bullet->runAction(Sequence::create(moveToLimit, dissappearOnLimit, NULL));
    
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_SPACE:
        {
            this->shoot();
            break;
        }

        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
          Vec2 dest = { getPosition().x - getContentSize().width * 0.1f, 
                        getPosition().y };
          moveToPoint(dest);
          break;
        }

        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
          Vec2 dest = { getPosition().x + getContentSize().width * 0.1f, 
                        getPosition().y };
          moveToPoint(dest);
          break;
        }

        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        {
          Vec2 dest = { getPosition().x, 
                          getPosition().y + getContentSize().height * 0.1f };
          moveToPoint(dest);
          break;
        }

        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        {
          Vec2 dest = { getPosition().x, 
                          getPosition().y - getContentSize().height * 0.1f };
          moveToPoint(dest);
          break;
        }

        default : break;
    }
}

void Player::removeBullet(Node* sender, bool cleanup)
{
    if (sender == nullptr)
        return;

    sender->removeFromParentAndCleanup(true);
}