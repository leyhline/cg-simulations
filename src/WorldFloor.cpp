#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/Shaders/Flat.h>
#include <Magnum/Primitives/Grid.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Angle.h>
#include <Magnum/Math/Constants.h>
#include <Magnum/Types.h>
#include "WorldFloor.h"

typedef Math::Rad<Float> Rad;

WorldFloor::WorldFloor(Object3D* parent, SceneGraph::DrawableGroup3D* group) :
    Object3D{parent}, SceneGraph::Drawable3D{*this, group}
{
    using namespace Magnum::Math::Literals;
    _shader = Shaders::Flat3D();
    _shader.setColor(0xaa00aa_rgbf);
    _mesh = MeshTools::compile(Primitives::grid3DWireframe(Vector2i{100, 100}));
    this->scale(_SCALING)
        .rotateX(Rad(Math::Constants<Float>::piHalf()))
        .translate(Vector3::yAxis(-5.1f));
}

void WorldFloor::draw(const Matrix4& transformation, SceneGraph::Camera3D& camera)
{
    _shader.setTransformationProjectionMatrix(camera.projectionMatrix() * transformation)
        .draw(_mesh);
}