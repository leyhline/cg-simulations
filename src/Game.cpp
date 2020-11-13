#include <random>
#include <Magnum/GL/Buffer.h>
#include <Magnum/Shaders/Phong.h>
#include <Corrade/Containers/Pointer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Types.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Primitives/Icosphere.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Math/Color.h>
#include "Game.h"
#include "Particle.h"
#include "WorldBox.h"
#include "WorldFloor.h"

using namespace Magnum;
using namespace Corrade;

typedef Math::Vector3<Float> Vector3;

Game::Game()
{
    using namespace Magnum::Math::Literals;
    GL::Renderer::setClearColor(0x000000_rgbf);

    _cameraObject = Containers::pointer<Object3D>(&_scene);
    _cameraObject->translate(Vector3::zAxis(30.f));
    _camera = Containers::pointer<SceneGraph::Camera3D>(*_cameraObject);
    _camera->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
        .setProjectionMatrix(Matrix4::perspectiveProjection(35.0_degf, 4.0f/3.0f, 0.001f, 100.0f))
        .setViewport(GL::defaultFramebuffer.viewport().size());
    
    _shader = Shaders::Phong(Shaders::Phong::Flag::InstancedTransformation);
    _shader.setAmbientColor(0x111111_rgbf)
           .setSpecularColor(0xff0000_rgbf)
           .setDiffuseColor(0x87ceeb_rgbf)
           .setLightPosition({10.0f, 15.0f, 5.0f});
    _particleMesh = MeshTools::compile(Primitives::icosphereSolid(1));
    _particleMesh.setInstanceCount(_NR_PARTICLES);
    _instanceBuffer = GL::Buffer{};
    _particleMesh.addVertexBufferInstanced(_instanceBuffer, 1, 0,
        Shaders::Phong::TransformationMatrix{},
        Shaders::Phong::NormalMatrix{});
    
    new WorldBox(&_scene, &_drawableWorld);
    new WorldFloor(&_scene, &_drawableWorld);
    std::default_random_engine gen(8872);
    std::uniform_real_distribution<Float> distMass(1.f, 10.f);
    std::normal_distribution<Float> distPos(0.f, 2.f);
    std::normal_distribution<Float> distVel(0.f, 4.f);
    for (UnsignedInt i = 0; i < _NR_PARTICLES; ++i)
    {
        Float mass = distMass(gen);
        Vector3 position = Vector3(distPos(gen), distPos(gen), distPos(gen));
        Vector3 velocity = Vector3(distVel(gen), distVel(gen), distVel(gen));
        Vector3 force = Vector3(0.f, 0.f, 0.f);
        _particles[i] = Containers::pointer<Particle>(&_scene, &_drawableParticles, _instanceData, i, mass, position, velocity, force);
    }
}

void Game::draw()
{
    GL::Renderer::disable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color|GL::FramebufferClear::Depth);
    _camera->draw(_drawableWorld);

    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
    _instanceBuffer.setData(_instanceData, GL::BufferUsage::DynamicDraw);
    _camera->draw(_drawableParticles);
    _shader.setTransformationMatrix(_camera->projectionMatrix())
        .draw(_particleMesh);
}

void Game::simulate(Float dt)
{
    for (UnsignedInt i = 0; i < _NR_PARTICLES; ++i)
    {
        _particles[i]->simulate(dt);
    }
}

void Game::zoom(Float factor)
{
    _cameraObject->translateLocal(Vector3::zAxis(factor));
}

void Game::rotate(Rad angleX, Rad angleY)
{
    _cameraObject->rotateX(angleX);
    _cameraObject->rotateY(angleY);
}