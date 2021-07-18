#include "WindowQuery.h"
#include "QuadTree.h"
#include <vector>
//检测地点是否在圆内
bool ifInRect(int x, int y, double r, ItemInfo item) {
	if ((r * r) >= ((x - item.x) * (x - item.x) + (y - item.y) * (y - item.y))) {
		return true;
	}
	return false;
}

//检测两个rect是否相交
bool IfIntersect(int x, int y, double r, MapRect rect) {
	if ((x - r > rect.maxX || x + r<rect.minX || y - r>rect.maxY || y + r < rect.minY) &&
		((r * r) <= ((x - rect.maxX) * (x - rect.maxX) + (y - rect.maxY) * (y - rect.maxY))) &&
		((r * r) <= ((x - rect.minX) * (x - rect.minX) + (y - rect.maxY) * (y - rect.maxY))) &&
		((r * r) <= ((x - rect.maxX) * (x - rect.maxX) + (y - rect.minY) * (y - rect.minY))) &&
		((r * r) <= ((x - rect.minX) * (x - rect.minX) + (y - rect.minY) * (y - rect.minY))))
		return false;
	return true;
}
//递归遍历
void RQ(int x, int y, double r, QuadNode quadNode, vector<ItemInfo>& queryResult) {
	if (quadNode.itemCount == 1 && ifInRect(x, y, r, quadNode.Obj)) {
		queryResult.push_back(quadNode.Obj);
		return;
	}
	if (quadNode.itemCount > 1 && quadNode.children[0] != NULL) {
		for (int i = 0; i < 4; i++) {
			if (IfIntersect(x, y, r, quadNode.children[i]->rect) && quadNode.children[i]->itemCount > 0) {
				RQ(x, y, r, *quadNode.children[i], queryResult);
			}
		}
	}
}

void RangeQuery(int x, int y, double r, QuadTree quadTree, vector<ItemInfo>& queryResult) {
	vector<ItemInfo> qr;
	RQ(x, y, r, *quadTree.root, qr);
	queryResult = qr;
}



