include_directories(../shared ../platform/include 3rdParty)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC_GUI TopBar.cpp
        AboutDialog.cpp
        AboutFile.cpp
        LayoutViewer.cpp
        KeyboardWidget.cpp
        SettingsDialog.cpp
        ToggleSwitch.cpp
        AutoCorrectDialog.cpp
        images.qrc)

set(SRC_MAIN main.cpp
        Layout.cpp
        LayoutConverter.cpp
        LayoutConverter.h
        SingleInstance.cpp
        AvroPhonetic.cpp
        PlatformConfig.cpp)

set(LINK_LIBS libShared Qt5::Widgets Qt5::Network Qt5::Svg platform)

if(OS_LINUX)
    list(APPEND LINK_LIBS ${ZSTD_LIBRARIES})
endif(OS_LINUX)

add_executable(kholabangla-gui ${SRC_MAIN} ${SRC_GUI})

target_link_libraries(kholabangla-gui ${LINK_LIBS})

if(OS_LINUX)
    install(TARGETS kholabangla-gui
        RUNTIME DESTINATION ${BIN_DIR})
endif()
