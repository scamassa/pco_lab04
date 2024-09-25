cmake_minimum_required(VERSION 3.13)
project(PCO_LAB02)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 COMPONENTS Core Gui Concurrent Widgets)
if (NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Concurrent Widgets REQUIRED)
endif()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE FORMS "ui/*.ui")

add_executable(pco_bogosort ${SOURCES} ${HEADERS} ${FORMS})

if (Qt5_FOUND)
    target_link_libraries(pco_bogosort PRIVATE Qt5::Core Qt5::Gui Qt5::Concurrent Qt5::Widgets -lpcosynchro)
else()
    target_link_libraries(pco_bogosort PRIVATE Qt6::Core Qt6::Gui Qt6::Concurrent Qt6::Widgets -lpcosynchro)
endif()