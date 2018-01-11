file(GLOB BOOST_LIBS "${BOOST_ROOT}/lib/*.a")
add_executable(base main.cpp)
target_link_libraries(base ${BOOST_LIBS} httpServer)