# include "cocos2d.h"
# include "audio/include/SimpleAudioEngine.h"
# include <iostream>

static cocos2d::Director* const & sDirector = cocos2d::Director::getInstance();
static CocosDenshion::SimpleAudioEngine* const & sAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
static cocos2d::Size const ScreenSize = sDirector->getVisibleSize();
static cocos2d::Vec2 const Origin = sDirector->getVisibleOrigin();
static cocos2d::Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, ScreenSize.height/2 + Origin.y };

using uint8 = uint8_t;