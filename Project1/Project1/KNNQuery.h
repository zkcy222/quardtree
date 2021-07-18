#ifndef _KNNQUERY_H_
#define _KNNQUERY_H_
#include "QuadTree.h"
#include <vector>
double MINDIST(int x, int y, MapRect R);

void KNNQuary(int x, int y, int k,QuadTree quadTree, vector<ItemInfo>& queryResult);

#endif // !_KNNQUERY_H_
