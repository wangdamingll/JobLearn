#include <iostream>
#include <sstream>
#include <string>
#include "BinaryHeap.hpp"
using namespace std;

// Test program
int main(){
    BinaryHeap<int> h;
    h.Insert(1);
    h.Insert(5);
    h.Insert(3);
    h.Insert(3);

    int x = 0;
    while(!h.IsEmpty()){
        h.DeleteMin( x );
        std::cout<<x<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
