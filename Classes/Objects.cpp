# include "Objects.hpp"

MedicalBox::MedicalBox(std::string const & name) : InteractableObject(name)
{

}

MedicalBox::~MedicalBox()
{

}

MedicalBox* MedicalBox::create()
{
  MedicalBox* sprite = new (std::nothrow) MedicalBox("various/First-Aid-Kit.png");

  if (sprite == nullptr)
    return nullptr;

  const char* fileName = sprite->getSpriteName().c_str();

  SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(fileName);

  if (sprite && sprite->initWithSpriteFrame(frame))
  {
      sprite->autorelease();
      return sprite;
  }

  CC_SAFE_DELETE(sprite);
  return nullptr;
}

bool MedicalBox::initWithSpriteFrame(SpriteFrame* frame)
{
  if (!Sprite::initWithSpriteFrame(frame))
    return false;

  PhysicsBody* boxShape = PhysicsBody::createBox(getContentSize());

  boxShape->setGravityEnable(false);
  boxShape->setTag(SpriteTags::MEDICALBOX);

  this->addComponent(boxShape);
  
  return true;
}

bool MedicalBox::onContactBegin(PhysicsContact & contact)
{
  PhysicsBody* owner = contact.getShapeA()->getBody();
  PhysicsBody* source = contact.getShapeB()->getBody();

  if (owner == nullptr || source == nullptr)
    return false;

  if (owner->getTag() == SpriteTags::MEDICALBOX && 
      source->getTag() == SpriteTags::PLAYER)
  {
        owner->getNode()->removeFromParentAndCleanup(true);
        return true;
  }

  return true;
}


Bullet::Bullet(std::string const & name) : InteractableObject(name)
{}

Bullet::~Bullet()
{}

Bullet* Bullet::create()
{
  Bullet* sprite = new (std::nothrow) Bullet("various/bullet.png");

  if (sprite == nullptr)
    return nullptr;

  const char* fileName = sprite->getSpriteName().c_str();

  SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(fileName);

  if (sprite && sprite->initWithSpriteFrame(frame))
  {
      sprite->autorelease();
      return sprite;
  }

  CC_SAFE_DELETE(sprite);
  return nullptr;
}

Vec2 Bullet::getDestByOrientation()
{
  Size const ScreenSize = sDirector->getVisibleSize();
  Vec2 const Origin = sDirector->getVisibleOrigin();

  float x, y;

  switch (getOrientation())
  {
      case Orientation::West:
      {
          x = Origin.x - getContentSize().width * 0.1;
          y = getPosition().y;
          break;
      }

      case Orientation::East:
      {
          x = Origin.x + ScreenSize.width + getContentSize().width * 0.1;
          y = getPosition().y;
          break;
      }

      case Orientation::North:
      {
          x = getPosition().x;
          y = Origin.y + ScreenSize.height + getContentSize().height * 0.1f;
          break;
      }

      case Orientation::South:
      {
          x = getPosition().x;
          y = Origin.y - getContentSize().height * 0.1f;
          break;
      }

      default : return getPosition();
  }

    return Vec2(x, y);
}

void Bullet::rotateByOrientation()
{
  float angle = 0;

  switch (getOrientation())
  {
    case Orientation::North:
    {
      angle = 270.f;
      break;
    }

    case Orientation::South:
    {
      angle = 90.f;
      break;
    }

    case Orientation::East:
    {
      angle = 360.f;
      break;
    }

    case Orientation::West:
    {
      angle = 180.f;
      break;
    }
  }

  if (angle != 0.f)
    setRotation(getRotation() + angle);
}

void Bullet::onEnter()
{
  InteractableObject::onEnter();
  
  rotateByOrientation();

  MoveTo* moveTo = MoveTo::create(random(0.25f, 0.50f), getDestByOrientation());

  CallFunc* dissapearOnLimit = CallFuncN::create(CC_CALLBACK_1(
                                        Curr_Class::onMoveFinished, this, true));

  runAction(Sequence::create(moveTo, dissapearOnLimit, nullptr));
}

void Bullet::onMoveFinished(Node* sender, bool cleanup)
{
  if (sender == nullptr)
    return;

  sender->removeFromParentAndCleanup(true);
}

bool Bullet::onContactBegin(PhysicsContact & /**/)
{
  return true;
}
