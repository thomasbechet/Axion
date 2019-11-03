CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#Project declaration
PROJECT(RuntimeTest LANGUAGES CXX VERSION 0.0.1)

#Include headers
INCLUDE_DIRECTORIES("../")

#Build executable
ADD_EXECUTABLE(
    ${PROJECT_NAME}
    main.cpp
)

#Link executable
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    axion-core
)

#Install targets
INSTALL(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/bin"
)