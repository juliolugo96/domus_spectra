# ifndef OBJECTS_HPP
# define OBJECTS_HPP

# include "SharedDefines.hpp"

using namespace cocos2d;

class InteractableObject : public Sprite
{
    public:
        InteractableObject(std::string const & fileName) : spriteName(fileName)
        {}

        ~InteractableObject() { /**/ }

        virtual bool onContactBegin(PhysicsContact & /**/) = 0;
        std::string const & getSpriteName() { return spriteName; }
    
    private:
        std::string spriteName;
};


class MedicalBox : public InteractableObject
{
    public:
        MedicalBox(std::string const & name);
        ~MedicalBox();

        using Curr_Class = MedicalBox;

        static MedicalBox* create();

        bool initWithSpriteFrame(SpriteFrame* /**/) override;

        bool onContactBegin(PhysicsContact & /**/) override;
};

class Bullet : public InteractableObject
{
    public:
        Bullet(std::string const & name);
        ~Bullet();

        using Curr_Class = Bullet;

        static Bullet* create();

        bool onContactBegin(PhysicsContact & /**/) override;

        Vec2 getDestByOrientation();

        Orientation getOrientation() const { return curr_ori; }

        void setOrientation(Orientation ori) { curr_ori = ori; }

        void onEnter() override;

        void onMoveFinished(Node* /**/, bool /**/);


    private:
        void rotateByOrientation();
                
        Orientation curr_ori;
};

# endif