cmake_minimum_required(VERSION 3.0.0)
project(gbEmulator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)

aux_source_directory(src SRC_LIST)

add_executable(gbEmulator ${SRC_LIST})

target_link_libraries(gbEmulator ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)