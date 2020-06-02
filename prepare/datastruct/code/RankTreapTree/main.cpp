#include <iostream>
#include "RankTreap.hpp"

using namespace std;

// Test program
int main( ){
    OrderStatisticTree t;
    vector<int> vec { 1, 3, 5, 7, 9, 11, 2 };
    for (int x : vec)
        t.insert(x);

    cout << "order of 7: " << t.order_of_key(7) << endl;
    cout << "order of 8: " << t.order_of_key(8) << endl;
    cout << "order of 1: " << t.order_of_key(1) << endl;

    cout << "key of rank 5: " << *t.find_by_order(5) << endl;
    return 0;
}
