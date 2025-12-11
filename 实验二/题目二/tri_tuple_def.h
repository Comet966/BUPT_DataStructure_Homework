//
// Created by Comet on 2025/12/8.
//
//三元组的定义

#ifndef ZUOYE_2_TRI_TUPLE_DEF_H
#define ZUOYE_2_TRI_TUPLE_DEF_H

#include <vector>
#include <iostream>
#include <algorithm>

#define MAX_ELEMENT_NUMBER 1000

//定义三元组
template<class T>
struct MatrixNode
{
    int row;
    int col;
    T value;
};

//定义稀疏矩阵结构体
template<class T>
struct SpareMatrix
{
    int m;//行数
    int n;//列数
    int t;//非零元素个数
    MatrixNode<T> data[MAX_ELEMENT_NUMBER];
};

template<class T>
SpareMatrix<T>* SpareMar_Create_vec(const std::vector<std::vector<int>>& vec,int row,int col)//使用容器vector实现的二维数组
{
    auto *p =new SpareMatrix<T>;
    p->m = row;
    p->n = col;
    int n=0;
    for (int i = 0; i < row ; ++i)
    {
        for(int j =0;j<col;j++)
        {
            if(vec[i][j]!=0){
                p->data[n].row = i;
                p->data[n].col = j;
                p->data[n].value = vec[i][j];
                n++;
            }
        }
    }
    p->t = n;
    return p;

}

template<class T,int Col>
SpareMatrix<T>* SpareMat_Create(const T (*Mat)[Col],int row,int col)
{
    auto * p =new SpareMatrix<T>;
    p->m = row;
    p->n = col;
    int n=0;

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(Mat[i][j]!=0)
            {
                p->data[n].row = i;
                p->data[n].col = j;
                p->data[n].value = Mat[i][j];
                n++;
            }
        }
    }

    p->t = n;
    return p;
}


template<class T>
void Spare_add(SpareMatrix<T>* &Orig_Mat,MatrixNode<T> x)
{
    if(x.row>Orig_Mat->m || x.col>Orig_Mat->n)throw "error";

    Orig_Mat->t = Orig_Mat->t +1;
    Orig_Mat->data[Orig_Mat->t] = x;

}

//三元组表元素的查找
template<class T>
MatrixNode<T>* SpareMat_Search(SpareMatrix<T>*Mat,int row,int col)
{
    SpareMatrix<T>* p = Mat;
    int i=0;
    while((p->data[i].col!=col)||(p->data[i].row!=row))
    {
        i++;
        if(i==Mat->t)
        {
            return nullptr;
        }
    }
    return &(p->data[i]);
}

//三元组对应的稀疏矩阵的展示
template<class T>
void SpareMat_Print(SpareMatrix<T>* Mat)
{
    for(int i=0;i<Mat->m;i++)
    {
        for(int j=0;j<Mat->n;j++)
        {
            MatrixNode<T>* p= SpareMat_Search<T>(Mat,i,j);
            if(p)
            {
                std::cout<<p->value<<"\t";
            }
            else
            {
                std::cout<<0<<"\t";
            }
        }
        std::cout<<std::endl;
    }
}

//三元组乘法运算
// 稀疏矩阵乘法：C = A × B
template<class T>
SpareMatrix<T> multiply(const SpareMatrix<T>& A, const SpareMatrix<T>& B) {
    if (A.n != B.m) {
        throw std::invalid_argument("矩阵维度不匹配，无法相乘");
    }

    SpareMatrix<T> C;
    C.m = A.m;
    C.n = B.n;
    C.t = 0;

    // 1. 把 B 按列组织成列表：B_col[j] 存放 B 第 j 列的所有非零元素 (行, 值)
    std::vector<std::vector<std::pair<int, T>>> B_col(B.n);
    for (int i = 0; i < B.t; ++i) {
        const auto& node = B.data[i];
        B_col[node.col].emplace_back(node.row, node.value);
    }

    // 2. 遍历 A 的每一行 i
    for (int i = 0; i < A.m; ++i) {
        // 收集 A 第 i 行的所有非零元素 (列, 值)
        std::vector<std::pair<int, T>> rowA;
        for (int k = 0; k < A.t; ++k) {
            if (A.data[k].row == i) {
                rowA.emplace_back(A.data[k].col, A.data[k].value);
            }
        }
        if (rowA.empty()) continue;

        // 3. 对 C 的每一列 j 计算 C[i][j]
        for (int j = 0; j < B.n; ++j) {
            T sum = T(0);
            // 遍历 B 第 j 列的非零元素
            for (const auto& [rowB, valB] : B_col[j]) {
                // 在 A 第 i 行中查找是否有 col == rowB
                for (const auto& [colA, valA] : rowA) {
                    if (colA == rowB) {
                        sum += valA * valB;
                        break;  // 假设同一位置最多一个非零元素
                    }
                }
            }

            if (sum != T(0)) {
                if (C.t >= MAX_ELEMENT_NUMBER) {
                    throw std::runtime_error("结果非零元素过多，超出数组上限");
                }
                C.data[C.t] = {i, j, sum};
                ++C.t;
            }
        }
    }

    // 4. 按行、列排序（保持三元组顺序）
    std::sort(C.data, C.data + C.t, [](const MatrixNode<T>& a, const MatrixNode<T>& b) {
        if (a.row != b.row) return a.row < b.row;
        return a.col < b.col;
    });

    return C;
}

//三元组表的转置
template<class T>
void TransMat(SpareMatrix<T>* OrigMat,SpareMatrix<T>* TranMat)
{
    TranMat->m = OrigMat->n;
    TranMat->n = OrigMat->m;
    TranMat->t = 0;
    for(int col=0;col<OrigMat->n;col++)//按照列优先进行遍历
    {
        for(int j=0;j<OrigMat->t;j++)
        {
            if(OrigMat->data[j].col == col)
            {
                TranMat->data[TranMat->t].col = OrigMat->data[j].row;
                TranMat->data[TranMat->t].row = OrigMat->data[j].col;
                TranMat->data[TranMat->t].value = OrigMat->data[j].value;
                TranMat->t++;
            }
        }
    }
}



#endif //ZUOYE_2_TRI_TUPLE_DEF_H
