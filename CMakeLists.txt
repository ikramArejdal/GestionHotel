cmake_minimum_required(VERSION 3.16)

project(GestionDeHotel VERSION 0.1 LANGUAGES CXX)

# Activer le support Qt Designer et MOC automatiquement
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver Qt6 Widgets et SQL
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# --- INCLUSION DES DOSSIERS ---
include_directories(
    database
    models
    views
    controllers
)

# --- LISTE DES FICHIERS SOURCES ---
set(PROJECT_SOURCES
    main.cpp
    views/LoginWindow.cpp
    views/LoginWindow.h
    views/LoginWindow.ui
    views/Dashboard.cpp
    views/Dashboard.h
    views/Dashboard.ui
    database/connexionDB.cpp
    database/connexionDB.h
    controllers/logincontroller.cpp
    controllers/logincontroller.h
    controllers/chambreController.cpp
    controllers/chambreController.h
    controllers/employeController.cpp
    controllers/employeController.h
    controllers/reservationController.cpp
    controllers/reservationController.h

    models/Chambre.h
    models/Employe.h
    models/Reservation.h
    views/EmployeView.cpp
    views/EmployeView.h
    views/EmployeView.ui
    views/ReservationView.cpp
    views/ReservationView.h 
    views/ReservationView.ui

    # Ajoute ici d'autres fichiers source si nécessaire
)

# --- CREATION DE L'EXECUTABLE ---
qt_add_executable(GestionDeHotel
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Lier l’exécutable avec Qt6 Widgets et SQL
target_link_libraries(GestionDeHotel PRIVATE
    Qt6::Widgets
    Qt6::Sql
)

# Pour Windows : supprimer la console noire
set_target_properties(GestionDeHotel PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# Finalisation pour Qt6
qt_finalize_executable(GestionDeHotel)
