#include <server.hpp>


int main() {
    http::server s("127.0.0.1", "4567");
    s.run();
    return 0;
}