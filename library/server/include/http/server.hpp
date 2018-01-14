//
// Created by app05 on 2018/1/9.
//

#ifndef STUDY_SERVER_HPP
#define STUDY_SERVER_HPP

#include <string>
#include <memory>
#include <boost/asio.hpp>


#include "ManagerCon.hpp"
#include "connection.hpp"
namespace http{



    class server{
    public:
        server() = delete;
        server(std::string address, std::string port, std::string path = "");

        void run();



        void registerConnectioncb(connection_cb cb);

    private:
        void do_accept();

        //////-----------------
        std::string m_address;
        std::string m_port;
        std::string m_path;

        //
        boost::asio::io_service m_io_service;
        boost::asio::ip::tcp::acceptor m_acceptor;
        boost::asio::ip::tcp::socket m_socket;

        managerConnection m_managerConnection;


        connection_cb m_cb;
    };
}



#endif //STUDY_SERVER_HPP
