CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#Project declaration
PROJECT(axion-core LANGUAGES CXX VERSION 0.0.1)

#Include headers
INCLUDE_DIRECTORIES("../")

#Using std=c++14
SET(CMAKE_CXX_STANDARD 14)

#Export macro definition
ADD_DEFINITIONS(-DAXION_CORE_EXPORT)

#Build library from sources
ADD_LIBRARY(
    ${PROJECT_NAME} SHARED
    Utility/ThreadPool.cpp
    Utility/Time.cpp
    Utility/Timer.cpp
    Utility/Color.cpp
    Math/Transform.cpp
    Math/Math.cpp
    Context/GameContext.cpp
)

#Adding pthread dependency
SET(THREADS_PREFER_PTHREAD_FLAG ON)
FIND_PACKAGE(Threads REQUIRED)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Threads::Threads)

#Install targets
INSTALL(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    LIBRARY DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../lib"
    RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../bin"
)