#include <iostream>
#include <string>
#include <memory>

using namespace std;

template <typename T>
class Singleton{
public:
    static T* Instance(){
        return &m_instance;
    }

    Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
private:
    static T m_instance;
};
template <typename T> T Singleton<T>::m_instance;

struct A
{
    A() = default;
    void Fun(){std::cout<<"A::Fun"<<std::endl;};
};
struct B
{
    B() = default;
    void Fun(){std::cout<<"B::Fun"<<std::endl;};
};

int main(){
    Singleton<A>::Instance()->Fun();
    Singleton<B>::Instance()->Fun();

    return 0;
}