//
// Created by app05 on 2018/1/11.
//





#include <boost/thread.hpp>
#include <memory>
#include <functional>

class test;

typedef std::shared_ptr<test> test_ptr;
typedef std::function<void(test_ptr)> callback;


class test : public std::enable_shared_from_this<test>{
public:
    test():m_cb(nullptr){
        std::cout << "test constructor \n";
    }
    ~test(){
        std::cout << "delete test \n";
    }

    void func(callback cb){
        m_cb = cb;
    }

    void run(){
        auto self(shared_from_this());
        boost::thread tt([self, this](){
            boost::thread dd([self, this](){
                if(m_cb)
                    m_cb(self);
                std::cout << "thread dd \n";
            });
            std::cout << "thread tt \n";
        });
    }
private:
    callback m_cb;
};


class server{
public:
    void regsiteFunc(callback cb){
        m_cb = cb;
    }
    void run(){
        auto tt = std::make_shared<test>();
//        auto tt = std::shared_ptr<test_ptr>();
        tt->func(m_cb);
        tt->run();
    }
private:
    callback m_cb;
};




int main(){



    server ss;
    ss.regsiteFunc([](test_ptr tt){
        std::cout << "success \n";
    });

    ss.run();

    while(true);

    return 0;
}