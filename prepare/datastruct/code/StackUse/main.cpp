#include "StackUse.hpp"
#include "StackUse2.hpp"

/* 栈-----栈的应用
 * 1. 平衡符号
 * 可以用来检查语法是否有错误
 * 2. 中缀表达式转后缀表达式(逆波兰记法)
 * 例如中缀表达式a + b * c + (d * e + f) * g 转换成后缀表达式: a b c * + d e * f + g * +
 * 3. 用后缀表达式计算结果(后缀表达式其实是中缀表达式的一个表现形式)
 * 例如后缀表达式:6 5 2 3 + 8 * + 3 + * ,其结果为:288
 * 4. 函数调用
 * */

int main() {
    TestStackUse();//栈----栈的应用
    TestStackUse2();//由后缀表达式构建一颗表达式树
}
