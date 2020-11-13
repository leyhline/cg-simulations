#pragma once

#include <Corrade/Containers/Array.h>
#include <Magnum/Types.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Matrix3.h>

using namespace Magnum;

typedef Math::Vector3<Float> Vector3;
typedef Math::Matrix4<Float> Matrix4;
typedef Math::Matrix3x3<Float> Matrix3x3;
typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;

class Particle : public Object3D, public SceneGraph::Drawable3D
{
    public:
        enum Integration {
            Euler,
            EulerCromer,
            Heun,
            Verlet
        };

        struct InstanceData {
            Matrix4 transformation;
            Matrix3x3 normalMatrix;
        };


        Particle(Object3D* parent, SceneGraph::DrawableGroup3D* group, Containers::Array<InstanceData>& instanceData, UnsignedInt instanceId,
                 Float mass, Vector3 position, Vector3 velocity, Vector3 force);

        void draw(const Matrix4& transformation, SceneGraph::Camera3D& camera) override;
        void simulate(Float dt);

        static constexpr Float BOUNDS = 20.f;
        
    private:
        void handleBounds(Float dt);

        const Vector3 _SCALING = {0.1f, 0.1f, 0.1f};
        UnsignedInt _instanceId;
        Float _mass;
        Vector3 _position;
        Vector3 _previousPosition;
        Vector3 _velocity;
        Vector3 _force;
        Containers::Array<InstanceData>& _instanceData;
};