set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

add_executable(qt0
    mainwindow.h
    mainwindow.cpp
    main.cpp
)
target_link_libraries(qt0 PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

set_target_properties(qt0 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

if(WIN32)
    add_custom_command(TARGET qt0 POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:qt0>
    )
endif()

set_target_properties(
    qt0
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

