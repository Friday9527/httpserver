//
// Created by nova on 2018/1/13.
//

#ifndef STUDY_CONNECTION_HPP
#define STUDY_CONNECTION_HPP


#include <memory>
#include <boost/asio.hpp>
#include <iostream>
#include <array>
#include <functional>
//#include "managerConnection.hpp"

namespace keepsocket{

    class managerConn;

    typedef std::array<char, 2048> socket_buffer;

    typedef std::function<void(const socket_buffer, boost::system::error_code)> msgCallBack;

    class connection : public  std::enable_shared_from_this<connection>{
    public:
        connection(const connection &) = delete;
        connection &operator =(const connection &) = delete;

        explicit  connection(boost::asio::ip::tcp::socket socket, managerConn &manager);

        void start();
        void stop();

        void send(socket_buffer);

        void receive(msgCallBack callBack);

        template <typename itBegin, typename itEnd>
                void send(itBegin, itEnd);
    private:
        managerConn &m_manager;

        boost::asio::ip::tcp::socket m_socket;

        socket_buffer m_buffer;

        msgCallBack m_func;
    };


    typedef std::shared_ptr<connection> connection_ptr;
}





#endif //STUDY_CONNECTION_HPP
