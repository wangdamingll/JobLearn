#include "HashMap1.hpp"
#include "HashMap2.hpp"

/* 哈希表-----哈希表的应用
 *
 * */

int main() {
    hashmap1::TestHashMap1();//基于hash table实现的HashMap,冲突解决使用拉链法
    hashmap2::TestHashMap2();//基于hash table实现的HashMap,冲突解决使用开放地址法
}
