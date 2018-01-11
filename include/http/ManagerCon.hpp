//
// Created by app05 on 2018/1/11.
//

#ifndef STUDY_MANAGERCON_HPP
#define STUDY_MANAGERCON_HPP

#include <http/commen.hpp>
#include <set>

namespace http{

    class managerConnection{
    public:
        managerConnection(const managerConnection&) = delete;
        managerConnection &operator =(const managerConnection&) = delete;
        managerConnection();

        void addConnection(connection_ptr con);
        void removeConnection(connection_ptr con);

    private:
        std::set<connection_ptr> cons;
    };

}





#endif //STUDY_MANAGERCON_HPP
