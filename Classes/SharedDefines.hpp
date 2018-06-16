# include "cocos2d.h"
# include "audio/include/SimpleAudioEngine.h"
# include <iostream>


# ifndef SHARED_DEFINES_HPP
# define SHARED_DEFINES_HPP

static cocos2d::Director* const & sDirector = cocos2d::Director::getInstance();
static cocos2d::SpriteFrameCache* const & sSpriteCache = cocos2d::SpriteFrameCache::getInstance();
static CocosDenshion::SimpleAudioEngine* const & sAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
static cocos2d::Size const ScreenSize = sDirector->getVisibleSize();
static cocos2d::Vec2 const Origin = sDirector->getVisibleOrigin();
static cocos2d::Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, ScreenSize.height/2 + Origin.y };

using uint8 = uint8_t;
using int8 = int8_t;
using uint16 = uint16_t;


# endif
