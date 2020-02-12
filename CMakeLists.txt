cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(potato-bulba
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include(GenerateExportHeader)

set(GENERATED_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(EXPORT_HEADER "${GENERATED_HEADERS_DIR}/bulba/export.hpp")

add_library(bulba-objects OBJECT
    include/bulba/greeting.hpp
    src/greeting.cpp
)
set_target_properties(bulba-objects
    PROPERTIES
        DEFINE_SYMBOL POTATO_BULBA_EXPORT_SYMBOL #before generate_export_header()
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
        POSITION_INDEPENDENT_CODE "${BUILD_SHARED_LIBS}"
)
generate_export_header(bulba-objects
    BASE_NAME potato_bulba
    EXPORT_FILE_NAME "${EXPORT_HEADER}"
    INCLUDE_GUARD_NAME POTATO_BULBA_EXPORT_HEADER
)
target_include_directories(bulba-objects
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${GENERATED_HEADERS_DIR}>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(bulba-objects
    PRIVATE
        Threads::Threads
)

add_library(bulba)
add_library(potato::bulba ALIAS bulba)
set_target_properties(bulba
    PROPERTIES
        OUTPUT_NAME potato-bulba
        DEBUG_POSTFIX "-d"
        RELWITHDEBINFO_POSTFIX "-rd"
        MINSIZEREL_POSTFIX "-min"
)
target_link_libraries(bulba
    PUBLIC
        bulba-objects
)


install(TARGETS bulba bulba-objects
    EXPORT potato-bulba-targets
    COMPONENT runtime
)

set(CONFIG_INSTALL_DIR lib/cmake/potato-bulba)

install(EXPORT potato-bulba-targets
    NAMESPACE potato::
    DESTINATION ${CONFIG_INSTALL_DIR}
    COMPONENT development
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
    COMPONENT development
)
install(DIRECTORY "${GENERATED_HEADERS_DIR}/"
    TYPE INCLUDE
    COMPONENT development
)
install(
    FILES
        "${CONFIG_FILE_NAME}"
        "${VERSION_FILE_NAME}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
    COMPONENT development
)
