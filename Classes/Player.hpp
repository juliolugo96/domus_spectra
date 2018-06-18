# ifndef PLAYER_HPP
# define PLAYER_HPP

# include "SharedDefines.hpp"
# include <array.H>

using namespace cocos2d;
using namespace Designar;

using KeyForMoveInfo = std::pair<EventKeyboard::KeyCode, Orientation>;

class Player : public Sprite
{
    public:
        Player();
        ~Player();

        using Curr_Class = Player;

        uint8 getLife() const { return life; }
        Orientation getOrientation() const;

        static Player* create();
        static Player* getInstance();
        static void destroy();

        bool initWithSpriteFrame(SpriteFrame* /**/) override;
        
        void setOrientation(Orientation ori);
        void modHp(int8 const value);
        
        void shoot();
        bool isOnScene() const;
        void onEnter() override;
        void update(float  /**/) override;

    private:
        void onKeyPressed(EventKeyboard::KeyCode /**/, Event* /**/);
        void onAnimationFinish(Node* /**/, bool /**/);
        void debugPosition() const;

        void initKeyMoveArray();
        
        Animation* getWalkAnimation(Orientation /**/);
        Vec2 getDestByOrientation(Orientation /**/);
        void moveToPoint(Vec2 const & tgt);
        
        void dead();

        bool isDead;
        Orientation orientation;
        uint16 score;
        int8 life;

        DynArray<KeyForMoveInfo> keyMovement;

};


# endif