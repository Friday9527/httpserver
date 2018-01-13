//
// Created by nova on 2018/1/13.
//

#ifndef STUDY_APPLICATION_HPP
#define STUDY_APPLICATION_HPP

#include <http/common.hpp>

namespace app{
    class application{
    public:
        application();
        ~application();

        void addReceive(http::connection_ptr con);

    private:

    };
}




#endif //STUDY_APPLICATION_HPP
