#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum State{
    EMPTY,
    DELETE,
    EXIST
};

//hash table 内部节点
template <typename K,typename V>
class HashNode{
public:
    HashNode():m_state(EMPTY){}
public:
    std::pair<K,V> m_kv;
    State m_state;
};

//基于hash table 实现的HashMap 冲突解决使用开放地址法
template <typename K,typename V,bool isLine = true> //模板偏特化
class HashMap{
public:
    explicit HashMap(const unsigned int size = 10):m_size(0){
        m_table.resize(GetNextPrime(size));
    }
public:
    bool Insert(const K& key,const V& value){
        CheckSize();
        unsigned int hashAddr = std::hash<K>{}(key)%m_table.size();//C++ 17
        unsigned int index = hashAddr;
        while(m_table[index].m_state == EXIST){
            if(m_table[index].m_kv.first == key){
                return false;
            }
            if(isLine){
                index = DetectedLine(index);
            }else{

            }
        }
        m_table[index].m_kv = std::make_pair(key,value);
        m_table[index].m_state = EXIST;
        m_size++;
        return true;
    }

    std::pair<HashNode<K,V>*,bool> Find(const K&key){
        unsigned int hashAddr = std::hash<K>{}(key)%m_size;//C++ 17
        unsigned int index = hashAddr;
        HashNode<K, V>& elem = m_table[index];
        if(elem.m_kv.first!=key){ //产生冲突了 继续寻找
            if(isLine){//线性查找
                while(true){
                   index++;
                   if(index == m_table.size()){
                       index = 0;
                   }
                   if(index == hashAddr){
                       return std::make_pair(&elem,false);
                   }
                   if(m_table[index].m_kv.first == key && m_table[index].m_state == EXIST){
                       return std::make_pair(&m_table[index], true);
                   }
                }
            }else{//平方查找

            }
        }else{
            if(m_table[index].m_state == EXIST){
                return make_pair(&elem, true);
            }
        }

        return make_pair(&elem, false);
    }

    bool Remove(const K& key){
        auto ret = Find(key);
        if(ret.second){
            ret.first->m_state = DELETE;
            m_size--;
            return true;
        }
        return false;
    }

    inline unsigned int Size(){
        return m_size;
    }

private:
    unsigned int DetectedLine(unsigned int hashAddr){ //线性探查法
        hashAddr++;
        if(hashAddr == m_table.size()){
            hashAddr = 0;
        }
        return hashAddr;
    }

    unsigned int DetectedSquare(unsigned int hashAddr, unsigned int& index){//平方探查法
        hashAddr = hashAddr + index * index;
        if(hashAddr >= m_table.size()){
            hashAddr = 0;
            index = 0;
        }
        return hashAddr;
    }

    void CheckSize(){
        if(m_size/m_table.size()*10>=6){ //当装载因子a大于0.5时，需要将vector扩容处理
            m_table.resize(GetNextPrime(m_size));

            HashMap<K,V> hm;
            for(auto it : m_table){
                if(it.m_state == EXIST){
                    hm.Insert(it.m_kv.first,it.m_kv.second);
                }
            }
            this->Swap(hm);
        }
    }

    void Swap(HashMap<K,V> hm){
        std::swap(m_size,hm.m_size);
        m_table.swap(hm.m_table);
    }

    unsigned int GetNextPrime(const unsigned int size){//使用素数表对齐做哈希表的容量，降低哈希冲突
        const int _PrimeSize = 28;
        static const unsigned long _PrimeList[_PrimeSize] ={
                52ul, 97ul, 193ul, 389ul, 769ul,
                1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
                49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
                1572869ul, 3145739ul, 6291469ul, 12582917ul, 24165843ul,
                50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
                1610612741ul, 3221225473ul, 4294967291ul
        };

        for(unsigned i = 0; i < _PrimeSize; ++i){
            if (_PrimeList[i] > size){
                return _PrimeList[i];
            }
        }
        return _PrimeList[_PrimeSize-1];
    }

private:
    std::vector<HashNode<K,V>> m_table; //hash table
    unsigned int m_size=0;//hash table store element number
};

int main() {
    {
        HashMap<int,int> map;
        map.Insert(25, 1);
        map.Insert(25, 2);
        map.Insert(14, 2);
        map.Insert(36, 3);
        map.Insert(49, 4);
        map.Insert(68, 5);
        map.Insert(57, 6);
        map.Insert(11, 7);
        map.Insert(37, 8);

        cout<<map.Size()<<endl;

        auto ret = map.Find(11);
        if(ret.second){
            std::cout<<"Find:key="<<ret.first->m_kv.first<<" value="<<ret.first->m_kv.second<<std::endl;
        }else{
            std::cout<<"not find"<<std::endl;
        }

        ret = map.Find(25);
        if(ret.second){
            std::cout<<"Find:key="<<ret.first->m_kv.first<<" value="<<ret.first->m_kv.second<<std::endl;
        }else{
            std::cout<<"not find"<<std::endl;
        }

        ret = map.Find(12);
        if(ret.second){
            std::cout<<"Find:key="<<ret.first->m_kv.first<<" value="<<ret.first->m_kv.second<<std::endl;
        }else{
            std::cout<<"not find"<<std::endl;
        }

        map.Remove(25);
        map.Remove(14);
        cout<<map.Size()<<endl;
    }
    return 0;
}