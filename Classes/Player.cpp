# include "Player.hpp"
# include "FinalScene.hpp"
# include "Objects.hpp"

static RefPtr<Player> sSharedPlayer = nullptr;

Player::Player() : Sprite(), score(0), life(100), isDead(false)
{
}

Player::~Player()
{
}

Player* Player::getInstance()
{
    if (sSharedPlayer == nullptr)
    {
        sSharedPlayer = Player::create();
        return sSharedPlayer;
    }

    return sSharedPlayer;
}

void Player::destroy()
{
    if (sSharedPlayer != nullptr)
        sSharedPlayer.reset();
}

bool Player::isOnScene() const
{
    return getParent() != nullptr;
}

Player* Player::create()
{
    SpriteFrame* frame = sSpriteCache->getSpriteFrameByName("main_character/pcN.png");

    if (frame == nullptr)
        return nullptr;

    Player* sprite = new (std::nothrow) Player();

    if (sprite && sprite->initWithSpriteFrame(frame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


bool Player::initWithSpriteFrame(SpriteFrame* frame)
{
    if (!Sprite::initWithSpriteFrame(frame))
        return false;

    RefPtr<EventListenerKeyboard> listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(Curr_Class::onKeyPressed, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    setOrientation(Orientation::North);
    initKeyMoveArray();
    addPhysicShape();

    return true;
}

void Player::addPhysicShape()
{
    RefPtr<PhysicsBody> body = PhysicsBody::createBox(getContentSize()/2.f);

    if (body == nullptr)
        return;
    
    body->setGravityEnable(false);
    body->setTag(SpriteTags::PLAYER);
    body->setDynamic(false);

    auto* contactListener = EventListenerPhysicsContact::create();

    contactListener->onContactBegin = CC_CALLBACK_1(Curr_Class::onContactBegin, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->addComponent(body);

}

void Player::update(float dt)
{
    if (isDead)
        stopAllActions();

    Sprite::update(dt);
}

void Player::modHp(int8 const value)
{
    life += value;

    if (life <= 0)
        dead();
}

void Player::dead()
{
    isDead = true;

    SpriteFrame* deadSprite = sSpriteCache->
                            getSpriteFrameByName("main_character/pcDead.png");

    if (deadSprite == nullptr)
        return;

    setDisplayFrame(deadSprite);

    sAudioEngine->playEffect("dead-effect.mp3", false, 1.f, 1.f);
}

void Player::setOrientation(Orientation ori)
{
    orientation = ori;
}

Orientation Player::getOrientation() const
{
    return orientation;
}

void Player::initKeyMoveArray()
{
    keyMovement =
    {
        KeyForMoveInfo(EventKeyboard::KeyCode::KEY_LEFT_ARROW, Orientation::West),
        KeyForMoveInfo(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, Orientation::East),
        KeyForMoveInfo(EventKeyboard::KeyCode::KEY_UP_ARROW, Orientation::North),
        KeyForMoveInfo(EventKeyboard::KeyCode::KEY_DOWN_ARROW, Orientation::South)
    };
}

Animation* Player::getWalkAnimation(Orientation ori)
{
    Animation* anim = Animation::create();
    
    std::string walk("main_character/pcEWalk%i.png");
    std::string stand("main_character/pcE.png");

    switch (ori)
    {
        case Orientation::West:
        {
            walk[17] = 'W';
            stand[17] = 'W';
            break;
        }

        case Orientation::South:
        {
            walk[17] = 'S';
            stand[17] = 'S';
            break;
        }
        
        case Orientation::North:
        {
            walk[17] = 'N';
            stand[17] = 'N';
            break;
        }

        case Orientation::East:
        {
            walk[17] = 'E';
            stand[17] = 'E';
            break;
        }

        default : return nullptr;
    }

    for (int8 i = 1; i < 3; ++i)
    {
        String* path = String::createWithFormat(walk.c_str(), i);
        SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(path->getCString());

        if (frame != nullptr)
            anim->addSpriteFrame(frame);
    }

    SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(stand.c_str());

    if (frame != nullptr)
        anim->addSpriteFrame(frame);

    anim->setDelayPerUnit(1.f/10.f);
    anim->setRestoreOriginalFrame(true);

    return anim;
}

Animation* Player::getShootAnimation(Orientation ori)
{
    Animation* anim = Animation::create();
    
    std::string shoot("main_character/pcEShoot%i.png");
    std::string stand("main_character/pcE.png");

    switch (ori)
    {
        case Orientation::West:
        {
            shoot[17] = 'W';
            stand[17] = 'W';
            break;
        }

        case Orientation::South:
        {
            shoot[17] = 'S';
            stand[17] = 'S';
            break;
        }
        
        case Orientation::North:
        {
            shoot[17] = 'N';
            stand[17] = 'N';
            break;
        }

        case Orientation::East:
        {
            shoot[17] = 'E';
            stand[17] = 'E';
            break;
        }

        default : return nullptr;
    }

    for (int8 i = 1; i < 3; ++i)
    {
        String* path = String::createWithFormat(shoot.c_str(), i);
        SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(path->getCString());

        if (frame != nullptr)
            anim->addSpriteFrame(frame);
    }

    SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(stand.c_str());

    if (frame != nullptr)
        anim->addSpriteFrame(frame);

    anim->setDelayPerUnit(1.f/5.f);
    anim->setRestoreOriginalFrame(false);

    return anim;
}

void Player::shoot()
{
    Bullet* bullet = Bullet::create();

    if (bullet == nullptr)  
        return;

    Scene* curr_scene = getScene();

    if (curr_scene == nullptr)
        return;

    bullet->setOrientation(getOrientation());

    Vec2 bulletPos = getPositionAwayFrom(*this, getOrientation());

    bullet->setPosition(bulletPos);

    curr_scene->addChild(bullet);

    Animate* anim = Animate::create(getShootAnimation(getOrientation()));

    runAction(anim);

    sAudioEngine->playEffect("shoot.mp3", false, 1.f, 1.f);
}

void Player::onEnter()
{
    Sprite::onEnter();

    Scene* curr_scene = getScene();

    if (curr_scene == nullptr)
        return;

    switch (curr_scene->getTag())
    {
        case SceneTags::Entrance:
        {
            break;
        }

        case SceneTags::FinalStage:
        {
            Vec2 const Origin = sDirector->getVisibleOrigin();
            Size const & ScreenSize = sDirector->getVisibleSize();

            Vec2 tgt;

            tgt.x = ScreenSize.width * 0.15f + Origin.x;
            tgt.y = ScreenSize.height * 0.42f + Origin.y;

            runAction(MoveTo::create(12.f, tgt));

            break;
        }
    }
}

bool Player::onContactBegin(PhysicsContact & contact)
{
    return true;
}

void Player::debugPosition() const
{
    Vec2 pos = getPosition();
    Vec2 const origin = sDirector->getVisibleOrigin();
    Vec2 ScreenSize(sDirector->getVisibleSize().width + origin.x, sDirector->getVisibleSize().height + origin.y);

    std::cout << (pos.x * 100.f/ScreenSize.x) << ','<<(pos.y * 100.f/ScreenSize.y) << std::endl;
    std::cout << pos.x << ',' << pos.y << std::endl;
}

Vec2 Player::getDestByOrientation(Orientation ori)
{
    float x, y;

    switch (ori)
    {
        case Orientation::West:
        {
            x = getPosition().x - getContentSize().width * 0.1f;
            y = getPosition().y;
            break;
        }

        case Orientation::East:
        {
            x = getPosition().x + getContentSize().width * 0.1f; 
            y = getPosition().y;
            break;
        }

        case Orientation::North:
        {
            x = getPosition().x;
            y = getPosition().y + getContentSize().height * 0.1f;
            break;
        }

        case Orientation::South:
        {
            x = getPosition().x;
            y = getPosition().y - getContentSize().height * 0.1f;
            break;
        }

        default : return getPosition();
    }

    return Vec2(x, y);
}

void Player::moveToPoint(Vec2 const & tgt)
{
    MoveTo* move = MoveTo::create(0.5f, tgt);

    CallFuncN* stopAnim = CallFuncN::create(CC_CALLBACK_1(
        Curr_Class::onAnimationFinish, this, true));

    Sequence* seq = Sequence::create(move, stopAnim, nullptr);

    runAction(seq);
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
        shoot();

    KeyForMoveInfo* key = keyMovement.search_ptr([&keyCode] (KeyForMoveInfo & it) -> bool
    {
        return it.first == keyCode;
    });

    if (key == nullptr)
        return;

    stopAllActions();

    setOrientation(key->second);

    moveToPoint(getDestByOrientation(key->second));

    Animate* anim = Animate::create(getWalkAnimation(key->second));

    RepeatForever* repeat = RepeatForever::create(anim);

    runAction(repeat);
}

void Player::onAnimationFinish(Node* sender, bool cleanup)
{
    stopAllActions();
}
