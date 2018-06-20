# include "Enemy.hpp"

Enemy::Enemy() : Sprite(), victim(nullptr)
{

}

Enemy::~Enemy()
{
    victim = nullptr;
}

Enemy* Enemy::create()
{
    SpriteFrame* frame = sSpriteCache->getSpriteFrameByName("enemyE1.png");

    if (frame == nullptr)
        return nullptr;

    Enemy *sprite = new (std::nothrow) Enemy();

    if (sprite && frame && sprite->initWithSpriteFrame(frame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool Enemy::initWithSpriteFrame(SpriteFrame* frame)
{
    if (!Sprite::initWithSpriteFrame(frame))
        return false;

    return true;
}

void Enemy::update(float dt)
{
    Sprite::update(dt);
}