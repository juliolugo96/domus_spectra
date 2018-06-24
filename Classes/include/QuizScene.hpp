# ifndef QUIZ_SCENE_HPP
# define QUIZ_SCENE_HPP

# include "SharedDefines.hpp"

using namespace cocos2d;

class QuizScene : public Layer
{
    public:
        QuizScene();
        ~QuizScene();

        CREATE_FUNC(QuizScene);

        static Scene* createScene();

        bool init() override;

        using Curr_Class = QuizScene;

    private:

        void addBackground();
        void addMenu();
        void showQuiz();

        void onCluePressed(Ref* /**/);
        void onBackPressed(Ref* /**/);

        RefPtr<Sprite> quizBg;        
};

# endif
