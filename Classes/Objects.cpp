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

  auto* contactListener = EventListenerPhysicsContact::create();

  contactListener->onContactBegin = CC_CALLBACK_1(Curr_Class::onContactBegin, this);

  _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

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
