//
// Created by app05 on 2018/1/10.
//



#include <http/connection.hpp>


namespace http {

    request::request(socket_buffer buffer, std::size_t length) {
        std::size_t position = 0;
        std::size_t lastPos = 0;

        auto copyFunction = [buffer](int begin, int length, std::string &str){
            for(int i = 0; i < length; i++){
                str += buffer[i + begin];
            }
        };

        auto findChar = [buffer](char c, size_t begin) ->int {
            for(int i = begin; i < buffer.size(); i++){
                if(buffer[i] == c){
                    return i;
                }
            }
            return 0;
        };
//        std::cout << buffer.data() << std::endl;

        //read meth path and http/version
        position = findChar(' ', 0);
        copyFunction(0, position, method);
        //path
        lastPos = position + 1;
        position = findChar(' ', lastPos);
        copyFunction(lastPos, position - lastPos, path);
        //version
        lastPos = position + 1;
        position = findChar('\r', lastPos);
        copyFunction(lastPos, position - lastPos, version);

        while(true){
            header h;
            lastPos = position + 2;
            if(buffer[lastPos] == '\r' && buffer[lastPos + 1] == '\n'){
                //read param

                for(int i = lastPos + 2; i < length; i++){
                    body.push_back(buffer[i]);
                }
                break;
            }

            position = findChar(':', lastPos + 2);
            if(position != 0){
                copyFunction(lastPos, position - lastPos, h.name);
            }

            lastPos = position;
            position = findChar('\r', lastPos + 2);
            if(position != 0){
                copyFunction(lastPos + 2, position - lastPos - 2, h.value);
            }
        }

    }



    connection::connection(boost::asio::ip::tcp::socket socket, managerConnection &managerCon)
    :m_socket(std::move(socket))
    ,m_managerCon(managerCon){
    }

    connection::~connection() {
//        std::cout << "~connection() \n";
    }

    void connection::start() {
        auto self(shared_from_this());
        m_socket.async_read_some(boost::asio::buffer(m_buffer), [this,self](boost::system::error_code error_code, std::size_t bytes_transferred){
            if(!error_code){
                try {
                    request req(m_buffer, bytes_transferred);
                    m_request = req;
                    if(m_cb){
                        boost::thread t([this, self](){
                            m_cb(self);
                        });
                    }
                }catch (std::exception exception){
                    std::cout << exception.what() << std::endl;
                }
            }
            else{
                std::cout << " error \n";
            }
        });
    }

    void connection::close() {
        auto self(shared_from_this());
        m_managerCon.removeConnection(self);
    }


    void connection::registCb(connection_cb cb) {
        m_cb = cb;
    }


    const request& connection::getRequest() {
        return m_request;
    }

    void connection::postReply(reply rep) {
        auto self(shared_from_this());
        m_socket.async_write_some(rep.get_write_buffer(),[this, self](boost::system::error_code ec, std::size_t){
            if(!ec){
                m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            }
            if(ec != boost::asio::error::operation_aborted){
                m_managerCon.removeConnection(self);
            }
        });
    }

    //hanle replay buffer
    write_buffer reply::get_write_buffer() {
        write_buffer buffer;
        const char name_value_separator[] = { ':', ' ' };
        const char crlf[] = { '\r', '\n' };
        switch (this->status){
            case OK:{
                buffer.push_back(boost::asio::buffer("HTTP/1.1 200 OK\r\n"));
                break;
            }
            case NotFound:{
                buffer.push_back(boost::asio::buffer("HTTP/1.1 404 Not Found\r\n"));
                break;
            }
            default:{
//                throw
            }
        }

        for(header h : headers){
            buffer.push_back(boost::asio::buffer(h.name));
            buffer.push_back(boost::asio::buffer(name_value_separator));
            buffer.push_back(boost::asio::buffer(h.value));
            buffer.push_back(boost::asio::buffer(crlf));
        }
        buffer.push_back(boost::asio::buffer(crlf));

        //write param
        if(body.size() > 0){
            buffer.push_back(boost::asio::buffer(body.data(), body.size()));
        }

        return buffer;
    }
}