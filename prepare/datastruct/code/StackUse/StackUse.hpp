#ifndef __STACK_USE__H__
#define __STACK_USE__H__

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>
using namespace std;

/* 栈-----栈的应用
 *
 * 算法思想:
 * 1. 平衡符号
 *  每个右花括号、右方括号及右圆括号必然对应其相应的左括号.序列[()]是合法的,但[(])是错误的.
 *  描述如下:
 *  做一个空栈.读入字符直到文件尾,如果字符是一个开放符号,则将其推入栈中.如果字符是一个封闭符号,则当栈空时报错.否则,将栈元素弹出.如果弹出的符号不是对应的开放符号,则报错.
 *  在文件尾,如果栈非空则报错.
 *
 * 2. 中缀表达式转后缀表达式
 *  见代码
 *
 * 3. 后缀表达式计算结果
 *  当见到一个数时就把它推入栈中;在遇到一个运算符时该运算符就作用于从该栈弹出的两个数(符号)上,再将所得结果推入栈中.
 *
 * 算法特点:
 * 1. 平衡符号采用的联机算法,时间复杂度是O(N)
 * 3. 后缀表达式计算结果时间复杂度是O(N)
 *
 * 注意事项:
 * 本例这是简单的栈的应用,简单支持单位数的运算,如:1+(2*3+4),而不支持双位数运算,如:11+(2*3+4)
 * */

//平衡符号
bool CheckStr(const std::string& str){
    std::stack<char> stack;
    std::unordered_set<char> openSet;
    std::unordered_set<char> closeSet;
    std::unordered_map<char,char> map;
    openSet.emplace('(');
    closeSet.emplace(')');
    map.emplace(')','(');//建立关系

    for(auto& it:str){
        auto openRet = openSet.find(it);
        if(openRet != openSet.end()){//如果是开放符号
            stack.push(it);
            continue;
        }

        auto closeRet = closeSet.find(it);
        if(closeRet!=closeSet.end()){//如果是封闭符号
            if(stack.empty()){//栈为空 报错
                return false;
            }
            auto ch = stack.top();
            stack.pop();
            if(ch != map[*closeRet]){//封闭符号对应的开放符号和栈顶的开放符号不相同
                return false;
            }
        }
    }

    return stack.empty();//如果栈不为空 则报错
}

//中缀表达式转后缀表达式
std::string NifixExprToSuffix(const std::string& str){
    std::stack<char> stack;
    std::unordered_map<char,int> opMap;//操作符优先级
    opMap.emplace('+',1);
    opMap.emplace('-',1);
    opMap.emplace('*',2);
    opMap.emplace('/',2);
    opMap.emplace('(',6);

    std::stringstream iss;
    for(auto& ch : str){
        if(ch==' '){//空格
            continue;
        }
        //判断是否是字母或者数字
        if((65<=ch&&ch<=90)||(97<=ch&&ch<=122)||(48<=ch&&ch<=57)){//A-Z a-z 0-9 字母或者数字 直接输出
            iss<<ch;
            continue;
        }

        //假设除了字母和数字外 其余的都是运算符
        //栈为空
        if(stack.empty()){
            stack.push(ch);
            continue;
        }

        //栈不为空 需要比较优先级
        if(ch == ')'){//如果是),将栈元素直到(都弹出且(不输出
            char top;
            do{
                if(stack.empty()){//如果找不到对应的(,则出现了错误
                    return "";
                }
                top = stack.top();
                stack.pop();
                if(top!='('){
                    iss<<top;
                }
            }while(top!='(');
            continue;
        }

        //比较优先级
        auto top = stack.top();
        if(opMap.find(top)->second<opMap.find(ch)->second || top == '('){//如果栈顶的元素优先级小于当前元素或者栈顶元素时(,这里(除非遇到)否则不弹出
            stack.push(ch);
            continue;
        }

        //如果栈顶的元素大于或者等于当前元素,则一直弹出,直到小于当前元素的优先级或者栈为空,遇到(跳出结束循环
        while(opMap.find(top)->second>=opMap.find(ch)->second && top!='('){
            stack.pop();//弹出
            iss << top;
            if(stack.empty()){
                break;
            }
            top = stack.top();
        }

        stack.push(ch);//压栈
    }

    while(!stack.empty()){ //将栈中全部元素输出
        iss<<stack.top();
        stack.pop();
    }
    return std::move(iss.str());
}


//后缀表达式计算
int SuffixCalculate(const std::string& suffixStr){
    std::stack<int> stack;
    std::unordered_map<char,std::function<int(int,int)>> opMap;//操作符
    opMap.emplace('+',[](int a, int b)->int{
        return (a+b);
    });
    opMap.emplace('-',[](int a,int b)->int{
        return (a-b);
    });
    opMap.emplace('*',[](int a,int b)->int{
        return (a*b);
    });
    opMap.emplace('/',[](int a, int b)->int{
        return (a/b);
    });

    for(auto& it:suffixStr){
        if(it == ' '){//空字符
            continue;
        }
        auto iter = opMap.find(it);
        if(iter==opMap.end()){//如果是一个数字,这里为了简单起见,只定义了加减乘除
            stack.push(it-'0');//char->int
            continue;
        }

        if(stack.size()<2){//错误
            return -1;
        }
        //如果是一个运算符
        auto num1 = stack.top();
        stack.pop();
        auto num2 = stack.top();
        stack.pop();
        stack.push(iter->second(num2,num1));
    }

    return (stack.top());
}
int TestStackUse(){
    auto start = std::chrono::steady_clock::now();

    const std::string str = "1+(2*3+4)";
    bool ret = CheckStr(str);//平衡符号应用
    if(!ret){
        std::cout<<"该表达式不合法"<<std::endl;
        return 0;
    }

    const std::string suffixExpr = NifixExprToSuffix(str);//中缀表达式转后缀表达式

    int num = SuffixCalculate(suffixExpr);
    std::cout<<"计算结果:"<<num<<std::endl;

    auto end = std::chrono::steady_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"time:"<<time.count()<<"ms"<<std::endl;
    return 0;
}


#endif //__STACK_USE__H__