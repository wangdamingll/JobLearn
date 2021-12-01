#include <iostream>
using namespace std;

//share_ptr 原理简单示意程序
template <typename T>
class SharePtr
{
public:
    SharePtr(){
        ptr = new T();
        ref = new int(1);
    }
    ~SharePtr(){
        if(ref != nullptr && --(*ref) == 0)
        {
            if(ptr != nullptr){
                delete ptr;
                ptr = nullptr;
            }
            delete ref;
            ref = nullptr;
        }
    }

    SharePtr(const SharePtr& anther)
    {
        Copy(anther);
    }

    SharePtr& operator= (const SharePtr& anther)
    {
        Copy(anther);
        return *this;
    }

    SharePtr(SharePtr&& anther) noexcept
    {
        Move(std::forward<SharePtr>(anther));
    }

    SharePtr& operator=(SharePtr&& anther) noexcept
    {
        Move(std::forward<SharePtr>(anther));
        return *this;
    }

    //辅助函数
    T* operator->()
    {
        return ptr;
    }

    T& operator*()
    {
        return *ptr;
    }

    bool operator==(const SharePtr& anther)
    {
        return this->ptr == anther.ptr;
    }

public:
    //测试
    int GetRefCount(){return *ref;}

private:
    void Copy(const SharePtr& anther)
    {
        if(ref != nullptr)
        {
            if(*ref == 1) {
                if (ptr != nullptr) {
                    delete ptr;
                    ptr = nullptr;
                }
                delete ref;
                ref = nullptr;
            } else{
                (*ref)--;
            }
        }

        if(anther.ref != nullptr)
        {
            (*anther.ref)++;
        }
        ptr = anther.ptr;
        ref = anther.ref;
    }

    void Move(SharePtr&& anther)
    {
        if(ref != nullptr)
        {
            if(*ref == 1) {
                if (ptr != nullptr) {
                    delete ptr;
                    ptr = nullptr;
                }
                delete ref;
                ref = nullptr;
            } else{
                (*ref)--;
            }
        }

        ptr = anther.ptr;
        ref = anther.ref;

        anther.ptr = nullptr;
        anther.ref = nullptr;
    }
private:
    //下面这两个其实可以一起分配内存,这里不搞复杂了,这里只演示原理
    T* ptr = nullptr;
    int* ref = nullptr;
};

class Test
{
public:
    Test() = default;
    ~Test(){
        std::cout<<"~Test()"<<std::endl;
    }
    int a = 0;
};

int main()
{
    {
        SharePtr<Test>* sharePtrA = new SharePtr<Test>();
        std::cout<<"sharePtrA.ref:"<<sharePtrA->GetRefCount()<<std::endl;
        std::cout<<"Test.a:"<<(*(*sharePtrA)).a<<std::endl;

        SharePtr<Test> sharePtrB = *sharePtrA;
        std::cout<<"sharePtrB.ref:"<<sharePtrB.GetRefCount()<<std::endl;

        if(*sharePtrA == sharePtrB)
        {
            std::cout<<"*sharePtrA == sharePtrB"<<std::endl;
        } else{
            std::cout<<"*sharePtrA != sharePtrB"<<std::endl;
        }

        delete sharePtrA;
        std::cout<<"sharePtrB.ref:"<<sharePtrB.GetRefCount()<<std::endl;

        sharePtrB->a++;
        std::cout<<"Test.a:"<<sharePtrB->a<<std::endl;
    }

    {
        SharePtr<Test> sharePtrA;
        std::cout<<"sharePtrA.ref:"<<sharePtrA.GetRefCount()<<std::endl;

        SharePtr<Test> sharePtrB = std::move(sharePtrA);
        std::cout<<"sharePtrB.ref:"<<sharePtrB.GetRefCount()<<std::endl;

        SharePtr<Test> sharePtrC(std::move(sharePtrB));
        std::cout<<"sharePtrC.ref:"<<sharePtrC.GetRefCount()<<std::endl;

        SharePtr<Test> sharePtrD;
        sharePtrD = std::move(sharePtrC);
        std::cout<<"sharePtrD.ref:"<<sharePtrD.GetRefCount()<<std::endl;
    }

    return 0;
}