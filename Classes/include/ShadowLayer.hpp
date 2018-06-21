# ifndef SHADOW_LAYER_HPP
# define SHADOW_LAYER_HPP

# include "SharedDefines.hpp"

using namespace cocos2d;

class ShadowLayer : public LayerColor 
{
  public:
    CREATE_FUNC(ShadowLayer);
    
    bool init() override;
    
    void setLightPosition(Point const & pos);
    void setLightSize(float size);
    
    void draw(Renderer* /**/, const Mat4 & /**/, uint32 /**/) override;

  private:
    GLProgram* _lightShaderProgram;
    Point _lightPosition;
    float _lightSize;
};

#endif