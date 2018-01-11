//
// Created by app05 on 2018/1/10.
//



#include <http/connection.hpp>


namespace http {

    request::request(socket_buffer buffer, std::size_t length) {
        std::size_t position = 0;
        std::size_t lastPos = 0;

        auto copyFunction = [](char *data, int begin, int length, std::string &str){
            for(int i = 0; i < length; i++){
                str += data[i + begin];
            }
        };

        auto findChar = [](socket_buffer buffer1, char c, size_t begin) ->int {
            for(int i = begin; i < buffer1.size(); i++){
                if(buffer1[i] == c){
                    return i;
                }
            }
            return 0;
        };
        std::cout << buffer.data() << std::endl;

        //read meth path and http/version
        position = findChar(buffer, ' ', 0);
        copyFunction(buffer.data(), 0, position, method);
        //path
        lastPos = position + 1;
        position = findChar(buffer, ' ', lastPos);
        copyFunction(buffer.data(), lastPos, position - lastPos, path);
        //version
        lastPos = position + 1;
        position = findChar(buffer, '\r', lastPos);
        copyFunction(buffer.data(), lastPos, position - lastPos, version);

        std::cout << method << std::endl;
        std::cout << path << std::endl;
        std::cout << version << std::endl;

        //read other heander
        while(true){
            header h;
            lastPos = position + 2;
            if(buffer[lastPos] == '\r' && buffer[lastPos + 1] == '\n'){
                //read param

                break;
            }

            position = findChar(buffer, ':', lastPos + 2);
            if(position != 0){
                copyFunction(buffer.data(), lastPos, position - lastPos, h.name);
            }

            lastPos = position;
            position = findChar(buffer, '\r', lastPos + 2);
            if(position != 0){
                copyFunction(buffer.data(), lastPos + 2, position - lastPos - 2, h.value);
            }


//            std::cout << h.name << std::endl;
//            std::cout << h.name.size() << std::endl;
//            std::cout << h.value << std::endl;
//            std::cout << h.value.size() << std::endl;
//
//            if(h.value.size() > 0 && h.name.size() > 0){
//                headers.push_back(h);
//            }


        }

    }



    connection::connection(boost::asio::ip::tcp::socket socket, managerConnection &managerCon)
    :m_socket(std::move(socket))
    ,m_managerCon(managerCon){
    }

    connection::~connection() {
        std::cout << "~connection() \n";
    }

    void connection::start() {
        m_socket.async_read_some(boost::asio::buffer(m_buffer), [this](boost::system::error_code error_code, std::size_t bytes_transferred){
            if(!error_code){
                std::cout << " no error " << std::endl;
                request req(m_buffer, bytes_transferred);
            }
            else{
                std::cout << " error \n";
            }
        });
    }

    void connection::write() {

    }




}