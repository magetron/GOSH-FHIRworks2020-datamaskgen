set(JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/json/include PARENT_SCOPE)
set(CATCH2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include PARENT_SCOPE)

set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")
set(JSON_BuildTests OFF CACHE INTERNAL "Don't build json tests")

find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()

include(Catch2/contrib/ParseAndAddCatchTests.cmake)

add_subdirectory(json)
add_subdirectory(cpr)
add_subdirectory(Catch2)
add_subdirectory(argh)
add_subdirectory(spdlog)