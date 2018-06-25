# include "Player.hpp"
# include "FinalScene.hpp"
# include "AisleScene.hpp"
# include "HallScene.hpp"
# include "HallLeftScene.hpp"
# include "HallRightScene.hpp"
# include "QuizScene.hpp"
# include "Objects.hpp"

static RefPtr<Player> sSharedPlayer = nullptr;

Player::Player() : Sprite(), score(0), life(100), isDead(false),
isMovingToPrevRoom(false), isDisabledMoving(false)
{
}

Player::~Player()
{
  delayedOperations.clear();
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
    listener->onKeyReleased = CC_CALLBACK_2(Curr_Class::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    setOrientation(Orientation::North);
    initKeyMoveArray();
    addPhysicShape();

    setTag(SpriteTags::PLAYER);

    this->scheduleUpdate();

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
    Sprite::update(dt);

    updateDelayedOperations(dt);

    if (isDead)
    {
        setSpriteFrame("main_character/pcDead.png");
        stopAllActions();
        keyMovement.clear();
        return;        
    }

    for (auto & it : keyMovement)
    {
        if (keysPressed.find(it.first) != keysPressed.end())
            onKeyPressed(it.first, nullptr);
    }
}

void Player::updateDelayedOperations(float dt)
{
  for (auto itr = delayedOperations.begin(); itr.has_current(); itr.next())
  {
    CustomDelayedOperation & op = itr.get_current();

    op.second -= dt;

    if (op.second <= 0)
    {
      op.first();
      itr.del();
    }
  }
}

void Player::addDelayedOperation(CustomDelayedOperation const & op)
{
  delayedOperations.append(op);
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
    stopAllActions();
    
    setSpriteFrame("main_character/pcDead.png");

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

    SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(stand.c_str());

    if (frame != nullptr)
        anim->addSpriteFrame(frame);

    for (int8 i = 1; i < 3; ++i)
    {
        String* path = String::createWithFormat(walk.c_str(), i);
        SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(path->getCString());

        if (frame != nullptr)
            anim->addSpriteFrame(frame);
    }

    anim->setDelayPerUnit(1.f/10.f);
    anim->setRestoreOriginalFrame(true);

    return anim;
}

void Player::setStandSpriteFrame()
{
    std::string stand("main_character/pcE.png");

    switch (getOrientation())
    {
        case Orientation::West:
        {
            stand[17] = 'W';
            break;
        }

        case Orientation::South:
        {
            stand[17] = 'S';
            break;
        }
        
        case Orientation::North:
        {
            stand[17] = 'N';
            break;
        }

        case Orientation::East:
        {
            stand[17] = 'E';
            break;
        }

        default : return;
    }

    SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(stand.c_str());

    if (frame != nullptr)
        setSpriteFrame(frame);
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

    if (isMovingDisabled())
        return;

    Scene* curr_scene = getScene();

    if (curr_scene == nullptr)
        return;

    Vec2 const Origin = sDirector->getVisibleOrigin();
    Size const & ScreenSize = sDirector->getVisibleSize();

    Vec2 tgt;
    Orientation next_ori;

    setEnterInScene(true);

    if (isExitOfRoom())
    {
      next_ori = getOrientation();
      setPosition(backInitPos);
      tgt = backDest;
    }
    else
    {
      switch (curr_scene->getTag())
      {
          case SceneTags::Entrance:
          {
              setEnterInScene(false);
              return;
          }

          case SceneTags::Aisle:
          {
              next_ori = Orientation::North;

              tgt = { ScreenSize.width * 0.5f + Origin.x, 
                      Origin.y + ScreenSize.height * 0.125f};

              break;
          }

          case SceneTags::Hall:
          {
              next_ori= Orientation::North;

              tgt = { ScreenSize.width/2 + Origin.x, 
                              ScreenSize.height * 0.15f + Origin.y };
              break;
          }

          case SceneTags::HallLeft:
          {
              next_ori = Orientation::West;

              tgt = { ScreenSize.width * 0.85f + Origin.x, 
                      Origin.y + ScreenSize.height * 0.5f};
              break;
          }

          case SceneTags::HallRight:
          {
              next_ori = Orientation::East;

              tgt = { ScreenSize.width * 0.125f + Origin.x, 
                      Origin.y + ScreenSize.height * 0.25f};

              break;
          }

          case SceneTags::FinalStage:
          {
              next_ori = Orientation::East;
              
              tgt.x = ScreenSize.width * 0.15f + Origin.x;
              tgt.y = ScreenSize.height * 0.42f + Origin.y;

              break;
          }

          default : return;
      }
    }

    MoveTo* move = MoveTo::create(1.25f, tgt);

    DelayTime* delay = DelayTime::create(1.5f);

    CallFunc* onMoveFinish = CallFuncN::create(CC_CALLBACK_1(
                            Curr_Class::onInitialMoveFinish, this, true));

    Animate* anim = Animate::create(getWalkAnimation(next_ori));

    RepeatForever* repeat = RepeatForever::create(anim);

    Sequence* seq = Sequence::create(delay, move, onMoveFinish, nullptr);

    runAction(repeat);
    
    runAction(seq);
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

    move->setTag(ActionTags::MOVEMENT);

    CallFuncN* stopAnim = CallFuncN::create(CC_CALLBACK_1(
        Curr_Class::onAnimationFinish, this, true));

    Sequence* seq = Sequence::create(move, stopAnim, nullptr);

    runAction(seq);
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (isEnterInScene())
        return;
    
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && !isDead)
    {
        shoot();
        return;        
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_P)
    {
        debugPosition();
        return;
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_B && isEnableForOpenDoor())
    {
        if (getScene() && getScene()->getTag() == SceneTags::Aisle &&
            getOrientation() == Orientation::North)
        {
            Scene* next_room = FinalScene::createScene();

            sDirector->replaceScene(TransitionFade::create(1.5f, next_room));
            return;
        }

        return;
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_O && isEnableForOpenDoor())
    {
        if (!isExitOfRoom())
            useEntrance();
        else
            useExit();
        return;
    }

    KeyForMoveInfo* key = keyMovement.search_ptr([&keyCode] (KeyForMoveInfo & it) -> bool
    {
        return it.first == keyCode;
    });

    if (key == nullptr)
        return;

    if (keysPressed.find(keyCode) == keysPressed.end())
        keysPressed[keyCode] = std::chrono::high_resolution_clock::now();

    setOrientation(key->second);

    moveToPoint(getDestByOrientation(key->second));

    if (getActionManager()->getActionByTag(ActionTags::ANIMATE, this) == nullptr)
    {
        Animate* anim = Animate::create(getWalkAnimation(key->second));

        RepeatForever* repeat = RepeatForever::create(anim);
        repeat->setTag(ActionTags::ANIMATE);        
        runAction(repeat);
    }
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* /**/)
{
    if (isEnterInScene())
        return;

    KeyForMoveInfo* key = keyMovement.search_ptr([&keyCode] (KeyForMoveInfo & it) -> bool
    {
        return it.first == keyCode;
    });

    if (key != nullptr)
    {
        stopAllActions();
        setStandSpriteFrame();
    }

    keysPressed.erase(keyCode);
}

