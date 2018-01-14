//
// Created by nova on 2018/1/14.
//

#include <socket/server.hpp>
#include <socket/connection.hpp>
#include <boost/thread.hpp>

int main() {

    keepsocket::server ss("127.0.0.1", "4567");


    ss.registMsgCallBack([](keepsocket::connection_ptr con) {
        std::cout << "keepsocket::connection_ptr \n";
        std::cout << "thread id1" <<   boost::thread::physical_concurrency() << std::endl;
        con->receive([con](keepsocket::socket_buffer buffer, boost::system::error_code error_code) {
            if (buffer.size() > 0 && !error_code) {
                std::cout << buffer.data() << std::endl;
                std::cout << "thread id" <<   boost::thread::physical_concurrency() << std::endl;
            }
//
//            boost::thread([con]() {
//                int i = 0;
//                keepsocket::socket_buffer buffer;
//
//                std::string str("abcdef");
//                con->send(str.begin(), str.end());
//
//            });

        });
    });

    ss.start();

    return 0;
}