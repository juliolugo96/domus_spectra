# include "SharedDefines.hpp"
# include <array.H>

# ifndef PLAYER_HPP
# define PLAYER_HPP

using namespace cocos2d;
using namespace Designar;

enum class Orientation
{
    North,
    South,
    West,
    East,
};

using KeyCodeInfo = std::pair<EventKeyboard::KeyCode, Orientation>;

class Player : public Sprite
{
    public:
        Player();
        ~Player();

        using Curr_Class = Player;

        uint8 getLife() const { return life; }
        Orientation getOrientation() const;

        static Player* create();

        bool initWithFile(const std::string & fileName) override;
        
        void setOrientation(Orientation ori);
        void modHp(int8 const value);
        
        void moveToPoint(Vec2 const & tgt);
        void shoot();
    
    private:
        void onKeyPressed(EventKeyboard::KeyCode /**/, Event* /**/);
        void removeBullet(Node* /**/, bool /**/);

        Orientation orientation;
        uint16 score;
        int8 life;

        DynArray<KeyCodeInfo> keyMovement;
};

# endif