#include <iostream>
#include <string>
#include <list>

using namespace std;

//动态触发联动:区别对待观察者

class BlogBase;

//观察者
class ObserverBase
{
public:
    ObserverBase() = default;
    virtual ~ObserverBase() = default;
    virtual void Update(const BlogBase& blog) = 0;
    virtual std::string GetName() = 0;
};

//博客
class BlogBase
{
public:
    BlogBase() = default;
    virtual ~BlogBase()  = default;
    void Attach(ObserverBase *observer) { m_observers.push_back(observer); }	 //添加观察者
    void Remove(ObserverBase *observer) { m_observers.remove(observer); }        //移除观察者

    virtual void SetStatus(string s) = 0; //设置状态
    virtual string GetStatus() const= 0;    //获得状态

    virtual void SetOp(string op) = 0; //设置操作
    virtual string GetOp() const= 0;    //获得操作

protected:
    virtual void Notify(const BlogBase& blog) //通知观察者
    {
        auto iter = m_observers.begin();
        for(; iter != m_observers.end(); iter++)
        {
            (*iter)->Update(blog);
        }
    }

protected:
    list<ObserverBase* > m_observers; //观察者链表
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

    void SetOp(string op) override {  //具体设置状态信息
        m_op = op;
    }
    string GetOp() const override { return m_op; }

protected:
    void Notify(const BlogBase& blog) override //通知观察者
    {
        auto iter = m_observers.begin();
        for(; iter != m_observers.end(); iter++)
        {
            std::string op = GetOp();
            if(op == "modify" && (*iter)->GetName() == "wangdaming")
            {
                (*iter)->Update(blog);
            }

            if(op == "update" && (*iter)->GetName() == "others")
            {
                (*iter)->Update(blog);
            }
        }
    }
protected:
    string m_status ; //状态
    string m_op ;//操作
};

//具体观察者
class ObserverBlogCSDN : public ObserverBase
{
public:
    ObserverBlogCSDN(string name): m_name(std::move(name)){}
    ~ObserverBlogCSDN() override  = default;
    void Update(const BlogBase& blog) override
    {
        cout<<m_name<<" observer->"<<blog.GetStatus()<<":"<<blog.GetOp()<<endl;  //拉模型
    }
    std::string GetName() override
    {
        return m_name;
    }

private:
    string m_name;  //观察者名称
};

int main(){
    BlogBase *blog = new BlogCSDN("wangdaming");
    ObserverBase *observer1 = new ObserverBlogCSDN("wangdaming");
    ObserverBase *observer2 = new ObserverBlogCSDN("others");
    blog->Attach(observer1);
    blog->Attach(observer2);

    blog->SetOp("modify");
    blog->SetStatus("DesignMode");

    blog->SetOp("update");
    blog->SetStatus("DataStruct");

    blog->Remove(observer1);
    blog->Remove(observer2);
    delete blog;
    delete observer1;
    return 0;
}
