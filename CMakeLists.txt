cmake_minimum_required(VERSION 3.14)

project(kcm_kosmos LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick)
find_package(KF5KCMUtils REQUIRED)
find_package(KF5ConfigWidgets REQUIRED)

add_library(kcm_kosmos_notifications MODULE kcm/kcm.cpp kcm/kcm.h)

target_link_libraries(kcm_kosmos_notifications
    Qt5::Core
    Qt5::Widgets
    Qt5::Quick
    KF5::KCMUtils
    KF5::ConfigWidgets
)

qt5_add_resources(KCM_KOSMOS_RESOURCES kcm/resource.qrc)
target_sources(kcm_kosmos_notifications PRIVATE ${KCM_KOSMOS_RESOURCES})

set_target_properties(kcm_kosmos_notifications PROPERTIES
    PREFIX ""              # remove "lib" prefix
    SUFFIX ".so"           # keep .so suffix
)

install(TARGETS kcm_kosmos_notifications
    DESTINATION lib/aarch64-linux-gnu/qt5/plugins/plasma/kcms/systemsettings
)

install(DIRECTORY kcm/contents/
    DESTINATION share/kpackage/kcms/kcm_kosmos_notifications/contents
)

install(PROGRAMS kosmos-notifications DESTINATION bin)
install(FILES kosmos-notifications.desktop DESTINATION /etc/xdg/autostart)
