#pragma once
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int DegreeTree = 18; // Lưu bậc của cây
const int ByteUnused = 0; // Mảng lấp đầy

class B_NODE_TREE
{
	
public:
	// Mô tả cấu trúc
	unsigned short int keyTally;		// Lưu số eWord(key) hiện tại của node
	B_NODE_TREE* pointers[DegreeTree];  // Lưu các con trỏ trỏ tới các node con
	B_NODE_TREE* parent;				// Lưu con trỏ trỏ tới node cha
	B_NODE_TREE* pRightBrother;			// Lưu con trỏ trỏ tới node anh em bên phải
	char keysWord[DegreeTree - 1][25];  // Lưu các eWord(key) của node
	bool leaf;							// Lưu cờ có phải node lá hay không?
	char unused[ByteUnused];			// Lưu mảng lấp đầy

	// Constructor, destructor
	B_NODE_TREE();
	B_NODE_TREE(char eWord[25]);
	~B_NODE_TREE();

	// Operation
	// Xóa key và Pointer trong một node từ vị trí index
	void deleteKeyPointer(const int& index);
	// Lấy vị trí đầu tiên mà eWord lớn hơn hoặc bằng eWord trong Node
	int posOfFirstKeyGreaterEqual(char eWord[25]);
	// Chèn một eWord vào node chưa đầy tại vị trí pos kèm theo con pChild
	void insertKeyNonFull(char eWord[25], const int& pos, B_NODE_TREE* pChild);
	// Cắt node this sang node2 tại vị trí trung gian mid, vị trí chèn postInsert của eWord trong node this kèm con pChild
	void splitNode(B_NODE_TREE* node2, const int& mid, const int& postInsert, char eWord[25], B_NODE_TREE* pChild);
	// Cập nhập lại node lá
	void updateLeafNode();
	// Cập nhật node cha
	void updateParent();
	// Lấy node tại vị trí
	B_NODE_TREE* getNode(const int&);
	// Tính độ fill của node
	double countPercentFillNode() const;
	
};





