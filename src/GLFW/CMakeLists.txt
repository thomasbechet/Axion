CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#Project declaration
PROJECT(axion-glfw LANGUAGES CXX VERSION 0.0.1)

#Include headers
INCLUDE_DIRECTORIES("../")
INCLUDE_DIRECTORIES("../../extlibs/GLFW/include/")

#Using std=c++14
SET(CMAKE_CXX_STANDARD 14)

#Export macro definition
ADD_DEFINITIONS(-DAXION_GLFW_EXPORT)

#Build library from sources
ADD_LIBRARY(
    ${PROJECT_NAME} SHARED
    Window/WindowGLFW.cpp
    Input/InputGLFW.cpp
    Loader/Loader.cpp
)

#Adding glfw dependency
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
    "${CMAKE_CURRENT_SOURCE_DIR}/../../extlibs/GLFW/lib-mingw-w64/libglfw3.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/libaxion-core.dll.a"
)

#Install targets
INSTALL(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../bin"
)

