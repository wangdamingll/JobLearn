#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
你可以认为 s 和 t 中仅包含英文小写字母。字符串 t 可能会很长（长度 ~= 500,000），而 s 是个短字符串（长度 <=100）。
字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

示例 1:
s = "abc", t = "ahbgdc"
返回 true.

示例 2:
s = "axc", t = "ahbgdc"
返回 false.

后续挑战 :
如果有大量输入的 S，称作S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
*/


//暴力枚举:std::string::find()依次找出s中的每个字符在t中的位置，并判断index是否满足要求即可
//这里不写了,基本上是超时的

//双指针
//s对应的长度为M t对应的长度为N
//时间复杂度:O(M + N)
//空间复杂度O(1)
class Solution1 {
public:
    bool isSubsequence(string s, string t) {
        uint32_t sindex = 0;
        uint32_t tindex =0;
        uint32_t ssize = s.size();
        uint32_t tsize = t.size();

        while(sindex<ssize && tindex<tsize){
            if(s[sindex] == t[tindex]){
                sindex++;
            }
            tindex++;
        }

        return sindex==ssize;
    }
};

//dp


//二分查找
//本题letcode网站报错:堆溢出,但是本机跑的没有问题,所以借鉴一下思路吧
//s对应的长度为M t对应的长度为N
//时间复杂度:O(N + MlogN)
//空间复杂度O(N)
//预先对t进行处理，把每个字母在t中的index缓存下来
//然后查找每个s中字符时,在缓存中采用二分查找
class Solution3 {
public:
    bool isSubsequence(string s, string t) {
        //缓存t
        std::unordered_map<char,std::vector<int32_t>> mem;
        for(int32_t index=0;index<t.size();index++){
            auto ret = mem.find(t[index]);
            if(ret==mem.end()){
                mem.emplace(t[index],std::vector<int32_t>{index});
            }else{
                ret->second.emplace_back(index);
            }
        }

        //二分查找(这里就不单独封装函数了)
        int32_t lastIndex = -1;
        for(int32_t index=0;index<s.size();index++){
            auto ret = mem.find(s[index]);
            if(ret==mem.end()){
                return false;
            }

            //找到第一个大于lastIndex的值
            int32_t bIndex = BinarySearch( ret->second,lastIndex,0,ret->second.size()-1);
            if(bIndex<lastIndex || ((bIndex==t.size()-1)&&(index!=s.size()-1))){
                return false;
            } else{
                lastIndex = bIndex;
            }
        }
        return true;
    }

    int32_t  BinarySearch(std::vector<int32_t>& tV,int lastIndex,int low,int high){
        int mid = 0;
        while(low<=high){
            mid = low + ((high-low)>>1);
            if(tV[mid]<=lastIndex){
               low = mid + 1;
            }else if(tV[mid] > lastIndex){
                high = mid - 1;
            }
        }
        return tV[low];
    }
};


int main() {
    Solution1 s;
    std::string sstr = "bb";
    std::string tstr = "ahbgdc";
    bool ret = s.isSubsequence(sstr,tstr);
    std::cout<<"ret="<<ret<<std::endl;
    return 0;
}