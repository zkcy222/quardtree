#ifndef _RANGEQUERY_H_
#define _RANGEQUERY_H_
#include"QuadTree.h"
#include<vector>

void RangeQuery(int x, int y, double r, QuadTree quadTree, vector<ItemInfo>& queryResult);

#endif