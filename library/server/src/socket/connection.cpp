//
// Created by nova on 2018/1/13.
//



#include "socket/connection.hpp"



namespace keepsocket{

    connection::connection(boost::asio::ip::tcp::socket socket, managerConn &manager)
    :m_socket(std::move(socket))
    ,m_manager(manager)
    ,m_func(nullptr)
    {

    }


    void connection::start() {
        auto self(shared_from_this());
        m_socket.async_receive(boost::asio::buffer(m_buffer), [self, this](boost::system::error_code error_code, std::size_t size){
            if(!error_code){
                if(m_func && m_buffer.size() > 0){
                    m_func(m_buffer, error_code);
                }
                else{
                    //TODO
                }
            }
            else{

            }
            start();
        });
    }

    void connection::stop() {

    }

    void connection::send(socket_buffer buffer) {
        m_socket.async_write_some(boost::asio::buffer(buffer), [](boost::system::error_code, std::size_t){

        });
    }

    void connection::receive(msgCallBack callBack) {
        m_func = callBack;
    }

    template <typename itBegin, typename itEnd>
    void connection::send(itBegin begin, itEnd end) {
        socket_buffer buffer;
        for(int i = 0; begin != end; ){
            buffer[i] = *begin;
            i++;
            begin++;
        }
        send(buffer);
    }

}