cmake_minimum_required(VERSION 2.8.4)
project(player2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    plugin/player2_dir/defines.h
    plugin/player2_dir/player2_dir.cpp
    plugin/player2_dir/player2_dir.h
    plugin/player2_help/defines.h
    plugin/player2_help/player2_help.cpp
    plugin/player2_help/player2_help.h
    plugin/player2_media_info/defines.h
    plugin/player2_media_info/player2_media_info.cpp
    plugin/player2_media_info/player2_media_info.h
    plugin/player2_playlist/defines.h
    plugin/player2_playlist/player2_playlist.cpp
    plugin/player2_playlist/player2_playlist.h
    plugin/player2_readme/defines.h
    plugin/player2_readme/player2_readme.cpp
    plugin/player2_readme/player2_readme.h
    plugin/player2_url/defines.h
    plugin/player2_url/player2_url.cpp
    plugin/player2_url/player2_url.h
    class_settings.cpp
    class_settings.h
    debug.h
    defines.h
    main.cpp
    settings_key.h
    settings_start_value.h
    typedefs.h
    widget.cpp
    widget.h)

add_executable(player2 ${SOURCE_FILES})