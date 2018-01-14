//
// Created by nova on 2018/1/13.
//

#ifndef STUDY_SERVER_HPP
#define STUDY_SERVER_HPP

#include <string>
#include <boost/asio.hpp>
#include <socket/managerConnection.hpp>
#include <socket/connection.hpp>
#include <functional>
#include <boost/thread.hpp>
namespace keepsocket{


    typedef std::function<void(connection_ptr)> msgFunc;

    class server{
    public:
        server(std::string address, std::string port);

        //please call pre start(), but not why.  ??
        void registMsgCallBack(msgFunc func);
        void start();
    private:
        std::string m_address;
        std::string m_port;


        boost::asio::io_service m_io_service;
        boost::asio::ip::tcp::socket m_socket;
        boost::asio::ip::tcp::acceptor m_acceptor;

        managerConn m_managerConn;

        void do_accept();

        msgFunc m_func;
    };
}





#endif //STUDY_SERVER_HPP
