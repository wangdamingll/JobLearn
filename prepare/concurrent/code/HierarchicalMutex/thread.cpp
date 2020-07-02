#include<iostream>
#include<chrono>
#include "HierarchicalMutex.hpp"

using namespace std;

void TestLowMutex(HierarchicalMutex& m1, HierarchicalMutex& m2) {
    while (true) {
        {
            std::lock_guard<HierarchicalMutex> lk1(m1);
            std::lock_guard<HierarchicalMutex> lk2(m2);
            std::cout << "threadid=" << std::this_thread::get_id() << std::endl;
        }
        std::this_thread::sleep_for(1s);
    }
}

void TestHighMutex(HierarchicalMutex& m1, HierarchicalMutex& m2) {
    while (true) {
        {
            std::lock_guard<HierarchicalMutex> lk1(m1);
            std::lock_guard<HierarchicalMutex> lk2(m2);
            std::cout << "threadid=" << std::this_thread::get_id() << std::endl;
        }
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    HierarchicalMutex m1(2000);
    HierarchicalMutex m2(20);

    std::thread t1(TestLowMutex,std::ref(m1),std::ref(m2));
    std::thread t2(TestHighMutex,std::ref(m1), std::ref(m2));
    t1.join();
    t2.join();
    return 0;
}

