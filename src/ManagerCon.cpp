//
// Created by app05 on 2018/1/11.
//



#include <ManagerCon.hpp>


namespace http{

    managerConnection::managerConnection() {}

    void managerConnection::addConnection(connection_ptr con) {
        cons.insert(con);
    }

    void managerConnection::removeConnection(connection_ptr con) {
        cons.erase(con);
    }

}