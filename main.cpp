#include <http/server.hpp>
#include <http/connection.hpp>

int main() {
    http::server s("127.0.0.1", "4567");
    s.registerConnectioncb([](http::connection_ptr con){
        const http::request req = con->getRequest();
        std::cout << "method " << req.method << std::endl;
        if(req.body.size() > 0){
            std::cout << "param " << req.body.data() << std::endl;
        }

    });
    s.run();
    return 0;
}