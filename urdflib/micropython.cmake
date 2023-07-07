add_library(urdflib INTERFACE)

target_sources(urdflib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/middleware/terms.c
    ${CMAKE_CURRENT_LIST_DIR}/middleware/graph.c
    ${CMAKE_CURRENT_LIST_DIR}/urdflib.c
    ${CMAKE_CURRENT_LIST_DIR}/globals.c
    ${CMAKE_CURRENT_LIST_DIR}/terms.c
    ${CMAKE_CURRENT_LIST_DIR}/graph.c
)

target_include_directories(urdflib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(usermod INTERFACE urdflib)