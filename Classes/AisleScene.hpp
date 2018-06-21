# ifndef AISLE_SCENE_HPP
# define AISLE_SCENE_HPP

using namespace cocos2d;

# include "SharedDefines.hpp"
# include "Objects.hpp"

class Aisle : public Layer
{
    public:
        Aisle();
        ~Aisle();

        static Scene* createScene();

        bool init() override;

    private:
        void AddMedicalBoxes();
        void AddAmmunition();
};

# endif