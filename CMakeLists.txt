cmake_minimum_required(VERSION 3.16)

project(GestionDeHotel VERSION 0.1 LANGUAGES CXX)

# Activer le support Qt Designer automatiquement
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Charger Qt (Widgets + SQL)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# --- INCLUSION DES DOSSIERS ---
include_directories(
    database
    models
    views
    controllers
)

# --- LISTE DES FICHIERS ---
set(PROJECT_SOURCES
        main.cpp
        LoginWindow.cpp
        LoginWindow.h
        LoginWindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GestionDeHotel
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(GestionDeHotel ${PROJECT_SOURCES})
endif()

# Lier avec Qt
target_link_libraries(GestionDeHotel PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

# Pour Windows (enlève la console noire)
set_target_properties(GestionDeHotel PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# Finalisation pour Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GestionDeHotel)
endif()
