cmake_minimum_required(VERSION 3.14)

project(WordSwipe VERSION 0.1 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt libraries
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Sql)

# Define source files
set(PROJECT_SOURCES
    main.cpp
    main.qml
    qml.qrc
    models/folder.h
    models/module.h
    models/card.h
    utils/database.cpp
    utils/database.h
    utils/exportimport.cpp
    utils/exportimport.h
)

# Define executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(app
        ${PROJECT_SOURCES}
    )
endif()

# Link Qt libraries
target_link_libraries(app
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql
)

# Set properties for macOS and Windows
set_target_properties(app PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install targets
install(TARGETS app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Finalize the executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(app)
    qt_finalize_executable(app)
endif()
