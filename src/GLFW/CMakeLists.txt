CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#Project declaration
PROJECT(axion-glfw LANGUAGES CXX VERSION 0.0.1)

#Include headers
INCLUDE_DIRECTORIES("../")
INCLUDE_DIRECTORIES("../../extlibs/GLFW/include/")

#Export macro definition
ADD_DEFINITIONS(-DAXION_GLFW_EXPORT)

#Build library from sources
ADD_LIBRARY(
    ${PROJECT_NAME} SHARED
    Window/WindowModuleGLFW.cpp
    Window/WrapperWindowModuleGLFW.cpp
    Input/InputModuleGLFW.cpp
    Input/WrapperInputModuleGLFW.cpp
    Loader/Loader.cpp
)

#Adding glfw dependency
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(MINGW)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME}
            "${CMAKE_CURRENT_SOURCE_DIR}/../../extlibs/GLFW/lib-mingw-w64/libglfw3.a"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/libaxion-core.dll.a"
        )
    else(MINGW)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME}
            "${CMAKE_CURRENT_SOURCE_DIR}/../../extlibs/GLFW/lib-linux/libglfw3.a"
            X11
            Xcursor  
            Xrandr 
            Xxf86vm
            Xinerama
            "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/libaxion-core.so"
        )
    endif(MINGW)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    TARGET_LINK_LIBRARIES(${PROJECT_NAME}
        "${CMAKE_CURRENT_SOURCE_DIR}/../../extlibs/GLFW/lib-vc2019/glfw3.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/axion-core.lib"
    )
endif()

#Install targets
INSTALL(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/bin"
)

