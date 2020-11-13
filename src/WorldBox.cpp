#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/Flat.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Trade/MeshData.h>
#include "WorldBox.h"

WorldBox::WorldBox(Object3D* parent, SceneGraph::DrawableGroup3D* group) :
    Object3D{parent}, SceneGraph::Drawable3D{*this, group}
{
    using namespace Magnum::Math::Literals;
    _shader = Shaders::Flat3D();
    _shader.setColor(0xffff66_rgbf);
    _mesh = MeshTools::compile(Primitives::cubeWireframe());
    this->scale(_SCALING);
}

void WorldBox::draw(const Matrix4& transformation, SceneGraph::Camera3D& camera)
{
    _shader.setTransformationProjectionMatrix(camera.projectionMatrix() * transformation)
        .draw(_mesh);
}