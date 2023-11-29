set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Qml Quick Charts)

qt_standard_project_setup()

qt_add_executable(beam_app
    beam_app_resource.qrc
    calfem.h
    calfem.cpp
    beam_model.h
    beam_model.cpp
    beam_view.h
    beam_view.cpp
    result_table_model.h
    result_table_model.cpp
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

target_link_libraries(beam_app PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Charts)

set_target_properties(beam_app PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
