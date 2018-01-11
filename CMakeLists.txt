cmake_minimum_required(VERSION 3.9)
project(study)

set(CMAKE_CXX_STANDARD 14)

SET(BOOST_COMPONENTS)
LIST(APPEND BOOST_COMPONENTS thread
        date_time
        system
        filesystem
        program_options
        signals
        serialization
        chrono
        unit_test_framework
        context
        locale
        coroutine)
SET( Boost_USE_STATIC_LIBS ON CACHE STRING "ON or OFF" )
FIND_PACKAGE(Boost 1.60 REQUIRED COMPONENTS ${BOOST_COMPONENTS})


file(GLOB BOOST_LIBS "${BOOST_ROOT}/lib/*.a")
file(GLOB SOUCRES "include/http/*.hpp" "src/http/*.cpp" main.cpp)
include_directories("${BOOST_ROOT}/include")
include_directories(include/)
add_executable(study ${SOUCRES})
target_link_libraries(study ${BOOST_LIBS})


add_subdirectory("test")