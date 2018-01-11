//
// Created by app05 on 2018/1/9.
//

#ifndef STUDY_CONNECTION_H
#define STUDY_CONNECTION_H

#include <vector>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/algorithm/algorithm.hpp>
#include <boost/thread.hpp>


#include "common.hpp"
#include "ManagerCon.hpp"

namespace http{



    typedef std::array<char, 8196> socket_buffer;


    struct header{
        std::string name;
        std::string value;
    };

    struct request{
        request(){}
        request(socket_buffer buffer, std::size_t length);
        std::string method;
        std::string path;
        std::string version;
        std::vector<char> body;
        std::vector<header> headers;
    };

    struct reply{
        enum status_code {
            OK                  = 200,
            RecordCreated       = 201,
            BadRequest          = 400,
            NotAuthorized       = 401,
            NotFound            = 404,
            Found               = 302,
            InternalServerError = 500
        };
        reply( status_code c = OK):status(c){}
        status_code              status;
        std::vector<header>      headers;
        std::vector<char>        body;
    };



    class connection : public std::enable_shared_from_this<connection>{
    public:
        connection(const connection &) = delete;
        connection &operator =(const connection &) = delete;
        explicit connection(boost::asio::ip::tcp::socket socket, managerConnection& managerCon);

        void registCb(connection_cb cb);

        ~connection();


        const request &getRequest();


        void postReply(reply rep);

        void start();

    private:
        boost::asio::ip::tcp::socket m_socket;
        socket_buffer m_buffer;

        managerConnection &m_managerCon;

        request m_request;

        void write(const reply &rep);

        connection_cb m_cb;
    };




}




#endif //STUDY_CONNECTION_H
