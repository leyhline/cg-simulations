#include <Magnum/Types.h>
#include <Magnum/Platform/Sdl2Application.h>

#include "Application.h"

using namespace Magnum;

Application::Application(const Arguments& arguments) :
    Magnum::Platform::Application{arguments, Configuration{}
        .setTitle("1 Particle Simulation")
        .setSize({800, 600})},
    _DT(1.f/120.f),
    _accumulator(0.f),
    _time(0.),
    _paused(false)
{
    setSwapInterval(1);
    _timeline.start();
}

void Application::drawEvent()
{
    Float duration = _timeline.previousFrameDuration();
    _accumulator += duration;
    while (!_paused && _accumulator >= _DT)
    {
        _game.simulate(_DT);
        _accumulator -= _DT;
        _time += _DT;
    }
    _game.draw();
    swapBuffers();
    redraw();
    _timeline.nextFrame();
}

void Application::mouseScrollEvent(MouseScrollEvent& event)
{
    _game.zoom(event.offset().y());
    event.setAccepted();
}

void Application::mouseMoveEvent(MouseMoveEvent& event)
{
    if (!(event.buttons() & MouseMoveEvent::Button::Left)) return;
    Vector2 delta = 3.0f*Vector2{event.relativePosition()}/Vector2{windowSize()};
    _game.rotate(
        Rad{delta.y()},
        Rad{delta.x()});
    event.setAccepted();
}

void Application::keyReleaseEvent(KeyEvent& event)
{
    if (!(event.key() == KeyEvent::Key::Space)) return;
    if (_paused)
    {
        _paused = false;
        _timeline.start();
    } else
    {
        _paused = true;
        _timeline.stop();
    }
    
    event.setAccepted();
}