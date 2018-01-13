//
// Created by nova on 2018/1/13.
//

#ifndef STUDY_MANAGERCONNECTION_HPP
#define STUDY_MANAGERCONNECTION_HPP


#include <set>

#include "connection.hpp"



namespace keepsocket{

    class managerConn{
    public:
        managerConn(const managerConn&) = delete;
        managerConn &operator =(const managerConn&) = delete;


        managerConn();

        void start(connection_ptr con);
        void stop(connection_ptr con);
    private:
        std::set<connection_ptr> m_conns;
    };
}



#endif //STUDY_MANAGERCONNECTION_HPP
