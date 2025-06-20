cmake_minimum_required(VERSION 3.5)

project(byte-messenger LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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

find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(byte-messenger
  ../src/basic-display-window.cpp
  ../src/basic-display-window.h
  ../src/basic-display-window.ui
  ../src/connection-window.cpp
  ../src/connection-window.h
  ../src/connection-window.ui
  ../src/main.cpp
  ../src/main-window.cpp
  ../src/main-window.h
  ../src/main-window.ui
  ../src/message.cpp
  ../src/message.h
  ../src/message-list.cpp
  ../src/message-list.h
  ../src/message-list-window.cpp
  ../src/message-list-window.h
  ../src/message-list-window.ui
  ../src/message-window.cpp
  ../src/message-window.h
  ../src/message-window.ui
  ../src/object-manager.cpp
  ../src/object-manager.h
  ../src/socket-routines.cpp
  ../src/socket-routines.h
  ../src/utilities.cpp
  ../src/utilities.h
  ../src/version.h
  ../src/version.cpp
)

target_link_libraries(byte-messenger PRIVATE Threads::Threads Qt5::Widgets)
