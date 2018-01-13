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
include_directories("${BOOST_ROOT}/include")
#add_executable(study ${SOUCRES})

include_directories("library/app/include")
include_directories("library/server/include")
include_directories("library/socketServer/socket/include")

##http server library
file(GLOB HTTP_LIB_SOUCRES "library/server/include/http/*.hpp" "library/server/src/http/*.cpp" )
add_library(httpServer ${HTTP_LIB_SOUCRES})
target_link_libraries(httpServer ${BOOST_LIBS})


##app library
file(GLOB APP_LIB_SOURCES "library/app/include/database/*.hpp" "library/app/src/database/*.cpp")
add_library(app  "${APP_LIB_SOURCES}")
target_link_libraries(app ${BOOST_LIBS})

##socket
file(GLOB SOCKET_LIB_SOURCES
        "library/server/include/socket/server.hpp.hpp"
        "library/server/include/socket/managerConnection.hpp"
        "library/server/include/socket/connection.hpp.hpp"
        "library/server/src/socket/*.cpp")
add_library(serverSocket  "${SOCKET_LIB_SOURCES}")
target_link_libraries(serverSocket ${BOOST_LIBS})



add_subdirectory("test")