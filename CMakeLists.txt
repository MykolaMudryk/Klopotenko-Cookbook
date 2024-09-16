cmake_minimum_required(VERSION 3.14)

project(Cookbook LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Gui)

set(SOURCES
    src/main.cpp
)

if(ANDROID)
  set(CMAKE_ANDROID_API 23)

  set(CMAKE_ANDROID_ARCH_ABI "arm64-v8a")

  set(COOKBOOK_ICON "${CMAKE_CURRENT_SOURCE_DIR}/icons/platform_specific/cookbookAndroid.png")

  set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  message(STATUS "ANDROID_PACKAGE_SOURCE_DIR: ${ANDROID_PACKAGE_SOURCE_DIR}")

  set_source_files_properties(${COOKBOOK_ICON} PROPERTIES
      ANDROID_PACKAGE_SOURCE_DIR "res/drawable"
  )

qt_add_executable(Calculator MACOSX_BUNDLE
    ${SOURCES}
    ${COOKBOOK_ICON}
)

  set_target_properties(Cookbook PROPERTIES
      ANDROID_GUI TRUE
      OUTPUT_NAME "Cookbook"
      QT_ANDROID_PACKAGE_SOURCE_DIR "${ANDROID_PACKAGE_SOURCE_DIR}"
  )

  include(/Users/mac/Library/Android/sdk/android_openssl/CMakeLists.txt)
endif()

if(APPLE)
  set(CMAKE_OSX_BUNDLE TRUE)

  set(COOKBOOK_ICON "${CMAKE_CURRENT_SOURCE_DIR}/icons/platform_specific/cookbookMac.icns")

  set_source_files_properties(${COOKBOOK_ICON} PROPERTIES
      MACOSX_PACKAGE_LOCATION "Resources"
  )

  qt_add_executable(Cookbook MACOSX_BUNDLE
      ${SOURCES}
      ${COOKBOOK_ICON}
  )

  set_target_properties(Cookbook PROPERTIES
      MACOSX_BUNDLE TRUE
      MACOSX_BUNDLE_ICON_FILE "cookbookMac.icns"
      RESOURCE "${COOKBOOK_ICON}"
  )

endif()

qt_policy(SET QTP0001 NEW)

qt_add_qml_module(Cookbook
    URI Cookbook
    VERSION 1.0

        RESOURCES resources/qml.qrc
        RESOURCES resources/icons.qrc

)

target_include_directories(Cookbook PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Cookbook PRIVATE Qt6::Core Qt6::Quick Qt6::Gui)
