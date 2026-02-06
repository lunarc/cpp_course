set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

add_executable(radio_checkbox
    mainwindow.h
    mainwindow.cpp
    main.cpp
)
target_include_directories(radio_checkbox PRIVATE ${EXPRTK_INCLUDE_DIRS})
target_link_libraries(radio_checkbox PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

set_target_properties(radio_checkbox PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

if(WIN32)
    add_custom_command(TARGET radio_checkbox POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:radio_checkbox>
    )
endif()

set_target_properties(
    radio_checkbox
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

