cmake_minimum_required(VERSION 3.16)

project(Customer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appCustomer
    main.cpp
)

qt_add_qml_module(appCustomer
    URI Customer
    VERSION 1.0
    QML_FILES Main.qml CustomButton.qml CloseButton.qml ReturnButton.qml
    RESOURCES Images.qrc Fonts.qrc
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCustomer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCustomer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCustomer
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appCustomer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
