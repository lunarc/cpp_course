set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
#endif()

find_package(Qt6 COMPONENTS 3DCore 3DExtras 3DInput 3DRender Core Widgets Gui Qml Quick Qml Charts REQUIRED)

#message(${Qt5_FIND_COMPONENTS})

add_executable(qt3d1
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

# resources.qrc

target_link_libraries(qt3d1
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Charts
    Qt::3DCore
    Qt::3DExtras
    Qt::3DInput
    Qt::3DRender
)
