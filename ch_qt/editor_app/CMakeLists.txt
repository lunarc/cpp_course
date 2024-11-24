set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(editor_app
        mainwindow.h
        mainwindow.cpp
        main.cpp
    )

    target_link_libraries(editor_app PRIVATE Qt5::Widgets)
else()
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

    qt_standard_project_setup()

    add_executable(editor_app
        mainwindow.cpp
        main.cpp
    )
    target_link_libraries(editor_app PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

    set_target_properties(editor_app PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )

    add_custom_command(TARGET editor_app POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:editor_app>
    )
endif()

set_target_properties(
    editor_app
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

