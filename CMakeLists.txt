cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(potato-bulba
    VERSION 0.1.0
    LANGUAGES CXX
)

find_package(Threads REQUIRED)

include(GenerateExportHeader)

set(GENERATED_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(EXPORT_HEADER "${GENERATED_HEADERS_DIR}/bulba/export.hpp")

add_library(bulba-obj OBJECT
    include/bulba/greeting.hpp
    src/greeting.cpp
)
generate_export_header(bulba-obj
    BASE_NAME potato_bulba
    EXPORT_FILE_NAME "${EXPORT_HEADER}"
    INCLUDE_GUARD_NAME POTATO_BULBA_EXPORT_HEADER
)
target_include_directories(bulba-obj
    PUBLIC
        include
        "${GENERATED_HEADERS_DIR}"
)
set_target_properties(bulba-obj
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden
)
if(BUILD_SHARED_LIBS)
    set_target_properties(bulba-obj
        PROPERTIES
            POSITION_INDEPENDENT_CODE ON
    )
endif()

add_library(bulba
    $<TARGET_OBJECTS:bulba-obj>
)
add_library(potato::bulba ALIAS bulba)
target_include_directories(bulba
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${GENERATED_HEADERS_DIR}>
        $<INSTALL_INTERFACE:include>
)
set_target_properties(bulba
    PROPERTIES
        OUTPUT_NAME potato.bulba
        DEBUG_POSTFIX "-d"
        RELWITHDEBINFO_POSTFIX "-rd"
        MINSIZEREL_POSTFIX "-min"
)
target_link_libraries(bulba
    PRIVATE
        Threads::Threads
)

foreach(target IN ITEMS bulba-obj bulba)
    set_target_properties(${target}
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
    )
endforeach()


install(TARGETS bulba
    EXPORT potato-bulba-targets
    COMPONENT runtime
)

set(CONFIG_INSTALL_DIR lib/cmake/potato-bulba)

install(EXPORT potato-bulba-targets
    NAMESPACE potato::
    DESTINATION ${CONFIG_INSTALL_DIR}
    COMPONENT develop
)

set(CONFIG_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/potato-bulba-config.cmake")
set(VERSION_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/potato-bulba-config-version.cmake")

include(CMakePackageConfigHelpers)

configure_package_config_file(cmake/potato-bulba-config.cmake "${CONFIG_FILE_NAME}"
    INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}"
)
write_basic_package_version_file("${VERSION_FILE_NAME}"
    VERSION "${potato-bulba_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(DIRECTORY include/
    TYPE INCLUDE
    COMPONENT develop
)
install(DIRECTORY "${GENERATED_HEADERS_DIR}/"
    TYPE INCLUDE
    COMPONENT develop
)
install(
    FILES
        "${CONFIG_FILE_NAME}"
        "${VERSION_FILE_NAME}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
    COMPONENT develop
)
