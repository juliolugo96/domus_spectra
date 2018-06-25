# include "QuizScene.hpp"

QuizScene::QuizScene()
{
    
}

QuizScene::~QuizScene()
{

}

Scene* QuizScene::createScene()
{
    RefPtr<Scene> main_screen = Scene::create();

    RefPtr<Layer> main_layer = QuizScene::create();

    if (main_screen == nullptr or main_layer == nullptr)
        return nullptr;

    main_layer->setTag(SpriteTags::LAYER);
    main_screen->setTag(SceneTags::Quiz);

    main_screen->addChild(main_layer);

    return main_screen;
}

bool QuizScene::init()
{
    if (!Layer::init())
        return false;

    addBackground();
    addMenu();

    return true;
}

void QuizScene::addBackground()
{
    RefPtr<Sprite> background = Sprite::createWithSpriteFrameName("riddle.png");

    if (background == nullptr)
        return;

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    background->setPosition(CenterPos);

    this->addChild(background);
}

void QuizScene::showQuiz()
{
    if (quizBg == nullptr)
        quizBg = Sprite::createWithSpriteFrameName("quizBg.png");
    else
    {
        if (!quizBg->isVisible())
            quizBg->setVisible(true);
        else
            quizBg->setVisible(false);

        return;
    }

    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();

    Vec2 const CenterPos = { ScreenSize.width/2 + Origin.x, 
                            ScreenSize.height/2 + Origin.y };

    quizBg->setPosition(CenterPos);

    this->addChild(quizBg);

    quizBg->setVisible(true);
}

void QuizScene::addMenu()
{
    Size const ScreenSize = sDirector->getVisibleSize();
    Vec2 const Origin = sDirector->getVisibleOrigin();
    
    Vec2 const menuPos = { ScreenSize.width/2 + Origin.x, 
                             ScreenSize.height * 0.125f + Origin.y };

     
    RefPtr<Label> backLabel = Label::createWithTTF("Exit", 
                                                    "fonts/Marker Felt.ttf", 18);

    RefPtr<Label> clueLabel = Label::createWithTTF("Get a Clue for Boss Door", 
                                                    "fonts/Marker Felt.ttf", 18);

    RefPtr<MenuItemLabel> backItem = MenuItemLabel::create(clueLabel, 
                                CC_CALLBACK_1(Curr_Class::onCluePressed, this));

    RefPtr<MenuItemLabel> clueItem = MenuItemLabel::create(backLabel, 
                                CC_CALLBACK_1(Curr_Class::onBackPressed, this));
    
    RefPtr<Menu> main_menu = Menu::create(backItem.get(), clueItem.get(), NULL);

    main_menu->setPosition(menuPos);

    this->addChild(main_menu);
    
}

void QuizScene::onBackPressed(Ref* /**/)
{
    sDirector->popScene();
}

void QuizScene::onCluePressed(Ref* /**/)
{
    showQuiz();
}