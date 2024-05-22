cmake_minimum_required(VERSION 3.5)

project(ViewerV20 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH "/home/dorthava/Qt/6.6.1/gcc_64")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

add_subdirectory(third_party/QtGifImage)

set(PROJECT_SOURCES
        main.cc

        viewer/viewer_exception.h

        viewer/viewer_view.cc
        viewer/viewer_view.h
        viewer/viewer_controller.cc
        viewer/viewer_controller.h
        viewer/viewer_model.cc
        viewer/viewer_model.h
        viewer/observer/observer_inteface.h
        viewer/strategy/strategy.h
        viewer/strategy/strategy.cc

        viewer/openglview.h
        viewer/openglview.cpp

        ui/viewer_view.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ViewerV20
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ViewerV20 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ViewerV20 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ViewerV20
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(LINK_LIBRARIES
        QtGifImage::QtGifImage
        # Other link libraries, for example:
        Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(ViewerV20 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ViewerV20 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})
target_link_libraries(ViewerV20 PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(ViewerV20 PRIVATE Qt6::Gui)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ViewerV20)
endif()
set_target_properties(ViewerV20 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ViewerV20
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ViewerV20)
endif()
