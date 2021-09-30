#include <iostream>
#include <string>
#include <memory>
#include <mutex>

using namespace std;

template <typename T>
class Singleton{
public:
    template <typename... Args>
    static T* Instance(Args&&... args){
        if(m_instance == nullptr){
            std::unique_lock<std::mutex> lock(mutex);
            if(m_instance == nullptr){
                m_instance = new T(std::forward<Args>(args)...);
            }
        }
        return m_instance;
    }

    Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
private:
    static T* m_instance;
    std::mutex;
};
template <typename T> T* Singleton<T>::m_instance = nullptr;


//test
struct A
{
    A(const string&){cout<<"lvaue"<<endl;}
    A(string&& x){cout<<"rvaue"<<endl;}
};
struct B
{
    B(const string&){cout<<"lvaue"<<endl;}
    B(string&& x){cout<<"rvaue"<<endl;}
};
struct C
{
    C(int x, double y){}
    void Fun(){cout<<"test"<<endl;}
};

int main(){
    string str = "bb";

    //创建A类型的单例
    Singleton<A>::Instance(str);

    //创建B类型的单例，临时变量str被move之后变成右值，然后可以根据移动语义来避免复制
    Singleton<B>::Instance(std::move(str));

    // 创建C类型的单例，含两个参数
    Singleton<C>::Instance(1, 3.14)->Fun();
    return 0;
}