cmake_minimum_required(VERSION 3.14)

project(Cookbook LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml Gui Network)

set(SOURCES
    main.cpp
)

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

    RESOURCES
        resources/qml.qrc
        resources/icons.qrc

    SOURCES
        main.cpp

        # Client files
        client/include/client.h
        client/include/network_client.h
        client/include/qml_handler.h

        client/src/client.cpp
        client/src/network_client.cpp
        client/src/qml_handler.cpp

        # Server files
        server/include/server.h
        server/include/request_handler.h
        server/include/database_handler.h
        server/include/qml_service.h

        server/src/server.cpp
        server/src/request_handler.cpp
        server/src/database_handler.cpp
        server/src/qml_service.cpp

        # Database files
        database/include/database.h
        database/include/query_builder.h
        database/include/connection.h

        database/src/database.cpp
        database/src/query_builder.cpp
        database/src/connection.cpp

        # Common files
        common/include/common.h
        common/include/json_parser.h
        common/include/utility.h

        common/src/json_parser.cpp
        common/src/utility.cpp
)


target_include_directories(Cookbook PRIVATE
    ${CMAKE_SOURCE_DIR}/client/include
    ${CMAKE_SOURCE_DIR}/server/include
    ${CMAKE_SOURCE_DIR}/database/include
    ${CMAKE_SOURCE_DIR}/common/include
)

target_link_libraries(Cookbook PRIVATE Qt6::Core Qt6::Quick Qt6::Gui Qt6::Network)
