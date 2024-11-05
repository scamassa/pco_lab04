cmake_minimum_required(VERSION 3.13)
project(PCO_LAB04_prog2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core Gui Test Widgets PrintSupport)
if (NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Test Widgets PrintSupport Core5Compat REQUIRED)
endif()

if (Qt5_FOUND)
    add_definitions(-DUSING_QT5)
else()
    add_definitions(-DUSING_QT6)
endif()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# Ajoutez les répertoires d'inclusion
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src)

# Liste des fichiers sources avec chemins complets
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sharedstation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/locomotive.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cppmain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/locomotivebehavior.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voie.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiedroite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiecourbe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voieaiguillage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiecroisement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voievariable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiebuttoir.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voietraverseejonction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/simview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/commandetrain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/loco.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/contact.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/segment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/trainsimsettings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/maquettemanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voieaiguillageenroule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voieaiguillagetriple.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/ctrain_handler.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sharedstation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sharedsectioninterface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/locomotive.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/launchable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/locomotivebehavior.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sharedsection.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voie.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiedroite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiecourbe.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voieaiguillage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiecroisement.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voievariable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voiebuttoir.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voietraverseejonction.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/simview.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/connect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/commandetrain.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/general.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/loco.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/contact.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/segment.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/trainsimsettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/maquettemanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voieaiguillageenroule.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/voieaiguillagetriple.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../QtrainSim/src/ctrain_handler.h
)

set(FORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/dialog.ui
)


#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../QtrainSim qtrainsim)


add_executable(PCO_LAB04_prog2 ${SOURCES} ${HEADERS})

if (Qt5_FOUND)
    target_link_libraries(PCO_LAB04_prog2 PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport -lpcosynchro)
else()
    target_link_libraries(PCO_LAB04_prog2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport Qt6::Core5Compat -lpcosynchro)
endif()

file(COPY ../../QtrainSim/data DESTINATION ${CMAKE_BINARY_DIR}/code/prog2)
file(COPY ../../QtrainSim/images DESTINATION ${CMAKE_BINARY_DIR}/code/prog2)
