CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#Project declaration
PROJECT(axion-opengl LANGUAGES CXX VERSION 0.0.1)

#Include headers
INCLUDE_DIRECTORIES("../")
INCLUDE_DIRECTORIES("../../extlibs/GLEW/include/")

#Using std=c++14
SET(CMAKE_CXX_STANDARD 14)

#Export macro definition
ADD_DEFINITIONS(-DAXION_GL_EXPORT)
ADD_DEFINITIONS(-DGLEW_STATIC)

#Build library from sources
ADD_LIBRARY(
    ${PROJECT_NAME} SHARED
    ../../extlibs/GLEW/src/glew.c
    Loader/Loader.cpp
    Renderer/RendererGL.cpp
    Renderer/ShaderGL.cpp
    Renderer/MeshGL.cpp
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

