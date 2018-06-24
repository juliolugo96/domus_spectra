# ifndef SHARED_DEFINES_HPP
# define SHARED_DEFINES_HPP

# include "cocos2d.h"
# include "audio/include/SimpleAudioEngine.h"
# include <iostream>
# include "2d/CCLight.h"
# include "CocosGUI.h"

enum class Orientation
{
    North,
    South,
    West,
    East,
};

enum SceneTags
{
    Entrance = 10,
    Hall,
    Aisle,
    FinalStage,
};

enum SpriteTags
{
    PLAYER  = 10,
    MEDICALBOX,
    BULLET,
    AMMUNITION,
    ENEMY,
    BOSS
};

enum ActionTags
{
    MOVEMENT = 10,
    ANIMATE,
};

using uint8 = uint8_t;
using uint32 = uint32_t;
using int8 = int8_t;
using uint16 = uint16_t;

# include "Player.hpp"

static cocos2d::Director* const & sDirector = cocos2d::Director::getInstance();
static cocos2d::SpriteFrameCache* const & sSpriteCache = cocos2d::SpriteFrameCache::getInstance();
static CocosDenshion::SimpleAudioEngine* const & sAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

# define sPlayer (Player::getInstance())


static cocos2d::Vec2 getPositionAwayFrom(cocos2d::Node& src, Orientation ori)
{
    cocos2d::Vec2 ret;
    cocos2d::Vec2 origin = src.getBoundingBox().origin;

    switch (ori)
    {
        case Orientation::North:
        {
            ret.y = origin.y + src.getContentSize().height * 1.12f;
            ret.x = src.getPosition().x;
            break;
        }

        case Orientation::South:
        {
            ret.y = origin.y - src.getContentSize().height * 0.15f;
            ret.x = src.getPosition().x;
            break;
        }

        case Orientation::East:
        {
            ret.x = origin.x + src.getContentSize().width * 1.12f;
            ret.y = src.getPosition().y;
            break;
        }

        case Orientation::West:
        {
            ret.x = origin.x - src.getContentSize().height * 0.15f;
            ret.y = src.getPosition().y;
            break;
        }

        default : break;
    }

    return ret;
}

# endif
