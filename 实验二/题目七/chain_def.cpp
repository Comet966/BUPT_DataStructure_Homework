//
// Created by Comet on 2025/12/11.
//

#include "chain_def.h"


bool block_is_empty(block* blk)
{
    if(blk->m[0]==-1 && blk->n[0]==-1 )
    {
        return true;
    }
    return false;
}

void block_initial(block* blk)//设置哨兵值
{
    std::fill(blk->m,blk->m+Max_Num-1,-1);
    blk->t =0;
}

bool block_search(block* blk,int m1,int n1)
{
    block*p=blk;
    for (int i = 0; i <Max_Num; ++i) {
        if(p->m[i] == m1 && p->n[i] == n1)return true;
    }
    return false;
}

block* block_Search(block blk[],int m1,int n1)
{
    block*p = blk;
    while(p)
    {
        if(block_search(p,m1,n1))return p;
        ++p;
    }
    return nullptr;
}


