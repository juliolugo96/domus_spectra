# ifndef SHARED_DEFINES_HPP
# define SHARED_DEFINES_HPP

# include "cocos2d.h"
# include "audio/include/SimpleAudioEngine.h"
# include <iostream>

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
    FinalStage,
};

enum SpriteTags
{
    PLAYER  = 10,
    MEDICALBOX,
    AMMUNITION,
    ENEMY,
    BOSS
};

using uint8 = uint8_t;
using int8 = int8_t;
using uint16 = uint16_t;

# include "Player.hpp"

static cocos2d::Director* const & sDirector = cocos2d::Director::getInstance();
static cocos2d::SpriteFrameCache* const & sSpriteCache = cocos2d::SpriteFrameCache::getInstance();
static CocosDenshion::SimpleAudioEngine* const & sAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

# define sPlayer (Player::getInstance())

# endif
