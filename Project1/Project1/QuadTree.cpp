#include "QuadTree.h"


bool ifInRect(ItemInfo a, MapRect rect) {
	if (a.x <= rect.maxX && a.x >= rect.minX && a.y >= rect.minY && a.y <= rect.maxY) {
		return true;
	}
	return false;
}

QuadNode* InitQuadNode()
{
	QuadNode* node = new QuadNode;
	node->rect = MapRect(0, 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		node->children[i] = NULL;
	}
	node->itemCount = 0;
	node->Obj = ItemInfo();

	return node;
}

void CreateQuadTree(MapRect maprect, int n, ItemInfo itemList[], QuadTree* quadTree) {
	CreateQuadBranch(maprect, n, itemList, &(quadTree->root));
}

void CreateQuadBranch(MapRect maprect, int n, ItemInfo itemList[], QuadNode** node)
{
	ItemInfo objList[100];
	for (int i = 0; i < n; i++) {
		objList[i] = itemList[i];
	}
	if (n > 0) {
		*node = InitQuadNode();
		QuadNode* pNode = *node;
		pNode->rect = maprect;
		pNode->itemCount = n;
		if (n > 1) {
			MapRect box[4];
			pNode->rect.Split(box);
			for (int i = 0; i < 4; i++)
			{
				pNode->children[i] = InitQuadNode();
				pNode->children[i]->rect = box[i];
				int nn = 0;
				for (int i1 = 0; i1 < n; i1++) {
					if (ifInRect(objList[i1], box[i])) {
						ItemInfo p = objList[nn];
						objList[nn] = objList[i1];
						objList[i1] = p;
						nn++;
					}
				}
				CreateQuadBranch(box[i], nn, objList, &(pNode->children[i]));
			}
		}
		else {
			pNode->Obj = itemList[0];
		}
	}
}

void PrintQuadTree(QuadTree *tree)
{
	//QuadNode root = ;
	PrintQuadNode(*tree->root);
}

void PrintQuadNode(QuadNode node)
{
	cout << node.Obj.x << " " << node.Obj.y << endl;
	for (int i = 0; i < 4; i++) {
		if (node.children[i] == NULL) {
			return;
		}
		PrintQuadNode(*node.children[i]);
	}
}