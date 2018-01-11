//
// Created by app05 on 2018/1/11.
//




#include <http/server.hpp>


int main(){

    http::server ss("127.0.0.1", "4567");
    ss.registerConnectioncb([](http::connection_ptr con){
        http::reply rep;
        http::request req = con->getRequest();
        rep.headers.push_back({"Content-Length", std::to_string(req.body.size())});
        rep.body = req.body;

        con->postReply(rep);
    });
    ss.run();
    return 0;
}