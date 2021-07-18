#include"KNNQuery.h"
//点q与rect R最小距离
double MINDIST(int x, int y, MapRect R) {
	if (x >= R.minX && x <= R.maxX && y > R.minY && y <= R.maxY) {
		return 0;
	}
	if (x >= R.minX && x <= R.maxX) {
		if (y > R.maxY) {
			return y - R.maxY;
		}
		else {
			return R.minY - y;
		}
	}
	if (y >= R.minY && y <= R.maxY) {
		if (x > R.maxX) {
			return x - R.maxX;
		}
		else {
			return R.minX - x;
		}
	}
	double a = pow(pow(x - R.maxX, 2) + pow(y - R.maxY, 2), 0.5);
	double b = pow(pow(x - R.minX, 2) + pow(y - R.maxY, 2), 0.5);
	double c = pow(pow(x - R.minX, 2) + pow(y - R.minY, 2), 0.5);
	double d = pow(pow(x - R.maxX, 2) + pow(y - R.minY, 2), 0.5);
	if (b < a)a = b;
	if (c < a)a = c;
	if (d < a)a = d;
	return a;
}

//点点距离
double actualDistance(int x, int y, ItemInfo item) {
	//std::cout <<item.ID<<" " << pow(pow(x - item.x, 2) + pow(y - item.y, 2), 0.5) << endl;
	return pow(pow(x - item.x, 2) + pow(y - item.y, 2), 0.5);
	
}

void KQ(int x, int y, int *k, QuadNode quadNode, vector<ItemInfo>& queryResult) {
	//一个或没有结点直接退出
	if (quadNode.itemCount == 1) {
		if (*k > 0) {
			(*k)--;
			//插入
			int resultN = queryResult.size();
			for (int i = 0; i < resultN; i++) {
				if (actualDistance(x, y, quadNode.Obj) < actualDistance(x, y, queryResult[i])) {
					queryResult.insert(queryResult.begin() + i, quadNode.Obj);
					break;
				}
				if (i == queryResult.size() - 1) {
					queryResult.push_back(quadNode.Obj);
				}
			}
			if (queryResult.size() == 0) {
				queryResult.push_back(quadNode.Obj);
			}
			//queryResult.push_back(quadNode.Obj);
		}
		else {
			//检查是否需要替换
			for (int i = 0; i < queryResult.size(); i++) {
				if (actualDistance(x, y, quadNode.Obj) < actualDistance(x, y, queryResult[i])) {
					queryResult.insert(queryResult.begin() + i, quadNode.Obj);
					queryResult.pop_back();
					break;
				}
			}
		}

	}
	if (quadNode.itemCount == 0) {
		return;
	}
	//四个子节点排序
	if (quadNode.itemCount > 1) {
		QuadNode* l[4];
		for (int i = 0; i < 4; i++) {
			l[i] = quadNode.children[i];
		}
		for (int i = 0; i < 4; i++) {
			for (int i1 = i; i1 < 4; i1++) {
				if (MINDIST(x, y, l[i]->rect) > MINDIST(x, y, l[i1]->rect)) {
					QuadNode* aaa = l[i];
					l[i] = l[i1];
					l[i1] = aaa;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			KQ(x, y, k, *l[i], queryResult);
		}
	}
	return;
}

void KNNQuary(int x, int y, int k, QuadTree quadTree, vector<ItemInfo>& queryResult) {
	vector<ItemInfo> qr;
	KQ(x, y, &k, *quadTree.root, qr);
	queryResult = qr;
}