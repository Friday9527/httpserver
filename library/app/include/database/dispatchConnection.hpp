//
// Created by nova on 2018/1/13.
//

#ifndef STUDY_DISPATCHCONNECTION_HPP
#define STUDY_DISPATCHCONNECTION_HPP

#include <http/common.hpp>
class app{
    inline void dispatchConnect(http::connection_ptr con){
        if(con->getRequest().path == "/login"){

        }
    }


};





#endif //STUDY_DISPATCHCONNECTION_HPP
