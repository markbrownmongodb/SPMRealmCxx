cmake_minimum_required(VERSION 3.15)

project (SPMRealmCxx)

set(CMAKE_CXX_STANDARD 20)
set(REALM_ENABLE_SYNC 1)

# on Apple platforms we use the built-in CFRunLoop
# everywhere else it's libuv, except UWP where it doesn't build
if(NOT APPLE AND NOT WINDOWS_STORE)
    set(REALM_HAVE_UV 1)

    option(REALM_FETCH_MISSING_DEPENDENCIES "Download missing dependencies with CMake's FetchContent where possible" ON)
    if(REALM_FETCH_MISSING_DEPENDENCIES)
        find_package(LibUV)
    else()
        find_package(LibUV REQUIRED)
    endif()
    if(LibUV_FOUND)
        set(libuv_target LibUV::LibUV)
    elseif(REALM_FETCH_MISSING_DEPENDENCIES)
        message(STATUS "LibUV not found, building from source with FetchContent")
        include(FetchContent)
        set(libUV_Git_TAG "v1.35.0")
        if(MSVC)
            set(liUV_Git_TAG "v1.43.0")
        endif()
        FetchContent_Declare(
            libuv
            GIT_REPOSITORY https://github.com/libuv/libuv.git
            GIT_TAG ${libUV_Git_TAG}
        )
        FetchContent_Populate(libuv)
        add_subdirectory(${libuv_SOURCE_DIR} ${libuv_BINARY_DIR} EXCLUDE_FROM_ALL)
        set(libuv_target uv_a)
    endif()
    
    target_link_libraries(cpprealm ${libuv_target})
    get_property(libuv_include_dir TARGET ${libuv_target} PROPERTY INCLUDE_DIRECTORIES)

    target_compile_definitions(cpprealm PUBLIC REALM_DISABLE_METADATA_ENCRYPTION=1 REALM_ENABLE_SYNC=1)
    target_compile_definitions(ObjectStore PUBLIC REALM_HAVE_UV=1)
    target_include_directories(ObjectStore PRIVATE ${libuv_include_dir})

else()
    target_compile_definitions(cpprealm PUBLIC REALM_ENABLE_SYNC=1)
endif()


add_executable(SPMRealmCxx Sources/SPMRealmCxx/main.cpp Sources/SPMRealmCxx/event_loop.cpp Sources/SPMRealmCxx/event_loop.hpp)
target_include_directories(SPMRealmCxx PUBLIC /usr/local/include)
target_compile_definitions(SPMRealmCxx PUBLIC REALM_DISABLE_METADATA_ENCRYPTION=1 REALM_ENABLE_SYNC=1 REALM_VERSION="0.0.1" REALM_NO_CONFIG=1 REALM_ENABLE_ASSERTIONS=1 REALM_ENABLE_ENCRYPTION=1 REALM_HAVE_UV=1 REALM_PLATFORM_APPLE=0)

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
    target_link_libraries(SPMRealmCxx "-lcompression" "-framework Foundation" "-framework Security")
endif()

target_link_libraries(SPMRealmCxx ${CPP_REALM_LIB} ${REALM_OBJECT_STORE_LIB} ${REALM_SYNC_LIB} ${REALM_CORE_LIB} ${REALM_CORE_PARSER_LIB} z curl stdc++)


