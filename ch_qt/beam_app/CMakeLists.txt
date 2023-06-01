set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt6 COMPONENTS Core Widgets Gui Qml Quick Qml Charts REQUIRED)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Widgets Gui Qml Quick Qml Charts)
endif()

add_executable(beam_app
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

target_link_libraries(beam_app Qt::Widgets Qt::Core Qt::Gui Qt::Qml Qt::Quick Qt::Charts)
