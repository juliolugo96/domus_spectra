# include "SharedDefines.hpp"

# ifndef ENTRANCE_SCENE_HPP
# define ENTRANCE_SCENE_HPP

using namespace cocos2d;

class Entrance : public Layer
{
    public:
        Entrance();
        ~Entrance();

        CREATE_FUNC(Entrance);

        static Scene* createScene();

        using Curr_Class = Entrance;

        bool init() override;
    
    private:
        void AddBackground();
        void AddPlayer();
};

# endif