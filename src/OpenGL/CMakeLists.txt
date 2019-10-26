CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#Project declaration
PROJECT(axion-opengl LANGUAGES CXX VERSION 0.0.1)

#Include headers
INCLUDE_DIRECTORIES("../")
INCLUDE_DIRECTORIES("../../extlibs/GLEW/include/")

#Using std=c++17
SET(CMAKE_CXX_STANDARD 17)

#Export macro definition
ADD_DEFINITIONS(-DAXION_GL_EXPORT)
ADD_DEFINITIONS(-DGLEW_STATIC)

#Build library from sources
ADD_LIBRARY(
    ${PROJECT_NAME} SHARED
    ../../extlibs/GLEW/src/glew.c
    Loader/Loader.cpp
    Renderer/RendererModuleGL.cpp
    Renderer/Asset/RendererShaderGL.cpp
    Renderer/Asset/RendererMeshGL.cpp
    Renderer/Asset/RendererMaterialGL.cpp
    Renderer/Asset/RendererTextureGL.cpp
    Renderer/Scene/RendererStaticmeshGL.cpp
    Renderer/Scene/RendererCameraGL.cpp
    Renderer/Scene/RendererPointLightGL.cpp
    Renderer/Scene/RendererDirectionalLightGL.cpp
    Renderer/FrameBuffer/ForwardPlusBuffers.cpp
    Renderer/FrameBuffer/RenderBuffer.cpp
    Renderer/Buffer/ConstantsUBO.cpp
    Renderer/Buffer/MaterialUBO.cpp
    Renderer/Buffer/PointLightUBO.cpp
    Renderer/Buffer/DirectionalLightUBO.cpp
    Renderer/Buffer/CameraUBO.cpp
    Renderer/Buffer/ConstantsUBO.cpp
    Renderer/Buffer/CullLightSSBO.cpp
    Renderer/GUI/RendererGUIViewportGL.cpp
    Renderer/GUI/RendererGUILayoutGL.cpp
    Renderer/GUI/RendererGUIComponentGL.cpp
    Renderer/GUI/RendererGUIRectangleGL.cpp
    Renderer/GUI/RendererGUIScalableRectangleGL.cpp
    Renderer/Shader/ShaderGLSL.cpp
    Renderer/RenderPass/RenderPass.cpp
    Renderer/RenderPass/ForwardPlusPass.cpp
    Renderer/RenderPass/WireframePass.cpp
)

#Adding glfw dependency
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(MINGW)
        FIND_PACKAGE(OpenGL)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME}
           "${OPENGL_gl_LIBRARY}"
           "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/libaxion-core.dll.a"
        )
    else(MINGW)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME}
            
        )
    endif(MINGW)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}
        
    ) 
endif()

#Install targets
INSTALL(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/bin"
)

