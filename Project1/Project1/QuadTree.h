#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <iostream>
using namespace std;

//地图区域
typedef struct MapRect
{
	int minX;
	int minY;
	int maxX;
	int maxY;
	MapRect() = default;
	//初始化
	MapRect(int x, int xx, int y, int yy)
	{
		minX = x;
		maxX = xx;
		minY = y;
		maxY = yy;
	}
	/*分为四个区域
	b | a
	--+--
	c | d
	*/
	void Split(MapRect* a)
	{
		int midX = (maxX + minX) / 2;
		int midY = (maxY + minY) / 2;
		a[0] = MapRect(midX + 1, maxX, midY + 1, maxY);
		a[1] = MapRect(minX, midX, midY + 1, maxY);
		a[2] = MapRect(minX, midX, minY, midY);
		a[3] = MapRect(midX + 1, maxX, minY, midY);
		for (int i = 0; i < 4; i++) {

		}
	}

	void print()
	{
		cout << "minX:" << minX << endl
			<< "maxX:" << maxX << endl
			<< "minY:" << minY << endl
			<< "maxX:" << maxY << endl;
	}
} MapRect;

//位置信息
typedef struct ItemInfo
{
	int ID;
	int x;
	int y;
	ItemInfo() = default;
	ItemInfo(int id, int xx, int yy)
	{
		ID = id;
		x = xx;
		y = yy;
	}
	void Print() {
		cout << "id:" << ID << " x:" << x << " y:" << y << endl;
	}
} ItemInfo;

//四叉树节点类型结构
typedef struct QuadNode
{
	MapRect rect;          //节点范围
	int itemCount;         // 物体个数
	ItemInfo Obj;          //物体
	QuadNode* children[4]; //子节点
} QuadNode;

//四叉树类型结构
typedef struct QuadTree
{
	QuadNode* root;
} QuadTree;

//初始化四叉树节点
QuadNode* InitQuadNode();

//构建四叉树
void CreateQuadTree(MapRect maprect, int n, ItemInfo itemList[], QuadTree* quadTree);

//构建分支
void CreateQuadBranch(MapRect maprect, int n, ItemInfo itemList[], QuadNode** node);

//判断物体是否在范围内
bool ifInRect(ItemInfo a, MapRect rect);

//打印树
void PrintQuadTree(QuadTree* tree);
void PrintQuadNode(QuadNode node);

#endif