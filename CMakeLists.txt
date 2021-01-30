cmake_minimum_required(VERSION 3.16)
project(http)

set(Boost_INCLUDE_DIR /home/skamath/proactive/c++/boost/out/include/)
set(Boost_LIBRARY_DIR /home/skamath/proactive/c++/boost/out/include/lib/)
set(BOOST_ROOT /home/skamath/proactive/c++/boost/out/)
#set(BOOST_DIR /home/skamath/proactive/c++/boost/out/)

find_package(Boost 1.75.0 COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(http main.cpp)
TARGET_LINK_LIBRARIES( http LINK_PUBLIC ${Boost_LIBRARIES} pthread)