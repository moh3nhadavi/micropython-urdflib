add_library(urdflib INTERFACE)

target_sources(urdflib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/urdflib.c
)

target_include_directories(urdflib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(usermod INTERFACE urdflib)