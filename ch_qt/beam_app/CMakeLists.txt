set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
#endif()

find_package(Qt6 COMPONENTS Core Widgets Gui Qml Quick Qml Charts REQUIRED)

#message(${Qt5_FIND_COMPONENTS})

add_executable(beam_app
    beam_model.h
    beam_model.cpp
    beam_view.h
    beam_view.cpp
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

# resources.qrc

target_link_libraries(beam_app Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Charts)
