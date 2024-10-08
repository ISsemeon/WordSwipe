cmake_minimum_required(VERSION 3.14)

project(WordSwipe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_INSTALL_PREFIX ${CMAKE_HOME_DIRECTORY}/install)

# Enable automatic handling of UI, MOC, and RCC files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to Qt installation (adjust if necessary)
# Conditionally set the path to Qt installation based on the operating system
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS
    set(CMAKE_PREFIX_PATH "/Users/semyon/Qt/6.4.0/macos")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Linux
    set(CMAKE_PREFIX_PATH "/home/simo/Qt/5.15.2/gcc_64")
endif()

# Find Qt libraries
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Qml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Qml)

# Define source files
set(PROJECT_SOURCES
    main.cpp
    qml.qrc
    models/folder.h
    models/folder.cpp
    models/FolderModel.cpp
    models/FolderModel.h
    models/CardsModel.h
    models/CardsModel.cpp
    models/ModuleModel.cpp
    models/ModuleModel.h
    models/module.h
    models/module.cpp
    models/card.h
    models/card.cpp
    models/DataController.cpp
    models/DataController.h
    models/SessionManager.cpp
    models/SessionManager.h
)

# Define the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(WordSwipe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(WordSwipe SHARED
            ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(WordSwipe
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link Qt libraries
target_link_libraries(WordSwipe
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Qml
)

# Set properties for macOS and Windows
set_target_properties(WordSwipe PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.mobility.wordSwipe
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    # Set this to your bundle identifier if needed
)

# Install targets
install(TARGETS WordSwipe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Finalize the executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(WordSwipe)
    qt_finalize_executable(WordSwipe)
endif()
