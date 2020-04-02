# C++ 基础知识点
---
## 1. 指针和引用的区别  
参考网址:[指针VS引用](https://www.runoob.com/w3cnote/cpp-difference-between-pointers-and-references.html)  
* 指针和引用本质上没有太大区别，引用的底层是用指针常量实现的(int * const p)
* int const *p:常量指针:指针指向可以修改，内存值不可以修改
* int * const p:指针常量:指向不可以修改，指向的内存值可以修改
  
---