# ifndef PLAYER_HPP
# define PLAYER_HPP

# include "SharedDefines.hpp"
# include <array.H>
# include <list.H>
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

        void setOpenDoor(bool enable) { canUseDoor = enable; }
        void setExitOfRoom(bool enable) { isMovingToPrevRoom = enable; }
        void setEnterInScene(bool enter) { isEnterOnScene = enter; }
        void setMovingDisable(bool enable) { isDisabledMoving = enable; }
        void setOrientation(Orientation ori);
        void modHp(int8 const value);
        
        void shoot();
        void addDelayedOperation(CustomDelayedOperation const & /**/);
        bool isOnScene() const;
        bool onContactBegin(PhysicsContact & /**/);

        bool isMovingDisabled() const { return isDisabledMoving; }
        bool isEnterInScene() const { return isEnterOnScene; }
        bool isEnableForOpenDoor() const { return canUseDoor; }
        bool isExitOfRoom() const { return isMovingToPrevRoom; }
        
        void onEnter() override;
        void update(float  /**/) override;

    private:
        void onKeyPressed(EventKeyboard::KeyCode /**/, Event* /**/);
        void onKeyReleased(EventKeyboard::KeyCode /**/, Event* /**/);

        void onAnimationFinish(Node* /**/, bool /**/);
        void onInitialMoveFinish(Node* /**/, bool /**/);
        void debugPosition() const;

        void addPhysicShape();
        void initKeyMoveArray();
        void setStandSpriteFrame();

        void updateDelayedOperations(float /**/);
        
        Animation* getWalkAnimation(Orientation /**/);
        Animation* getShootAnimation(Orientation /**/);
        
        Vec2 getDestByOrientation(Orientation /**/);
        void moveToPoint(Vec2 const & tgt);
        
        void dead();
        void useEntrance();
        void useExit();

        bool isDead;
        bool canUseDoor;
        bool isEnterOnScene;
        bool isMovingToPrevRoom;
        bool isDisabledMoving;

        Vec2 backDest;
        Vec2 backInitPos;

        Orientation orientation;
        uint16 score;
        int8 life;

        DLList<CustomDelayedOperation> delayedOperations;
        DynArray<KeyForMoveInfo> keyMovement;
        
        std::map<EventKeyboard::KeyCode, TimePoint> keysPressed;
};


# endif