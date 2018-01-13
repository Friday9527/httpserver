file(GLOB BOOST_LIBS "${BOOST_ROOT}/lib/*.a")

#include_directories("../library/app/include")
#include_directories("../library/server/include")
include_directories("../library/server/include")
add_executable(base main.cpp)
#target_link_libraries(base ${BOOST_LIBS} httpServer)
target_link_libraries(base ${BOOST_LIBS} serverSocket)
