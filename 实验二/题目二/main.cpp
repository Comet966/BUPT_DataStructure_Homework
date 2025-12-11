#include <iostream>
#include "stack_define.h"
#include "tri_tuple_def.h"

using namespace std;
int main() {

//乘法测试:
    SpareMatrix<int> A;
    A.m = 3; A.n = 4; A.t = 4;
    A.data[0] = {0, 1, 1};
    A.data[1] = {1, 2, 2};
    A.data[2] = {2, 0, 3};
    A.data[3] = {2, 3, 4};

    SpareMatrix<int> B;
    B.m = 4; B.n = 3; B.t = 5;
    B.data[0] = {0, 0, 5};
    B.data[1] = {1, 1, 6};
    B.data[2] = {2, 0, 7};
    B.data[3] = {2, 2, 8};
    B.data[4] = {3, 1, 9};

    auto C = multiply(A, B);
    SpareMat_Print(&A);
    cout<<endl;
    SpareMat_Print(&B);
    cout<<endl;
    SpareMat_Print(&C);
    return 0;

}
