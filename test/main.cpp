//
// Created by app05 on 2018/1/11.
//




#include <socket/server.hpp>
#include <socket/connection.hpp>
int main(){
    
    keepsocket::server ss("127.0.0.1", "4567");
    ss.registMsgCallBack([](keepsocket::connection_ptr con ){
        std::cout << "keepsocket::connection_ptr \n";
        con->receive([](keepsocket::socket_buffer buffer, boost::system::error_code error_code){
            if(buffer.size() > 0 && !error_code){
                std::cout << buffer.data() << std::endl;
            }
        });
    });
    ss.start();

    return 0;
}