set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Widgets Gui Qml Quick Qml Charts)
else()
    find_package(Qt6 COMPONENTS Core Widgets Gui Qml Quick Qml Charts REQUIRED)
    if (NOT Qt6_FOUND)
        find_package(Qt5 5.15 REQUIRED COMPONENTS Core Widgets Gui Qml Quick Qml Charts)
    endif()
endif()

add_executable(qt7
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)

# resources.qrc

target_link_libraries(qt7 Qt::Widgets)
