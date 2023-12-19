cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(player2App LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CXX_STANDARD 17)

set(QT_PACKAGES Core Gui Qml Quick LinguistTools Multimedia MultimediaWidgets Widgets Core5Compat)
set(LINK_LIBS Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Widgets Qt6::Multimedia Qt6::Core5Compat)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
	qt_standard_project_setup()
endif()

set(SOURCES main.cpp
	src/settings/Settings.cpp
	src/shortcut/qglobalshortcut.cc)

set(RESOURCES resources/resources.qrc)

if(WIN32)
	list(APPEND SOURCES src/shortcut/qglobalshortcut_win.cc)
elseif(APPLE)
	list(APPEND SOURCES src/shortcut/qglobalshortcut_mac.cc)
elseif(UNIX)
	list(APPEND SOURCES src/shortcut/qglobalshortcut_x11.cc)
	list(APPEND QT_PACKAGES x11extras)
	list(APPEND LINK_LIBS X11 xcb)
endif()

find_package(Qt6 6.2 REQUIRED COMPONENTS ${QT_PACKAGES})

set(HEADERS
	src/plugins/PluginDir.h
	src/plugins/PluginHelp.h
	src/plugins/PluginMediaInfo.h
	src/plugins/PluginPlaylist.h
	src/plugins/PluginReadme.h
	src/plugins/PluginUrl.h
	src/settings/Settings.h
	src/settings/SettingsKey.h
	src/defines.h
	src/shortcut/qglobalshortcut.h)

qt6_add_resources(RCC_SOURCES ${RESOURCES})

qt_add_executable(player2App ${SOURCES} ${HEADERS})

qt_add_resources(player2App "configuration"
	PREFIX "/"
	FILES qtquickcontrols2.conf
)

qt_add_translations(player2App translate/uk_UA.ts 
	translate/en_US.ts)

target_include_directories(player2App PRIVATE src)

target_link_libraries(player2App PRIVATE ${LINK_LIBS})

if (BUILD_QDS_COMPONENTS)
	include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
	include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS player2App
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
	"Path to the custom QML components defined by the project")
