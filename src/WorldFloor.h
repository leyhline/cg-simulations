#pragma once

#include <Magnum/GL/Mesh.h>
#include <Magnum/Types.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Shaders/Flat.h>

using namespace Magnum;

typedef Math::Vector2<Int> Vector2i;
typedef Math::Vector3<Float> Vector3;
typedef Math::Matrix4<Float> Matrix4;
typedef Math::Matrix3x3<Float> Matrix3x3;
typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;

class WorldFloor : public Object3D, public SceneGraph::Drawable3D
{
    public:
        WorldFloor(Object3D* parent, SceneGraph::DrawableGroup3D* group);

        void draw(const Matrix4& transformation, SceneGraph::Camera3D& camera) override;

    private:
        const Float _SIZE = 100.f;
        const Vector3 _SCALING = {_SIZE, _SIZE, _SIZE};
        GL::Mesh _mesh;
        Shaders::Flat3D _shader;
};