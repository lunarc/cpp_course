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
#message(${Qt5_FIND_COMPONENTS})

add_executable(drawing1
    drawing_kit.h
    drawing_kit.cpp
    render_area.h
    render_area.cpp
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

# resources.qrc

target_link_libraries(drawing1 Qt::Widgets Qt::Core Qt::Gui Qt::Qml Qt::Quick Qt::Charts)
