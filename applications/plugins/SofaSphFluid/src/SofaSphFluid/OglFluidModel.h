#ifndef OglFluidModel_H_
#define OglFluidModel_H_

#include <sofa/core/visual/VisualModel.h>
#include <sofa/helper/gl/FrameBufferObject.h>
#include <SofaOpenglVisual/OglModel.h>
#include <sofa/core/topology/BaseMeshTopology.h>
#include <sofa/core/behavior/MechanicalState.h>
#include <sofa/defaulttype/VecTypes.h>
#include <sofa/defaulttype/Vec3Types.h>
#include <SofaBaseTopology//TopologyData.inl>
#include <SofaOpenglVisual/OglVariable.h>

namespace sofa
{
namespace component
{
namespace visualmodel
{
using namespace sofa::defaulttype;
/**
 *  \brief Render volume using particles
 *
 */

// http://developer.download.nvidia.com/presentations/2010/gdc/Direct3D_Effects.pdf

template<class DataTypes>
class OglFluidModel : public core::visual::VisualModel
{
public:
    SOFA_CLASS(OglFluidModel, core::visual::VisualModel);
    //typedef ExtVec3fTypes DataTypes;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::Deriv Deriv;
    typedef typename DataTypes::VecDeriv VecDeriv;
    typedef typename DataTypes::Real Real;

private:
    topology::PointData< ResizableExtVector<Coord> > m_positions;
    ResizableExtVector<Coord> m_previousPositions;

    GLuint m_posVBO;
    helper::gl::FrameBufferObject* m_spriteDepthFBO;
    helper::gl::FrameBufferObject* m_spriteThicknessFBO;
    helper::gl::FrameBufferObject* m_spriteNormalFBO;
    helper::gl::FrameBufferObject* m_spriteBlurDepthHFBO;
    helper::gl::FrameBufferObject* m_spriteBlurDepthVFBO;
    helper::gl::FrameBufferObject* m_spriteShadeFBO;

    OglShader::SPtr m_spriteShader;
    OglShader::SPtr m_spriteNormalShader;
    OglShader::SPtr m_spriteBlurDepthShader;
    OglShader::SPtr m_spriteShadeShader;

    void drawSprites(const core::visual::VisualParams* vparams);
    void updateVertexBuffer();

    static const std::string PATH_TO_SPRITE_VERTEX_SHADER;
    static const std::string PATH_TO_SPRITE_FRAGMENT_SHADER;
    static const std::string PATH_TO_SPRITENORMAL_VERTEX_SHADER;
    static const std::string PATH_TO_SPRITENORMAL_FRAGMENT_SHADER;
    static const std::string PATH_TO_SPRITEBLURDEPTH_VERTEX_SHADER;
    static const std::string PATH_TO_SPRITEBLURDEPTH_FRAGMENT_SHADER;
    static const std::string PATH_TO_SPRITESHADE_VERTEX_SHADER;
    static const std::string PATH_TO_SPRITESHADE_FRAGMENT_SHADER;
protected:
    OglFluidModel();
    virtual ~OglFluidModel();
public:
    Data<unsigned int> d_debugFBO;
    Data<float> d_spriteRadius;
    Data<float> d_spriteThickness;
    Data<unsigned int> d_spriteBlurRadius;
    Data<float> d_spriteBlurScale;
    Data<float> d_spriteBlurDepthFalloff;
    Data<Vec4f> d_spriteDiffuseColor;


    void init();
    void initVisual();
    void fwdDraw(core::visual::VisualParams*);
    void bwdDraw(core::visual::VisualParams*);
    void drawVisual(const core::visual::VisualParams* vparams);
    void computeBBox(const core::ExecParams* params, bool onlyVisible = false);

    virtual void updateVisual();

    static std::string templateName(const OglFluidModel<DataTypes>* = NULL)
    {
        return DataTypes::Name();
    }

    virtual std::string getTemplateName() const
    {
        return templateName(this);
    }

};

}

}

}

#endif /*OglFluidModel_H_*/
