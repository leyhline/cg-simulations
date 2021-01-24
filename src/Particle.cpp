#include <Magnum/Math/Color.h>
#include <Magnum/Math/Math.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Functions.h>
#include <Magnum/Math/Constants.h>
#include "Particle.h"

inline void Particle::handleBounds(Float dt)
{
    Float diffX = Math::abs(_position.x()) - BOUNDS;
    if (diffX > 0.f)
    {
        _velocity.x() *= -1.f;
        _position.x() = (_position.x() > 0) ? _position.x() - 2*diffX : _position.x() + 2*diffX;
        _previousPosition.x() = _position.x() - _velocity.x() * dt;
    }
    Float diffY = Math::abs(_position.y()) - BOUNDS;
    if (Math::abs(_position.y()) > Math::abs(BOUNDS))
    {
        _velocity.y() *= -1.f;
        _position.y() = (_position.y() > 0) ? _position.y() - 2*diffY : _position.y() + 2*diffY;
        _previousPosition.y() = _position.y() - _velocity.y() * dt;
    }
    Float diffZ = Math::abs(_position.z()) - BOUNDS;
    if (Math::abs(_position.z()) > Math::abs(BOUNDS))
    {
        _velocity.z() *= -1.f;
        _position.z() = (_position.z() > 0) ? _position.z() - 2*diffZ : _position.z() + 2*diffZ;
        _previousPosition.z() = _position.z() - _velocity.z() * dt;
    }
}

Particle::Particle(Object3D* parent, SceneGraph::DrawableGroup3D* group, Containers::Array<InstanceData>& instanceData, UnsignedInt instanceId,
                   Float mass, Vector3 position, Vector3 velocity, Vector3 force) :
    Object3D{parent}, SceneGraph::Drawable3D{*this, group}, _instanceId(instanceId),
    _mass(mass), _position(position), _previousPosition(position - velocity * (1.f/120.f)), _velocity(velocity), _force(force),
    _instanceData(instanceData)
{
    this->scale(_SCALING);
    this->_integrationScheme = Euler;
}

void Particle::draw(const Matrix4& transformation, SceneGraph::Camera3D&)
{
    const Matrix4 t = transformation * Matrix4::translation(_position * 2.5f);
    _instanceData[_instanceId] = InstanceData{t, t.normalMatrix()};
}

void Particle::simulate(Float dt)
{
    _force = Vector3(0.f, -1.f * _mass * 9.81f, 0.f);
    switch (_integrationScheme)
    {
        case Euler:
            _previousPosition = _position;
            _position += _velocity * dt;
            _velocity += _force / _mass * dt;
            break;
        case EulerCromer:
            _previousPosition = _position;
            _velocity += _force / _mass * dt;
            _position += _velocity *dt;
            break;
        case Verlet:
            Vector3 tempPosition = _position;
            _position = _position * 2 - _previousPosition + _force * dt * dt / _mass;
            _previousPosition = tempPosition;
            _velocity = (_position - _previousPosition) / dt;
            break;
    }
    handleBounds(dt);
}