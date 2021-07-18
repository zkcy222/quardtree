#ifndef _WINDOWQUERY_H_
#define _WINDOWQUERY_H_
#include"QuadTree.h"
#include<vector>

void WindowQuery(MapRect queryRectangle, QuadTree quadTree, vector<ItemInfo>& queryResult);

#endif