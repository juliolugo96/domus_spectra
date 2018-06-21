# ifndef ENTRANCE_SCENE_HPP
# define ENTRANCE_SCENE_HPP

# include "SharedDefines.hpp"
# include "ShadowLayer.hpp" 

using namespace cocos2d;

class Entrance : public Layer
{
    public:
        Entrance();
        ~Entrance();
        ShadowLayer* _shadowLayer;
        CREATE_FUNC(Entrance);

        static Scene* createScene();

        using Curr_Class = Entrance;
        void update(float dt) override;
        bool init() override;

    private:
        void AddBackground();
        void AddPlayer();
        void AddMedicalBox();


};

# endif