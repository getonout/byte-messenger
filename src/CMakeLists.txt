cmake_minimum_required(VERSION 3.5)

project(byte-messenger LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER /usr/lib/mxe/usr/bin/x86_64-w64-mingw32.static-gcc)
set(CMAKE_CXX_COMPILER /usr/lib/mxe/usr/bin/x86_64-w64-mingw32.static-g++)
set(QT_HOST_PATH /usr/lib/mxe/usr/x86_64-w64-mingw32.static/qt5/bin)
set(CMAKE_PREFIX_PATH /usr/lib/mxe/usr/x86_64-w64-mingw32.static/qt5/lib)

set(CMAKE_FIND_ROOT_PATH /usr/lib/mxe/usr/x86_64-w64-mingw32.static)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(Qt5_DIR "/usr/lib/mxe/usr/x86_64-w64-mingw32.static/qt5")
find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(byte-messenger SHARED
    basic-display-window.cpp
    basic-display-window.h
    basic-display-window.ui
    connection-window.cpp
    connection-window.h
    connection-window.ui
    main.cpp
    main-window.cpp
    main-window.h
    main-window.ui
    message.cpp
    message.h
    message-list.cpp
    message-list.h
    message-list-window.cpp
    message-list-window.h
    message-list-window.ui
    message-window.cpp
    message-window.h
    message-window.ui
    object-manager.cpp
    object-manager.h
    socket-routines.cpp
    socket-routines.h
    utilities.cpp
    utilities.h
    version.h
    version.cpp
  )
else()
  add_executable(byte-messenger.exe
    basic-display-window.cpp
    basic-display-window.h
    basic-display-window.ui
    connection-window.cpp
    connection-window.h
    connection-window.ui
    main.cpp
    main-window.cpp
    main-window.h
    main-window.ui
    message.cpp
    message.h
    message-list.cpp
    message-list.h
    message-list-window.cpp
    message-list-window.h
    message-list-window.ui
    message-window.cpp
    message-window.h
    message-window.ui
    object-manager.cpp
    object-manager.h
    socket-routines.cpp
    socket-routines.h
    utilities.cpp
    utilities.h
    version.h
    version.cpp
  )
endif()

target_compile_definitions(byte-messenger.exe PRIVATE WIN_BUILD)


target_link_libraries(byte-messenger.exe PRIVATE Threads::Threads Qt5::Widgets)

