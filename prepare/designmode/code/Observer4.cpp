#include <iostream>
#include <string>
#include <list>
#include <memory>

using namespace std;

//观察者模式拉模型实现
//采用weak_ptr方式实现观察者列表
//优点:观察者目标类能知道观察者列表中的对象是否有效

class BlogBase;

//观察者
class ObserverBase
{
public:
    ObserverBase() = default;
    virtual ~ObserverBase() = default;
    virtual void Update(const BlogBase& blog) = 0;
};

//博客
class BlogBase
{
public:
    BlogBase() = default;
    virtual ~BlogBase()  = default;
    void Attach(std::weak_ptr<ObserverBase>&& observer)  //添加观察者
    {
        m_observers.push_back(std::move(observer));
    }
    void Remove(const std::weak_ptr<ObserverBase>& observer) //移除观察者
    {
        m_observers.remove_if([&](const std::weak_ptr<ObserverBase>& item)->bool{
            if(!item.expired())
            {
                return item.lock() == observer.lock();
            }
            return false;
        });
    }
    void Notify(const BlogBase& blog) //通知观察者
    {
        auto iter = m_observers.begin();
        for(; iter != m_observers.end();)
        {
            if(!iter->expired())
            {
                iter->lock()->Update(blog);
                iter++;
            } else{
                std::cout<<"observer is null."<<std::endl;
                iter = m_observers.erase(iter);
            }
        }
    }

    uint32_t Size(){return m_observers.size();}

    virtual void SetStatus(string s) = 0; //设置状态
    virtual string GetStatus() const= 0;    //获得状态
private:
    list<std::weak_ptr<ObserverBase>> m_observers; //观察者链表
};

//具体博客类
class BlogCSDN : public BlogBase
{
private:
    string m_name; //博主名称
public:
    explicit BlogCSDN(string name): m_name(std::move(name)) {}
    ~BlogCSDN() override  = default;

    void SetStatus(string s) override {  //具体设置状态信息
        m_status = "CSDN:" + m_name + ":" + s;
        Notify(*this);
    }
    string GetStatus() const override { return m_status; }

protected:
    string m_status; //状态
};

//具体观察者
class ObserverBlogCSDN : public ObserverBase
{
private:
    string m_name;  //观察者名称
public:
    ObserverBlogCSDN(string name): m_name(std::move(name)){}
    ~ObserverBlogCSDN() override  = default;
    void Update(const BlogBase& blog) override
    {
        cout<<m_name<<" observer->"<<blog.GetStatus()<<endl;  //拉模型
    }
};

int main(){
    BlogBase *blog = new BlogCSDN("wangdaming");
    std::shared_ptr<ObserverBase> pShare1 = std::make_shared<ObserverBlogCSDN>("wangdaming");
    blog->Attach(pShare1);
    {
        std::shared_ptr<ObserverBase> pShare2 = std::make_shared<ObserverBlogCSDN>("others");
        blog->Attach(pShare2);
        blog->SetStatus("DesignMode");
    }
    blog->SetStatus("DataStruct");
    blog->Remove(pShare1);
    delete blog;
    return 0;
}
