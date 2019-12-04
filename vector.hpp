#include<cstdlib>
#include<limits>
#define MAX_SIZE std::numeric_limits<std::size_t>::max()
template<typename T>
class vector
{
private:
    T* data=nullptr;
    T* end=nullptr;
    std::size_t d_size=0;
    std::size_t d_max_size=0;
public:
    vector()=default;
    vector(std::size_t count,T value){
        d_max_size=count>MAX_SIZE/2?MAX_SIZE:count*2;
        d_size=count;
        reset(d_max_size);
        T* temp=data;
        for(std::size_t i;i<d_size;++i){
            *data=value;
            data++;
        }
    }
    vector(std::size_t count){
        d_max_size=count>MAX_SIZE/2?MAX_SIZE:count*2;
        d_size=count;
        reset(d_max_size);
        T* temp=data;
    }
    vector(vector v){
        d_max_size=v.max_size();
        d_size=v.size();
        reset(d_max_size);
        T* temp=data;
        for(std::size_t i;i<d_size;++i){
            *data=v[i];
            data++;
        }
    }
    ~vector(){
        clear();
    }
    vector operator=(vector v){
//
    }
    auto get_space(std::size_t size){
        if(size!=0){
            auto* s=std::malloc(size*sizeof(T));
            if(s==nullptr){
                throw;
            }
        }
        return s;
    }
    void reset(std::size_t size){
        clear();
        data=get_space(size);
    }
    void resize(){

    }
    void clear(){
        std::free(data);
        d_size=d_max_size=0;
        data=end=nullptr;
    }
    std::size_t size(){
        return d_size;
    }
    std::size_t max_size(){
        return d_max_size;
    }
    
};

