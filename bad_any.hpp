#include <typeinfo>
#include <algorithm>
template <typename T>
class base_data
{
public:
    T T_data;
    base_data<T>() = default;
    base_data<T>(T T_data) : T_data(T_data){};
    ~base_data<T>() = default;
};
class base_any
{
private:
    void *data;
    const std::type_info &id;

public:
    base_any();
    template <typename T>
    base_any(T data) : data(new T(data)), id(typeid(T)){};
    template <typename T>
    base_any operator=(const base_any &T_data)
    {
        return copy(T_data);
    }
    ~base_any()
    {
        clear();
    };
    bool empty()
    {
        return data != nullptr;
    }
    template <typename T>
    void set(T data)
    {
        clear();
        data = new T(data);
        id = typeid(T);
    }
    template <typename T>
    T get()
    {
        return dynamic_cast<T *>(data)->base_data;
    }
    const std::type_info &type()
    {
        return id;
    }
    void clear()
    {
        delete data;
        data = nullptr;
    }
    template <typename T>
    base_any copy(const base_any & T_data)
    {
        return base_any(std::copy(data->T_data));
    }
};

class any
{
private:
    base_any data;

public:
    any() = default;
    template <typename T>
    any(T T_data) : data(base_any(T_data)){};
    ~any() = default;
    template <typename T>
    any operator=(T T_data)
    {
        data.set<T>(T_data.data.get<T>());
        return *this;
    }
    any operator=(const any &T_data)
    {
        
    }
    template <typename T>
    void emplace(T T_data)
    {
        data = base_any(T_data);
    }
    void reset()
    {
        data.clear();
    }
    bool has_value()
    {
        return data.empty();
    }
    const std::type_info &type()
    {
        return data.type();
    }
    void swap(any T_data)
    {
        std::swap(data,T_data.data);
    }
    template <typename T>
    T get()
    {
        if (data.empty())
        {
            //throw in here
        }
        else
        {
            return data.get<T>();
        }
    }
};
class any_cast
{
    template <typename T>
    any_cast(any T_any)
    {
        if (typeid(T) == T_any.type())
        {
            T_any.data.get<T>();
        }
        else
        {
            //throw in here
        }
    };
};
void std::swap(any any1, any any2)
{
    any1.swap(any2);
}
