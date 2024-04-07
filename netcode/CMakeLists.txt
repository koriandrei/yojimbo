add_library(Yojimbo_netcode netcode.c)
target_include_directories(Yojimbo_netcode PUBLIC .)

target_link_libraries(Yojimbo_netcode PRIVATE Yojimbo_SodiumBuiltin)
