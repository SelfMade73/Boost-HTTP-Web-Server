cmake_minimum_required(VERSION 3.16)
project(http_server)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_ROOT_DIR ./.. )

if(WIN32)
    add_definitions( -D_WIN32_WINNT=0x0601 )
endif()

add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DRAPIDJSON_HAS_STDSTRING=1)

set (RAPID_JSON_INCLUDE C:/Users/mi/Desktop/rapidjson/rapidjson/include)
set (BOOST_INCLUDE C:/boost_1_73_0/boost_1_73_0)

file ( GLOB SRC_ALL "${PROJECT_ROOT_DIR}/http_server/src/*.cpp" )
file ( GLOB INC_ALL "${PROJECT_ROOT_DIR}/http_server/include/*.h" )

include_directories(
        ${PROJECT_ROOT_DIR}
        ${RAPID_JSON_INCLUDE}
        ${BOOST_INCLUDE}
)
add_executable(http_server main.cpp ${INC_ALL} ${SRC_ALL} )