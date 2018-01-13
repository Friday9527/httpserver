//
// Created by app05 on 2018/1/11.
//

#ifndef STUDY_COMMEN_HPP
#define STUDY_COMMEN_HPP

//#include "connection.hpp"
#include <memory>
#include <functional>
#include <boost/asio.hpp>
namespace http{
    class connection;
    typedef std::shared_ptr<connection> connection_ptr;

    typedef std::function<void(connection_ptr)> connection_cb;

    typedef std::vector<boost::asio::const_buffer> write_buffer;
}


#endif //STUDY_COMMEN_HPP
