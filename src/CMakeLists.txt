cmake_minimum_required(VERSION 3.1)

add_subdirectory(bluenebula-crypto)

add_executable(bluenebula-auth main.cpp)
target_link_libraries(bluenebula-auth PUBLIC bluenebula-crypto)
set_target_properties(bluenebula-auth PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
