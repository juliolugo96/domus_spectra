# ifndef AISLE_SCENE_HPP
# define AISLE_SCENE_HPP

# include "SharedDefines.hpp"
# include "Objects.hpp"

using namespace cocos2d;


class AisleScene : public Layer
{
    public:
        AisleScene();
        ~AisleScene();

        CREATE_FUNC(AisleScene);
        
        static Scene* createScene();

        bool init() override;

    private:
        void AddMedicalBoxes();
        void AddAmmunition();
};

# endif