//
// Created by nova on 2018/1/13.
//




#include <socket/managerConnection.hpp>


namespace keepsocket{
    managerConn::managerConn() {

    }


    void managerConn::start(connection_ptr con) {
        m_conns.insert(con);
    }

    void managerConn::stop(connection_ptr con) {
        m_conns.erase(con);
    }
}