#include "WindowQuery.h"
#include "QuadTree.h"
#include <vector>

//检测两个rect是否相交
bool IfIntersect(MapRect r1, MapRect r2) {
	if (r1.minX > r2.maxX || r1.maxX<r2.minX || r1.minY>r2.maxY || r1.maxY < r2.minY)
		return false;
	return true;
}
//递归遍历
void WQ(MapRect queryRectangle, QuadNode quadNode, vector<ItemInfo>& queryResult) {
	if (quadNode.itemCount == 1 && ifInRect(quadNode.Obj, queryRectangle)) {
		queryResult.push_back(quadNode.Obj);
		return;
	}
	if (quadNode.itemCount > 1 && quadNode.children[0] != NULL) {
		for (int i = 0; i < 4; i++) {
			if (IfIntersect(quadNode.children[i]->rect, queryRectangle) && quadNode.children[i]->itemCount > 0) {
				WQ(queryRectangle, *quadNode.children[i], queryResult);
			}
		}
	}
}

void WindowQuery(MapRect queryRectangle, QuadTree quadTree, vector<ItemInfo>& queryResult) {
	vector<ItemInfo> qr;
	WQ(queryRectangle, *quadTree.root, qr);
	queryResult = qr;
}

