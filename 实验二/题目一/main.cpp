#include <iostream>
#include "stack_define.h"
#include "tri_tuple_def.h"

using namespace std;
int main() {

//链栈的建立与初始化
    LinkStack<int> test_stack;
//判断栈空
    cout<<"Is Empty?"<<endl;
    cout<<test_stack.Empty()<<endl;
    cout<<endl;

    int x1[10]={1,2,5,6,7,12,23,34,55,59};
    for(int i=0;i<10;i++)
    {
        test_stack.Push(x1[i]);
    }
    test_stack.Print();
//链栈的入栈出栈
    cout<<"Push 66 into"<<endl;
    int x2=66;
    test_stack.Push(x2);
    test_stack.Print();
    cout<<"Pop 66 out"<<endl;
    x2=test_stack.Pop();
    test_stack.Print();
//取栈顶
    cout<<"Get pop"<<endl;
    cout<<test_stack.GetPop()<<endl;



    return 0;

}
