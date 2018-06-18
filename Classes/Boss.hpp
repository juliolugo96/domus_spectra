#ifndef BOSS_HPP
#define BOSS_HPP

# include "SharedDefines.hpp"

using namespace cocos2d;

class Boss : public Sprite
{
    public:
        Boss();
        ~Boss();
        
        static Boss* create();

        bool initWithSpriteFrame(SpriteFrame* /**/) override;
        void onEnter() override;
        
    private:
        void shoot();
        void addAnimation();
};

# endif