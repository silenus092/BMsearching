cmake_minimum_required(VERSION 3.5)
project(BMsearching)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
# For Mysql
include_directories(/home/note/Downloads/mysql-connector/include/)
add_library(libmysqlcppconn STATIC IMPORTED)
set_property(TARGET libmysqlcppconn PROPERTY IMPORTED_LOCATION /home/note/Downloads/mysql-connector/lib/libmysqlcppconn-static.a)


set(SOURCE_FILES
    src/BM.cpp
    src/BM.h
    src/BMsearching.cpp
    src/BMsearching.h
    src/Horspool.cpp
    src/Horspool.h src/HashMethod.cpp src/HashMethod.h)

add_executable(BMsearching ${SOURCE_FILES} )
#mysql too
target_link_libraries (BMsearching libmysqlcppconn)

target_link_libraries(BMsearching pthread)

target_link_libraries(BMsearching ${CMAKE_DL_LIBS})