CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

project(l4)

set(CMAKE_C_STANDARD 11)

add_executable(l4_cli cli.c interface.c logic.c list.c)
add_executable(l4_ui ui.c interface.c logic.c list.c)

add_library(l4_list_static STATIC list.c)
add_library(l4_logic_static STATIC logic.c)

add_library(l4_list_dynamic SHARED list.c)
add_library(l4_logic_dynamic SHARED logic.c)
target_link_libraries(l4_logic_dynamic l4_list_dynamic)

add_executable(l4_cli_static cli.c interface.c)
target_link_libraries(l4_cli_static l4_logic_static l4_list_static)

add_executable(l4_ui_dynamic ui.c interface.c)
target_link_libraries(l4_ui_dynamic l4_api_dynamic l4_list_dynamic)
