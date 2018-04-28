CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

#Project declaration
PROJECT(axion-core VERSION 0.0.1 DESCRIPTION "Core system")

#Include headers
INCLUDE_DIRECTORIES(../)

#Using std=c++14
SET(CMAKE_CXX_STANDARD 14)

#Export macro definition
ADD_DEFINITIONS(-AXION_CORE_EXPORT)

#Build library from sources
ADD_LIBRARY(
    ${PROJECT_NAME} SHARED
    Utility/ThreadPool.cpp
    Math/Math.cpp
)

#Install targets
INSTALL(
    TARGETS ${PROJECT_NAME}
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)