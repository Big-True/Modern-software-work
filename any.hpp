#include<cstdlib>
#include <typeinfo>
#include<algorithm>

template<typename T>
class i_data{
public:
    T t_data;
    i_data()=delete;
    i_data(T r_data):t_data(r_data){};
    ~i_data();
    const std::type_info &type(){
        return typeid(T);
    }
};
class base_any
{
public:
    i_data<void>* s_data=nullptr;
    base_any();
    template<typename T>
    base_any(T t_data){
        set<T>(t_data);
    }
    ~base_any(){
        reset();
    };
    void reset(){
        if(s_data!=nullptr){
            std::free(s_data);
        }
    }
    template<typename T>
    void set(T t_data){
        if(s_data!=nullptr){
            reset();
        }
        s_data=std::malloc(sizeof(i_data<T>));
        *s_data=i_data<T>(t_data);
    }
    const std::type_info &type(){
        return s_data->type();
    }
    bool has_value(){
        return s_data!=nullptr;
    }
    template<typename T>
    T get(){
        if(has_value()){
            return (reinterpret_cast<i_data<T>*>(s_data))->t_data;
        }
        else{
            //throw in here
        }
    }
};
class any
{
private:
    base_any* data=nullptr;
public:
    any();
    template<typename T>
    any(T t_data){
        reset();
        data=new base_any(t_data);
    }
    ~any(){
        reset();
    };
    bool has_value(){
        return data!=nullptr;
    }
    void reset(){
        if (has_value()){
            delete data;
            data=nullptr;
        }
    }
    template<typename T>
    void emplace(T t_data){
        reset();
        data=new base_any(t_data);
    }
    const std::type_info &type(){
        if(has_value()){
            return data->type();
        }
        else{
            //throw in here
        }
    }
    void swap(any a_data){
        std::swap(this->data,a_data.data);
    }
    template<typename T>
    T get(){
        return data->get<T>();
    }
};
namespace std{
    void swap(any a1,any a2){
        a1.swap(a2);
    }
}

template<typename T>
T any_cast(any a){
    if(a.has_value() && a.type()==typeid(T)){
        return a.get<T>();
    }
    else{
        //throw in here
    }
}