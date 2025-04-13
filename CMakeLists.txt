cmake_minimum_required(VERSION 3.21)

project(qt-example VERSION 0.0.0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
qt_add_executable(qt-example)
qt_add_resources(qt-example "icons"
    PREFIX "/icons"
    BASE ${PROJECT_SOURCE_DIR}/assets/google/material-design-icons
    FILES ${PROJECT_SOURCE_DIR}/assets/google/material-design-icons/close.svg
)

set_target_properties(qt-example PROPERTIES
    POSITION_INDEPENDENT_CODE True
    WIN32_EXECUTABLE True
    DEBUG_POSTFIX d
    COMPILE_DEFINITIONS_RELEASE QT_NO_DEBUG_OUTPUT
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_sources(qt-example PRIVATE
    main.cpp
    main_window.cpp
)

target_link_libraries(qt-example PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Svg
)

install(TARGETS qt-example
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET qt-example
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
