#include <iostream>
#include <string>
#include <memory>
#include <functional>

using namespace std;

//hash table 内部节点
template <typename T,typename U>
class Node{
public:
    Node(const T& key,const T& value){
        m_key = key;
        m_value = value;
    }
    ~Node(){
        std::cout<<"~Node()"<<std::endl;
    }
public:
    T m_key;
    U m_value;
    std::unique_ptr<Node<T,U>> pNode = nullptr; //内存是否能回收？
};

//基于hash table 实现的HashMap 冲突解决使用拉链法
template <typename T,typename U>
class HashMap{
public:
    explicit HashMap(const unsigned int size){
        this->m_size = size;
        m_ppNode = std::make_unique<unique_ptr<Node<T,U>>[]>(m_size);
        for(unsigned int index=0;index<m_size;index++){
            m_ppNode[index].reset(nullptr);
        }
    }
public:
    void Insert(const T& key,const U& value){
        int index = std::hash<T>{}(key)%m_size; //std::hash C++ 17
        std::unique_ptr<Node<T,U>> newNode = std::make_unique<Node<T,U>>(key,value);
        if(m_ppNode[index] == nullptr){
            m_ppNode[index] = std::move(newNode);//内存是否被正确回收？待验证
            return ;
        }
        //map容器考虑去重
        Node<T,U>* node = m_ppNode[index].get();
        while(node->pNode!= nullptr){
            if(node->m_key == key){
                node->m_value = value;
                return;
            }
            node = node->pNode.get();
        }
        if(node->m_key == key){ //判断循环最后一个元素
            node->m_value = value;
            return ;
        }
        //没有重复的元素 采用尾插法
        node->pNode = std::move(newNode);
    }
    U Get(const T&key){
        int index = std::hash<T>{}(key)%m_size;
        auto p = m_ppNode[index].get();
        while(p!= nullptr){
            if(p->m_key == key){
                return p->m_value;
            }
            p = p->pNode.get();
        }
        return U();
    }
    bool Find(const T&key){
        int index = std::hash<T>{}(key)%m_size;
        auto p = m_ppNode[index].get();
        while(p!= nullptr){
            if(p->m_key == key){
                return true;
            }
            p = p->pNode.get();
        }
        return false;
    }
private:
    std::unique_ptr<unique_ptr<Node<T,U>>[]> m_ppNode = nullptr;//unique_ptr对象数组
    unsigned int m_size=0;
};

int main() {
    {
        HashMap<string,string> map(100);
        map.Insert("a","aaa");
        map.Insert("b","bbb");

        if(map.Find("a")){
            std::cout<<"True"<<std::endl;
        }else{
            std::cout<<"False"<<std::endl;
        }

        if(map.Find("aa")){
            std::cout<<"True"<<std::endl;
        }else{
            std::cout<<"False"<<std::endl;
        }

        std::string valuea = map.Get("a");
        std::cout<<"valuea="<<valuea<<std::endl;
        std::string valueb = map.Get("b");
        std::cout<<"valueb="<<valueb<<std::endl;

        std::string valuec = map.Get("c");
        std::cout<<"valuec="<<valuec<<std::endl;
    }
    return 0;
}