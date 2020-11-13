find_package(Corrade REQUIRED
    Main
    Utility
    Containers)
find_package(Magnum REQUIRED
    Sdl2Application
    SceneGraph
    GL
    Trade
    Primitives
    MeshTools)
find_package(MagnumIntegration REQUIRED
    ImGui)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(app
    app.cpp
    Application.cpp
    Game.cpp
    Particle.cpp
    WorldBox.cpp
    WorldFloor.cpp)

target_link_libraries(app PRIVATE
    Corrade::Main
    Corrade::Utility
    Corrade::Containers
    Magnum::Sdl2Application
    Magnum::SceneGraph
    Magnum::GL
    Magnum::Trade
    Magnum::Primitives
    Magnum::MeshTools
    MagnumIntegration::ImGui)