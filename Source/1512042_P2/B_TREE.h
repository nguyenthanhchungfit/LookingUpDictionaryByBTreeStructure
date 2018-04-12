#pragma once
#include <algorithm>
#include "B_NODE_TREE.h"


class B_TREE
{
private:
	B_NODE_TREE* root;	// Lưu node gốc của cây

	// Support function

	// Hàm xóa đệ quy các node
	void sRemoveAllNode(B_NODE_TREE *&p);

	// Hàm tính tổng độ fill của các node trong cây
	double sCountPercentFillNode();

	// Hàm tìm node leaf. (NULL k chèn đc)
	B_NODE_TREE* findMatchLeafNode(char eWord[25]);

//---------------------------------------------------------------------------------------
public:
	// Constructor, Destructor
	B_TREE();
	B_TREE(const B_TREE&);
	~B_TREE();

	// Main Functions

	// Hàm tính số node trong cây
	unsigned int countNode();

	// Tính size của 1 node
	unsigned short int sizeNode();

	// Tính số key max trong 1 node trong các node của cây
	unsigned short int maxNumberOfKeysInNode();

	// Tính số key min trong 1 node trong các node của cây
	unsigned short int minNumberOfKeysInNode();

	// Tín chiều cao của cây
	unsigned short int height();

	// Tính độ fill trung bình của các node trong cây
	double averageFullFillNode();

	// Tính số node lá
	unsigned int numberOfLeaf_Node();

	// Hàm tìm kiếm
	bool searchKey(char eWord[25], string& path);

	// Hàm chèn một từ mới vào trong cây
	bool insertWord(char eWord[25]);
};


