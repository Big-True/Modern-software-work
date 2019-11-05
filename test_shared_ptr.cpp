#include "shared_ptr.hpp"
#include<iostream>
int main()
{
    shared_ptr<int> a=new int(15);
    std::cout<<a.use_count()<<':'<<*a<<std::endl;
    shared_ptr<int> b;
    b=a;
    std::cout<<a.use_count()<<':'<<*a<<' '<<b.use_count()<<':'<<*b<<std::endl;
    a.reset(new int(20));
    std::cout<<a.use_count()<<':'<<*a<<' '<<b.use_count()<<':'<<*b<<std::endl;
    return 0;
}