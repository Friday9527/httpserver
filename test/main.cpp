//
// Created by app05 on 2018/1/11.
//

#include <iostream>
#include <array>
template <typename itBegin, typename itEnd>
void send(itBegin begin, itEnd end)
{
    do{
        std::cout << *begin;
    }while (begin++ != end);
}



int main(){

    std::array<char, 10> data1;
    for(int i = 0; i < 10; i++){
        data1[i] = i;
    }
    send(data1.begin(), data1.end());

    std::string str("qwertyuiopasdfghjkl");
//    for(auto it = str.begin(); it != str.end(); it++){
//        int k = 0;
//        std::cout << k << std::endl;
//    }
//    send()

    return 0;
}