void Player::onAnimationFinish(Node* sender, bool cleanup)
{
}

void Player::useEntrance()
{
    Scene* curr_scene = getScene();

    if (curr_scene == nullptr)
        return;

    switch (curr_scene->getTag())
    {
        case SceneTags::Entrance:
        {
            Scene* next_room = HallScene::createScene();
            sDirector->replaceScene(TransitionFade::create(1.5f, next_room));
            break;
        }

        case SceneTags::Aisle:
        {
            Scene* next_room = nullptr;

            if (getOrientation() == Orientation::South)
                next_room = HallScene::createScene();

            if (next_room != nullptr)
                sDirector->replaceScene(TransitionFade::create(1.5f, next_room));
            break;
        }

        case SceneTags::Hall:
        {
            Scene* next_room = nullptr;
            
            if (getOrientation() == Orientation::North)
                next_room = AisleScene::createScene();
            else if (getOrientation() == Orientation::West)
                next_room = HallLeftScene::createScene();
            else if (getOrientation() == Orientation::East)
                next_room = HallRightScene::createScene();
            
            if (next_room != nullptr)
                sDirector->replaceScene(TransitionFade::create(1.5, next_room));
            
            break;
        }

        case SceneTags::HallRight:
        {
          Scene* next_room = nullptr;

          if (getOrientation() == Orientation::West)
            next_room = HallScene::createScene();
          else
          {
            next_room = QuizScene::createScene();
            sDirector->pushScene(TransitionFade::create(1.5f, next_room));
            return;
          }

          if (next_room != nullptr)
            sDirector->replaceScene(TransitionFade::create(1.5f, next_room));

          break;
        }

        case SceneTags::HallLeft:
        {
            Scene* next_room = nullptr;

            if (getOrientation() == Orientation::East)
                next_room = HallScene::createScene();

            if (next_room != nullptr)
                sDirector->replaceScene(TransitionFade::create(1.5f, next_room));

            break;
        }

        default : break;
    }
}

void Player::useExit()
{
    Scene* scene = getScene();

    if (scene == nullptr)
        return;

    Vec2 const Origin = sDirector->getVisibleOrigin();
    Size const & ScreenSize = sDirector->getVisibleSize();

    switch (scene->getTag())
    {
      case SceneTags::HallRight:
      {
        backInitPos = { Origin.x + ScreenSize.width * 1.10f,
                        Origin.y + ScreenSize.height * 0.25f };

        backDest = {  Origin.x + ScreenSize.width * 0.95f,
                      Origin.y + ScreenSize.height * 0.25f };

        break;
      }

      case SceneTags::HallLeft:
      {
        backInitPos = { Origin.x - ScreenSize.width * 0.1f,
                        Origin.y + ScreenSize.height * 0.25f };

        backDest = {  Origin.x + ScreenSize.width * 0.15f,
                      Origin.y + ScreenSize.height * 0.25f };
        break;
      }

      case SceneTags::Aisle:
      case SceneTags::Hall:
      {
        backInitPos = { Origin.x + ScreenSize.width * 0.5f,
                        Origin.y + ScreenSize.height * 1.10f };

        backDest = {  Origin.x + ScreenSize.width * 0.5f,
                      Origin.y + ScreenSize.height * 0.85f };
        break;
      }

      default : break;
    }

    useEntrance();
}

void Player::onInitialMoveFinish(Node* sender, bool /**/)
{
    setExitOfRoom(false);
    setOpenDoor(false);
    setEnterInScene(false);
    stopAllActions();
    setStandSpriteFrame();
}
