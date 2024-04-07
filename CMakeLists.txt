project(Yojimbo)

add_subdirectory(sodium)

add_subdirectory(netcode)
add_subdirectory(reliable)
add_subdirectory(serialize)
add_subdirectory(tlsf)

# set(YOJIMBO_SOURCES "")

add_subdirectory(source)

list(TRANSFORM YOJIMBO_SOURCES PREPEND source/)

add_library(Yojimbo_Yojimbo ${YOJIMBO_SOURCES})
target_include_directories(Yojimbo_Yojimbo PUBLIC include)
target_include_directories(Yojimbo_Yojimbo PRIVATE .)

target_link_libraries(Yojimbo_Yojimbo PRIVATE Yojimbo_netcode Yojimbo_reliable Yojimbo_SodiumBuiltin tlsf)
target_link_libraries(Yojimbo_Yojimbo PUBLIC Yojimbo_serialize)

add_executable(Yojimbo_Client client.cpp)
add_executable(Yojimbo_Server server.cpp)
add_executable(Yojimbo_Soak soak.cpp)
add_executable(Yojimbo_Test test.cpp)

target_include_directories(Yojimbo_Client PRIVATE .)
target_include_directories(Yojimbo_Server PRIVATE .)

target_link_libraries(Yojimbo_Client PRIVATE Yojimbo_Yojimbo)
target_link_libraries(Yojimbo_Server PRIVATE Yojimbo_Yojimbo)
