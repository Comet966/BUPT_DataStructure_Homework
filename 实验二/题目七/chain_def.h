//
// Created by Comet on 2025/12/11.
//

#ifndef ZUOYE_2_CHAIN_DEF_H
#define ZUOYE_2_CHAIN_DEF_H
#include <iostream>
#include <cstring>
#define Max_Num 100
const int UNINITIALIZED = -1;//哨兵值
struct block{
    int m[Max_Num];
    int n[Max_Num];
    int t;
};//每个block表示一个连通域
void block_initial(block* blk);//设置哨兵值

bool block_is_empty(block* blk);

bool block_search(block* blk,int m1,int n1);//查找是否在对应连通域中

block* block_Search(block* blk[],int m1,int n1);

template<int Col>
void devide_block(block blk[],const int(*mat)[Col],int row,int col)
{
    block *p=blk;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(mat[i][j]==1)
            {
                while(p) {
                    p = block_Search(&blk, i, j);
                    if (p != nullptr) {
                        p->m[p->t] = i;
                        p->n[p->t] = j;
                        p->t = p->t + 1;
                    }
                    ++p;
                }

            }
        }
    }
}


#endif //ZUOYE_2_CHAIN_DEF_H
