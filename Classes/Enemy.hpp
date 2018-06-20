# ifndef ENEMY_HPP
# define ENEMY_HPP

# include "SharedDefines.hpp"
# include "Player.hpp"

using namespace cocos2d;

class Enemy : public Sprite
{
    public:
        Enemy();
        ~Enemy();
        static Enemy* create();

        void update(float /**/) override;
        bool initWithSpriteFrame(SpriteFrame* /**/) override;

    private:

        Player* victim;
};

# endif