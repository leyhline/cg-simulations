#pragma once

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Pointer.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Types.h>
#include <Magnum/Math/Angle.h>
#include <Magnum/GL/Mesh.h>
#include "Particle.h"

using namespace Magnum;
using namespace Corrade;

typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;
typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;
typedef Math::Rad<Float> Rad;

class Game
{
    public:
        Game();
        void draw();
        void simulate(Float dt);
        void zoom(Float factor);
        void rotate(Rad angleX, Rad angleY);

    private:
        const UnsignedInt _NR_PARTICLES = 2000;
        Scene3D _scene;
        SceneGraph::DrawableGroup3D _drawableWorld;
        SceneGraph::DrawableGroup3D _drawableParticles;
        Shaders::Phong _shader;
        GL::Mesh _particleMesh;
        GL::Buffer _instanceBuffer;
        Containers::Pointer<Object3D> _cameraObject;
        Containers::Pointer<SceneGraph::Camera3D> _camera;
        Containers::Array<Containers::Pointer<Particle>> _particles {_NR_PARTICLES};
        Containers::Array<Particle::InstanceData> _instanceData {_NR_PARTICLES};
};