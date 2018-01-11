//
// Created by app05 on 2018/1/11.
//

#ifndef STUDY_COMMEN_HPP
#define STUDY_COMMEN_HPP

//#include "connection.hpp"
#include <memory>


namespace http{
    class connection;
    typedef std::shared_ptr<connection> connection_ptr;
}


#endif //STUDY_COMMEN_HPP
