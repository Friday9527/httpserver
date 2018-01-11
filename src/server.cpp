//
// Created by app05 on 2018/1/9.
//


#include <server.hpp>
namespace http{

    server::server(std::string address, std::string port, std::string path)
    :m_address(address)
    ,m_port(port)
    ,m_path(path)
    ,m_io_service()
    ,m_acceptor(m_io_service)
    ,m_socket(m_io_service)
    ,managerConnection()
    {
        boost::asio::ip::tcp::resolver resolver(m_io_service);
        boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({m_address, m_port});
        m_acceptor.open(endpoint.protocol());
        m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        m_acceptor.bind(endpoint);
        m_acceptor.listen();

        do_accept();
    }

    void server::run() {
        m_io_service.run();
    }

    void server::do_accept() {

        m_acceptor.async_accept(m_socket, [this](boost::system::error_code error_code){

            if(!m_acceptor.is_open()){
                return;
            }

            if(!error_code){
                auto con = std::make_shared<connection>(std::move(m_socket));
                managerConnection.addConnection(con);
                con->start();
            }
            do_accept();

        });
    }


}