#include <iostream>
#include <vector>
using namespace std;

/*
1025. 除数博弈
爱丽丝和鲍勃一起玩游戏，他们轮流行动。爱丽丝先手开局。

最初，黑板上有一个数字 N 。在每个玩家的回合，玩家需要执行以下操作：

选出任一 x，满足 0 < x < N 且 N % x == 0 。
用 N - x 替换黑板上的数字 N 。
如果玩家无法执行这些操作，就会输掉游戏。

只有在爱丽丝在游戏中取得胜利时才返回 True，否则返回 False。假设两个玩家都以最佳状态参与游戏。


示例 1：
输入：2
输出：true
解释：爱丽丝选择 1，鲍勃无法进行操作。
示例 2：

输入：3
输出：false
解释：爱丽丝选择 1，鲍勃也选择 1，然后爱丽丝无法进行操作。

提示：
1 <= N <= 1000
 */

//普通递归(超时)
class Solution1 {
public:
    bool divisorGame(int N) {
        return DivisorGame(N);
    }

    bool DivisorGame(int n){
        if(n<1){
            return false;
        }

        for(int i=1;i<n;i++){
            if(n%i==0 && !DivisorGame(n-i)){
                return true;
            }
        }
        return false;
    }
};

//记忆化递归
class Solution2 {
public:
    bool divisorGame(int N) {
        int book[1001]={0};;
        return DivisorGame(N,book);
    }

    bool DivisorGame(int n,int* book){
        if(n<1){
            return false;
        }

        if(book[n]!=0){
            return book[n]==1;
        }

        for(int i=1;i<n;i++){
            if(n%i==0 && !DivisorGame(n-i,book)){
                book[n]=1;
                return true;
            }
        }
        book[n]=2;
        return false;
    }
};

//dp
//dp[i]=  [ n%k==0 && !dp[n-k] ]  (0<k<i)
//dp[1] = false
//dp[2]= 2%1==0 && !dp[2-1] = true && !false = true
class Solution3 {
public:
    bool divisorGame(int N) {
        int dp[1001]={0};;
        for(int i=1;i<=N;i++){
            bool ret = false;
            for(int j=1;j<i;j++){
                if(i%j==0 && !(dp[i-j]==1))   {
                    ret = true;
                    break;
                }
            }
            if(ret){
               dp[i] = 1;
            }else{
               dp[i] = 2;
            }
        }
        return (dp[N]==1);
    }
};

//N 为奇数的时候 Alice（先手）必败，NN 为偶数的时候 Alice 必胜
class Solution4 {
public:
    bool divisorGame(int N) {
        return (N%2==0);
    }
};

int main() {
    Solution4 s;
    bool ret = s.divisorGame(4);
    if(ret){
        std::cout<<"1"<<std::endl;
    }else{
        std::cout<<"2"<<std::endl;
    }

}
