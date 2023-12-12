cmake_minimum_required(VERSION 3.16)

project(untitled14 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

set(SOURCE_FILES
    main.cpp
    src/databasemanager.cpp
    src/TableModel.cpp
    qml/qml.qrc
)
set(HEADER_FILES
    inc/databasemanager.h
    inc/TableModel.h
)
qt_add_executable(appuntitled14
    inc/databasemanager.h
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

qt_add_qml_module(appuntitled14
    URI untitled14
    VERSION 1.0
    QML_FILES qml/Main.qml
)
target_include_directories(appuntitled14
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
find_package(Qt6 COMPONENTS Sql REQUIRED)

target_link_libraries(appuntitled14 PRIVATE Qt6::Sql)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appuntitled14 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled14
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appuntitled14
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appuntitled14
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
