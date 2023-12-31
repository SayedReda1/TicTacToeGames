cmake_minimum_required(VERSION 3.5)

project(Games VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#======================= INCLUSION OF Qt =======================#
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/Forms")
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/Resources")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Src")

include_directories(${FORMS_DIR})
include_directories(${RESOURCE_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})


file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${RESOURCE_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
if (WIN32)
    add_executable(Games WIN32 ${SOURCES}


    )
elseif(UNIX)
    add_executable(Games ${SOURCES})
endif()

# Add the target includes for MY_PROJECT
target_include_directories(Games PRIVATE ${FORMS_DIR})
target_include_directories(Games PRIVATE ${INCLUDE_DIR})
target_include_directories(Games PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(Games Qt6::Widgets winmm)

