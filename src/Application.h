#pragma once

#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Timeline.h>
#include <Magnum/Types.h>

#include "Game.h"

using namespace Magnum;

class Application : public Platform::Application
{
    public:
        explicit Application(const Arguments& arguments);

    private:
        void drawEvent() override;
        void mouseScrollEvent(MouseScrollEvent& event) override;
        void mouseMoveEvent(MouseMoveEvent& event) override;
        void keyReleaseEvent(KeyEvent& event) override;

        const Float _DT;
        Float _accumulator;
        Double _time;
        Timeline _timeline;
        Game _game;
        bool _paused;
};