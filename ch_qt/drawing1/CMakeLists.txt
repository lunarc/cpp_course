set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

qt_add_executable(drawing1
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
target_link_libraries(drawing1 PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Charts)

set_target_properties(drawing1 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

if(WIN32)
    add_custom_command(TARGET drawing1 POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:drawing1>
    )
endif()

set_target_properties(
    drawing1
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc


