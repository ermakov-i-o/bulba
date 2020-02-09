include(CMakeFindDependencyMacro)
find_dependency(Threads)

include("${CMAKE_CURRENT_LIST_DIR}/potato-bulba-targets.cmake")

@PACKAGE_INIT@
