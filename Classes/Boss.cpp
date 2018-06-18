# include "Boss.hpp"

Boss::Boss() : Sprite()
{

}

Boss::~Boss()
{

}

Boss* Boss::create()
{
    SpriteFrame* frame = sSpriteCache->getSpriteFrameByName("boss/boss1.png");

    if (frame == nullptr)
        return nullptr;

    Boss *sprite = new (std::nothrow) Boss();

    if (sprite && sprite->initWithSpriteFrame(frame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool Boss::initWithSpriteFrame(SpriteFrame* frame)
{
    if (!Sprite::initWithSpriteFrame(frame))
        return false;
    
    addAnimation();

    return true;
}

void Boss::onEnter()
{
    Sprite::onEnter();

    Vec2 const Origin = sDirector->getVisibleOrigin();
    Size const & ScreenSize = sDirector->getVisibleSize();

    Vec2 tgt;

    tgt.x = ScreenSize.width * 0.86f + Origin.x;
    tgt.y = ScreenSize.height * 0.82f + Origin.y;


    Sequence* seq = Sequence::create(DelayTime::create(10),MoveTo::create(2.f, tgt), NULL);

    runAction(seq);
}

void Boss::addAnimation()
{
    Animation* anim = Animation::create();

    for (size_t i = 1; i < 3; ++i)
    {
        String* path = String::createWithFormat("boss/boss%i.png", i);
        SpriteFrame* frame = sSpriteCache->getSpriteFrameByName(path->getCString());
        anim->addSpriteFrame(frame);
    }

    anim->setDelayPerUnit(1.f/ 5.f);
    anim->setRestoreOriginalFrame(true);

    RepeatForever* repeater = RepeatForever::create(Animate::create(anim));

    runAction(repeater);
}

void Boss::shoot()
{

}

