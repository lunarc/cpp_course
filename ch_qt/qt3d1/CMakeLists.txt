set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS REQUIRED Widgets Core Gui Qml 3DCore 3DExtras 3DInput 3DRender)

qt_standard_project_setup()

qt_add_executable(qt3d1
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

target_link_libraries(qt3d1 PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::3DCore
    Qt6::3DExtras
    Qt6::3DInput
    Qt6::3DRender
)

set_target_properties(qt3d1 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
