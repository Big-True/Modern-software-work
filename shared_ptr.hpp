#include <cstdlib>
#include <vector>
#include <algorithm>

template <typename T>
class shared_ptr;
template <typename T>
class counter
{
private:
    std::size_t shared_ptr_times;
    std::size_t weak_ptr_times;
    std::vector<shared_ptr<T> *> v_ptr;
    T *ptr;

public:
    counter() = delete;
    counter(T *data, shared_ptr<T> *s_ptr)
    {
        shared_ptr_times = 1;
        weak_ptr_times = 0;
        ptr = data;
        v_ptr.push_back(s_ptr);
    }
    ~counter()
    {
        clear();
    }
    T *get()
    {
        return ptr;
    }
    std::size_t get_shared_ptr_times()
    {
        return shared_ptr_times;
    }
    std::size_t get_weak_ptr_times()
    {
        return weak_ptr_times;
    }
    T *get_shared_ptr(shared_ptr<T> *s_ptr)
    {
        shared_ptr_times++;
        v_ptr.push_back(s_ptr);
        return ptr;
    }
    void delete_shared_ptr(shared_ptr<T> *t_ptr)
    {
        for (auto i = v_ptr.begin(); i != v_ptr.end(); ++i)
        {
            if (*i == t_ptr)
            {
                v_ptr.erase(i);
                shared_ptr_times--;
                break;
            }
        }
        if (shared_ptr_times == 0 && weak_ptr_times == 0)
        {
            clear();
        }
    }
    void clear()
    {
        delete ptr;
    }
};

template <typename T>
class shared_ptr
{
private:
    T *ptr = nullptr;
    counter<T> *count = nullptr;

public:
    shared_ptr() = default;
    shared_ptr(T *p_data)
    {
        count = new counter<T>(p_data, this);
        ptr = p_data;
    };
    ~shared_ptr()
    {
        clear();
    }
    shared_ptr<T> operator=(shared_ptr<T> s)
    {
        clear();
        if (s)
        {
            count = s.count;
            ptr = s.count->get_shared_ptr(this);
        }
        return *this;
    };
    T &operator*()
    {
        return *get();
    }
    explicit operator bool()
    {
        return get() != nullptr;
    }
    T *get()
    {
        return ptr;
    }
    T *operator->()
    {
        return *get();
    }
    template <class Y>
    Y &operator[](std::size_t id) const
    {
        return get()[id];
    }
    void reset(T *p_data)
    {
        clear();
        ptr = p_data;
        count = new counter<T>(p_data, this);
    }
    std::size_t use_count()
    {
        return count == nullptr ? 0 : count->get_shared_ptr_times();
    }
    bool unique()
    {
        return count->get_shared_ptr_times() == 1;
    }
    void swap(shared_ptr &s_data)
    {
        std::swap(ptr, s_data.ptr);
        std::swap(count, s_data.count);
    }
    void clear()
    {
        if (count != nullptr)
        {
            count->delete_shared_ptr(this);
        }
    }
    template <class Y>
    bool owner_before(const shared_ptr<Y> &s_data) const
    {
        if (typeid(Y) == typeid(T))
        {
            if (count == s_data.count && count != nullptr)
            {
                return std::find(count->v_ptr.begin(), count->v_ptr.end(), this) < std::find(s_data.count->v_ptr.begin(), s_data.count->v_ptr.end(), s_data.get_this());
            }
        }
        else
        {
            return false;
        }
    }
    shared_ptr *get_this()
    {
        return this;
    }
};
