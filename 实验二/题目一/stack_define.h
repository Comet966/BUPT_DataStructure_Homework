//
// Created by Comet on 2025/12/8.
//

#ifndef ZUOYE_2_STACK_DEFINE_H
#define ZUOYE_2_STACK_DEFINE_H

#include <iostream>
//定义链栈结点
template<class T>
struct Node
{
    T data;
    struct Node<T>*next;
};
//定义链栈模板类
template<class T>
class LinkStack
{
public:
    LinkStack();//构造函数
    ~LinkStack();//析构函数
    void Push(T x);//入栈操作
    T Pop();//出栈
    T GetPop();//查找栈顶元素
    bool Empty();//判断是否为空
    void Print();
private:
    struct Node<T>*top;//栈顶指针
};

template<class T>
LinkStack<T>::LinkStack() {
    top = nullptr;
}

template<class T>
void LinkStack<T>::Push(T x) {
    auto *p = new Node<T>;//使用auto编译器自动确定数据类型
    p->data = x;
    p->next = top;
    top = p;
}

template<class T>
T LinkStack<T>::Pop() {
    if(Empty())throw "下溢";
    Node<T>* p = top;//防止内存泄露
    top = top->next;
    T temp = p->data;
    delete p;
    return temp;
}

template<class T>
bool LinkStack<T>::Empty() {
    if(top == nullptr)return true;
    return false;
}

template<class T>
T LinkStack<T>::GetPop() {
    return top->data;
}

template<class T>
LinkStack<T>::~LinkStack() {
    while (top)
    {
        Node<T>*p=top;
        top = top->next;
        delete p;
    }
}

template<class T>
void LinkStack<T>::Print() {
    using namespace std;
    Node<T>*p=top;
    while (p)
    {
        cout<<p->data<<endl;
        p=p->next;
    }
}

#endif //ZUOYE_2_STACK_DEFINE_H
