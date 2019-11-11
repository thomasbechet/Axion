CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#Project declaration
PROJECT(axion-core LANGUAGES CXX VERSION 0.0.1)

#Include headers
INCLUDE_DIRECTORIES("../")
INCLUDE_DIRECTORIES("../../extlibs/STB/include/")
INCLUDE_DIRECTORIES("../../extlibs/TinyObjLoader/include/")
INCLUDE_DIRECTORIES("../../extlibs/RapidXML/include/")
INCLUDE_DIRECTORIES("../../extlibs/nlohmann/include/")

#Export macro definition
ADD_DEFINITIONS(-DAXION_CORE_EXPORT)

#Build library from sources
ADD_LIBRARY(
    ${PROJECT_NAME} SHARED
    Asset/AssetModule.cpp
    Asset/AssetLoader.cpp
    Asset/Asset.cpp
    Builder/AssetFactories.cpp
    Builder/ComponentFactories.cpp
    Builder/SystemFactories.cpp
    Context/ContextModule.cpp
    Context/Engine.cpp
    Content/System/BasicWindowSystem.cpp
    Content/System/BasicSpectatorSystem.cpp
    Content/System/RenderModeSystem.cpp
    Content/Component/TransformComponent.cpp
    Content/Component/CameraComponent.cpp
    Content/Component/BasicSpectatorComponent.cpp
    Content/Component/ModelComponent.cpp
    Content/Component/PointLightComponent.cpp
    Content/Component/DirectionalLightComponent.cpp
    Content/Component/CustomShapeComponent.cpp
    Content/Component/Shape/UVSphereShapeComponent.cpp
    Content/Component/Shape/RectangleShapeComponent.cpp
    Content/Component/Shape/QuadShapeComponent.cpp
    Content/Asset/Material.cpp
    Content/Asset/Mesh.cpp
    Content/Asset/Model.cpp
    Content/Asset/Package.cpp
    Content/Asset/Shader.cpp
    Content/Asset/Texture.cpp
    Content/Asset/Scene.cpp
    Renderer/Renderer.cpp
    Utility/ThreadPool.cpp
    Utility/Time.cpp
    Utility/Timer.cpp
    Utility/TimeRecorder.cpp
    Utility/Memory.cpp
    Utility/ConfigParser.cpp
    Utility/LibraryLoader.cpp
    Utility/Path.cpp
    Utility/Reference.cpp
    Input/InputModule.cpp
    Input/Button.cpp
    Input/Axis.cpp
    Logger/ThreadSafeLoggerModule.cpp
    Logger/ConsoleLoggerModule.cpp
    Math/Transform.cpp
    Math/Transform2D.cpp
    Math/Geometry/Shape.cpp
    Math/Geometry/Sphere.cpp
    Math/Geometry/UVSphere.cpp
    Math/Geometry/IcoSphere.cpp
    Math/Geometry/Rectangle.cpp
    Math/Geometry/Quad.cpp
    Scene/SceneModule.cpp
    Scene/GameMode/GameModeManager.cpp
    Scene/Entity/EntityManager.cpp
    Scene/Entity/Entity.cpp
    Scene/Component/Component.cpp
    Scene/Component/ComponentManager.cpp
    Scene/System/System.cpp
    Scene/System/SystemManager.cpp
)

#Adding pthread dependency
SET(THREADS_PREFER_PTHREAD_FLAG ON)
FIND_PACKAGE(Threads REQUIRED)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
    Threads::Threads
    "${CMAKE_DL_LIBS}"
)

#Install targets
INSTALL(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/bin"
)