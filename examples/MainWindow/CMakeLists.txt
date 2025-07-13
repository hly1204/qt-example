cmake_minimum_required(VERSION 3.21)

project(mainwindow VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Enable AUTO_MOC AUTO_UIC AUTO_RCC
qt_standard_project_setup()
qt_add_executable(mainwindow)

set_target_properties(mainwindow PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    WIN32_EXECUTABLE ON
    DEBUG_POSTFIX d
    # see: https://cmake.org/cmake/help/latest/policy/CMP0043.html#policy:CMP0043
    COMPILE_DEFINITIONS $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_compile_options(mainwindow PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_sources(mainwindow PRIVATE main.cc)
target_link_libraries(mainwindow PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

install(TARGETS mainwindow
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET mainwindow
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_TOOL_OPTIONS
        "--exclude-plugins qpdf"
        "--translations en,zh_CN"
)
install(SCRIPT ${deploy_script})