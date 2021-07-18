#include <iostream>
#include <vector>
#include "QuadTree.h"
#include "WindowQuery.h"
#include"RangeQuery.h"
#include"KNNQuery.h"
using namespace std;

int main()
{
	//测试数据
	//  0123456789
	//0 ***********
	//9 ***********
	//8 ***********
	//7 ***********
	//6 ***********
	//5 *****4*****
	//4 ****3******
	//3 ***2*******
	//2 **1********
	//1 *0*********
	//0 ***********
	MapRect map(0, 10, 0, 10);
	ItemInfo itemList[5];
	int itemPos[5][2] = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
	for (int i = 0; i < 5; i++)
		itemList[i] = ItemInfo(i, itemPos[i][0], itemPos[i][1]);

	//构建quadtree
	QuadTree qtree = QuadTree();
	CreateQuadTree(map, 5, itemList, &qtree);
	//PrintQuadTree(&qtree);

	//三种query测试
	//window query
	MapRect queryRectangle(0, 3, 0, 3);
	vector<ItemInfo> wqqr;
	WindowQuery(queryRectangle, qtree, wqqr);
	cout << "window query:" << endl;
	for (int i = 0; i < wqqr.size(); i++) {
		wqqr[i].Print();
	}


	//KNN query
	vector<ItemInfo> KNNqr;
	KNNQuary(1, 5, 3, qtree, KNNqr);
	cout << "KNN query:" << endl;
	for (int i = 0; i < KNNqr.size(); i++) {
		KNNqr[i].Print();
	}

	//range query
	vector<ItemInfo> rqqr;
	RangeQuery(1, 1, pow(2, 0.5) - 0.00001, qtree, rqqr);
	cout << "range query:" << endl;
	for (int i = 0; i < rqqr.size(); i++) {
		rqqr[i].Print();
	}
	return 0;
}
