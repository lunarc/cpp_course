set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS 3DCore 3DExtras 3DInput 3DRender Core Widgets Gui Qml Quick Qml Charts REQUIRED)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS 3DCore 3DExtras 3DInput 3DRender Core Widgets Gui Qml Quick Qml Charts)
endif()

add_executable(qt3d1
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

target_link_libraries(qt3d1
    Qt::Widgets
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::Charts
    Qt::3DCore
    Qt::3DExtras
    Qt::3DInput
    Qt::3DRender
)
