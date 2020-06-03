#include <iostream>
#include "RankTreap1.hpp"
#include "RankTreap2.hpp"
#include <algorithm>
#include <chrono>

using namespace std;

// Test program
#define NUM (3000000)
int main(){
#if 1
    vector<uint64_t> vec;
    for (uint64_t i=1;i<=NUM;i++){
        vec.emplace_back(i);
    }

    std::random_shuffle(vec.begin(),vec.end());

    auto start = std::chrono::steady_clock::now();

    RankTreap<uint64_t> t;
    for(auto&it:vec){
        t.Insert(it);
    }

    std::cout << "kth of 7: " << t.Kth(7) << std::endl;
    std::cout << "kth of 8: " << t.Kth(8) << std::endl;
    std::cout << "kth of 1: " << t.Kth(1) << std::endl;

    std::cout << "kth of rank 5: " << t.Rank(5) << std::endl;

    for(auto&it:vec){
        t.Remove(it);
    }

    t.PrintTree();

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(end-start);
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
