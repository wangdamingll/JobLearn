#include <iostream>
#include "RankTreap1.hpp"
#include "RankTreap2.hpp"
#include <algorithm>
#include <chrono>

using namespace std;

// Test program
#define NUM (3000000)

template <typename T>
void DebugPrint(const RankTreap<T>& t){
    for(int i=1;i<=NUM+1;i++){
        std::cout << "k "<<i<<":" << t.Kth(i) << " ";
    }
    std::cout<<std::endl;
    for(int i=1;i<=NUM+1;i++){
        std::cout << "r "<<i<<":" << t.Rank(i) << " ";
    }
    std::cout<<std::endl;
}

void DebugPrintV(vector<uint64_t>& vec){
    for(auto&it:vec){
        if(it == 2){
            continue;
        }
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
}

int main(){
#if 1
    vector<uint64_t> vec;
    for (uint64_t i=1;i<=NUM;i++){
        vec.emplace_back(i);
    }

    //DebugPrintV(vec);

    std::random_shuffle(vec.begin(),vec.end());

    auto start = std::chrono::steady_clock::now();

    RankTreap<uint64_t> t;
    for(auto&it:vec){
        if(it==2){
            continue;
        }
        t.Insert(it);
    }

    //DebugPrint(t);

    std::cout << "----------Insert----------" << std::endl;
    t.Insert(2);

    //DebugPrint(t);

    std::cout << "----------Remove----------" << std::endl;
    t.Remove(1);
    t.Remove(2);
    t.Remove(3);
    t.Remove(NUM-3);
    t.Remove(NUM);

    //DebugPrint(t);

    uint64_t count=0;
    for(auto&it:vec){
        if(t.Kth(t.Rank(it))==it){
            count++;
        }
    }
    if(count!=vec.size()-5){
        std::cout<<"error"<<std::endl;
    }

    t.MakeEmpty();
    t.PrintTree();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"s"<<std::endl;
#else
    OrderStatisticTree t;
    vector<int> vec { 1, 3, 5, 7, 9, 11, 2 };
    for (int x : vec)
        t.Insert(x);

    cout << "order of 7: " << t.order_of_key(7) << endl;
    cout << "order of 8: " << t.order_of_key(8) << endl;
    cout << "order of 1: " << t.order_of_key(1) << endl;

    cout << "key of rank 5: " << *t.find_by_order(5) << endl;
    return 0;
#endif

}
