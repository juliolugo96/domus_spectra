# ifndef PLAYER_HPP
# define PLAYER_HPP

# include "SharedDefines.hpp"
# include <array.H>
# include <map>

using namespace cocos2d;
using namespace Designar;

using TimePoint = std::chrono::high_resolution_clock::time_point;

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
        bool isEnableForOpenDoor() const { return canUseDoor; }

        void setOpenDoor(bool enable) { canUseDoor = enable; }
        void setOrientation(Orientation ori);
        void modHp(int8 const value);
        
        void shoot();
        bool isOnScene() const;
        bool onContactBegin(PhysicsContact & /**/);
        void onEnter() override;
        void update(float  /**/) override;

    private:
        void onKeyPressed(EventKeyboard::KeyCode /**/, Event* /**/);
        void onKeyReleased(EventKeyboard::KeyCode /**/, Event* /**/);

        void onAnimationFinish(Node* /**/, bool /**/);
        void debugPosition() const;

        void addPhysicShape();
        void initKeyMoveArray();
        
        Animation* getWalkAnimation(Orientation /**/);
        Animation* getShootAnimation(Orientation /**/);
        Vec2 getDestByOrientation(Orientation /**/);
        void moveToPoint(Vec2 const & tgt);
        
        void dead();
        void useEntrance();

        bool isDead;
        bool canUseDoor;
        Orientation orientation;
        uint16 score;
        int8 life;

        DynArray<KeyForMoveInfo> keyMovement;
        std::map<EventKeyboard::KeyCode, TimePoint> keysPressed;
};


# endif