#include <typeinfo>
#include <algorithm>
template <typename T>
class base_data
{
public:
    T base_data;
    base_data<T>() = default;
    base_data<T>(T T_data) : data(T_data){};
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
    any operator=(any T_data){
        data.set<T>(T_data.data.get<T>());
        return *this;
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
        }
    };
};
void std::swap(any any1, any any2)
{
    if (any1.type() == any2.type())
    {
    }
}
