set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (LINUX)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(beam_app
    beam_app_resource.qrc
    logger.h
    logger.cpp
    output_redirector.h
    output_redirector.cpp
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

    target_link_libraries(beam_app PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
else()
    find_package(Qt6 COMPONENTS Widgets REQUIRED)

    qt_standard_project_setup()

    qt_add_executable(beam_app
    beam_app_resource.qrc
    beam_app_toolbar.qss
    beam_app_menus.qss
    custom_title_bar.h
    custom_title_bar.cpp
    calfem.h
    calfem.cpp
    beam_model.h
    beam_model.cpp
    beam_view.h
    beam_view.cpp
    result_table_model.h
    result_table_model.cpp
    output_redirector.h
    output_redirector.cpp
    logger.h
    logger.cpp
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp 
    )
    target_link_libraries(beam_app PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

    set_target_properties(beam_app PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )

    add_custom_command(TARGET beam_app POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:beam_app>
    )
endif()

set_target_properties(
    beam_app
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

set(CMAKE_CXX_STANDARD 17)  
