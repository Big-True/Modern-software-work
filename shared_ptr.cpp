#include <cstdlib>
#include <vector>

template <typename T>
class counter
{
private:
    std::size_t shared_ptr_times;
    std::size_t weak_ptr_times;
    std::vector<shared_ptr<T>> v_ptr;
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
        delete ptr;
    }
    T *get()
    {
        return ptr;
    }
    std::size_t get_shared_ptr_times(){
        return shared_ptr_times;
    }
    std::size_t get_weak_ptr_times(){
        return weak_ptr_times;
    }
    counter<T>* get_shared_ptr()
    {
        shared_ptr_times++;
        return
    }
    void delete_shared_ptr(shared_ptr<T> t_ptr){
        shared_ptr_times--;
        if(shared_ptr_times==0 && weak_ptr_times==0){
            ~counter();
        }
    }
};

template <typename T>
class shared_ptr
{
private:
    T *ptr = nullptr;
    counter *count = nullptr;

public:
    shared_ptr() = default;
    shared_ptr(T* p_data){};
    ~shared_ptr() {}
    shared_ptr<T> operator=(shared_ptr<T> s){};
    T operator*()
    {
        return *ptr;
    }
    operator->() {}
    bool operator bool()
    {
        return ptr!=nullptr;
    }
    T *get()
    {
        return ptr;
    }
    std::size_t use_count()
    {
        return ptr==nullptr?0:count->get_shared_ptr_times();
    }
    bool unique()
    {
        return count->get_shared_ptr_times()==1;
    }
};
