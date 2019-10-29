#include <typeinfo>
#include <algorithm>

class base_i_data
{
public:
    base_i_data(){};
    virtual const std::type_info &type(){};
    virtual base_i_data *clone(){
        return new base_i_data();
    }
};
template <typename T>
class i_data : public base_i_data
{
public:
    T t_data;
    const std::type_info &tyid;
    i_data() = delete;
    i_data(T r_data) : t_data(r_data), tyid(typeid(T)), base_i_data(){};
    ~i_data();
    virtual const std::type_info &type() override
    {
        return tyid;
    }
    virtual i_data *clone(){
        return new i_data(t_data);
    }
};
class base_any
{
public:
    base_i_data *s_data = nullptr;
    base_any() : s_data(nullptr){};
    template <typename T>
    base_any(T t_data)
    {
        set<T>(t_data);
    }
    ~base_any()
    {
        reset();
    };
    void reset()
    {
        if (s_data != nullptr)
        {
            std::free(s_data);
        }
    }
    template <typename T>
    void set(T t_data)
    {
        if (s_data != nullptr)
        {
            reset();
        }
        s_data = (new (i_data<T>)(t_data));
    }
    const std::type_info &type()
    {
        if (has_value())
        {
            return (reinterpret_cast<base_i_data *>(s_data))->type();
        }
        else
        {
            //throw in here
        }
    }
    bool has_value()
    {
        return s_data != nullptr;
    }
    template <typename T>
    T get()
    {
        if (has_value())
        {
            return (reinterpret_cast<i_data<T> *>(s_data))->t_data;
        }
        else
        {
            //throw in here
        }
    }
    base_any *clone(){
        return new base_any(s_data->clone());
    }
};
class any
{
private:
    base_any *data = nullptr;

public:
    any()=default;
    template <typename T>
    any(T t_data)
    {
        reset();
        data = new base_any(t_data);
    }
    ~any()
    {
        reset();
    };
    any(const any &a1){
        if(a1.data!=nullptr){
            data=new base_any();
        }
        else{
            //throw in here
        }
    }
    any operator=(any a1){
        if(has_value()){
            reset();
        }
        if(a1.has_value()){
            this->data=new base_any(a1);
        }
        return *this;
    }
    bool has_value()
    {
        return data != nullptr;
    }
    void reset()
    {
        if (has_value())
        {
            delete data;
            data = nullptr;
        }
    }
    template <typename T>
    void emplace(T t_data)
    {
        reset();
        data = new base_any(t_data);
    }
    const std::type_info &type()
    {
        if (has_value())
        {
            return data->type();
        }
        else
        {
            //throw in here
        }
    }
    void swap(any a_data)
    {
        std::swap(this->data, a_data.data);
    }
    template <typename T>
    T get()
    {
        if(has_value()){
            return data->get<T>();
        }
        else{
            //throw in here
        }
    }
};
namespace std
{
    void swap(any a1, any a2)
    {
        a1.swap(a2);
    }
}

template <typename T>
T any_cast(any a)
{
    if (a.has_value() && a.type() == typeid(T))
    {
        return a.get<T>();
    }
    else
    {
        //throw in here
    }
}