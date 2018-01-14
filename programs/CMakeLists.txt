


add_executable(database "database/main.cpp")
include_directories("../library/server/include/")
target_link_libraries(database serverSocket)