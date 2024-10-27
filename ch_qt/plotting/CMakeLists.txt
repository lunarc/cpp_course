set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(plotting
        mainwindow.ui
        mainwindow.cpp
        main.cpp
    )

    target_link_libraries(plotting PRIVATE Qt5::Widgets)
else()
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

    qt_standard_project_setup()

    qt_add_executable(plotting
    drawing_kit.h
    drawing_kit.cpp
    drawing_area.h
    drawing_area.cpp
    shape_drawing_area.h
    shape_drawing_area.cpp
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
    )
    target_link_libraries(plotting PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Charts)

    set_target_properties(plotting PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )

    add_custom_command(TARGET plotting POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:plotting>
    )
endif()

set_target_properties(
    plotting
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc


