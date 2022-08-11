cmake_minimum_required(VERSION 3.15)

project (hello)

set(CMAKE_CXX_STANDARD 20)
set(REALM_ENABLE_SYNC 1)

add_executable(hello main.cpp)
target_include_directories(hello PUBLIC /usr/local/include)
target_compile_definitions(hello PUBLIC REALM_DISABLE_METADATA_ENCRYPTION=1 REALM_ENABLE_SYNC=1 REALM_VERSION="0.0.1" REALM_NO_CONFIG=1 REALM_ENABLE_ASSERTIONS=1 REALM_ENABLE_ENCRYPTION=1)

find_library (
    REALM_CORE_LIB
    NAMES realm-dbg librealm-dbg
)
message(STATUS "REALM_CORE_LIB: [${REALM_CORE_LIB}]")

find_library (
    REALM_SYNC_LIB
    NAMES realm-sync-dbg librealm-sync-dbg
)
message(STATUS "REALM_SYNC_LIB: [${REALM_SYNC_LIB}]")

find_library (
    REALM_CORE_PARSER_LIB
    NAMES realm-parser-dbg librealm-parser-dbg
)
message(STATUS "REALM_CORE_PARSER_LIB: [${REALM_CORE_PARSER_LIB}]")

find_library (
    REALM_OBJECT_STORE_LIB
    NAMES realm-object-store-dbg librealm-object-store-dbg
)
message(STATUS "REALM_OBJECT_STORE_LIB: [${REALM_OBJECT_STORE_LIB}]")

find_library (
    CPP_REALM_LIB
    NAMES cpprealm libcpprealm
)
message(STATUS "CPP_REALM_LIB: [${CPP_REALM_LIB}]")

if(APPLE)
    target_link_libraries(hello "-lcompression" "-framework Foundation" "-framework Security")
endif()

target_link_libraries(hello ${CPP_REALM_LIB} ${REALM_OBJECT_STORE_LIB} ${REALM_SYNC_LIB} ${REALM_CORE_LIB} ${REALM_CORE_PARSER_LIB} z curl stdc++)

