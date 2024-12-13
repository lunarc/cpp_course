set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (LINUX)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(sliders_spin
        mainwindow.h
        mainwindow.cpp
        main.cpp
    )

    target_link_libraries(progress_bar PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
else()
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

    qt_standard_project_setup()

    add_executable(progress_bar
        mainwindow.h
        mainwindow.cpp
        main.cpp
    )
    target_include_directories(progress_bar PRIVATE ${EXPRTK_INCLUDE_DIRS})
    target_link_libraries(progress_bar PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

    set_target_properties(progress_bar PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )

    add_custom_command(TARGET progress_bar POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:progress_bar>
    )
endif()

set_target_properties(
    progress_bar
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

