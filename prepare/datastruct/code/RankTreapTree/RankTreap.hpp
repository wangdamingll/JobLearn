#ifndef ORDER_STATISITC_TREE_H
#define ORDER_STATISITC_TREE_H

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

using OrderStatisticTree = __gnu_pbds::tree<
        int,
        __gnu_pbds::null_type,
        less<int>,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update>;
#endif //ORDER_STATISITC_TREE_H
