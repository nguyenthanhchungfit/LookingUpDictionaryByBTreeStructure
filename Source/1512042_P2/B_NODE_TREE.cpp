#include "B_NODE_TREE.h"

// Constructor, Destructor

B_NODE_TREE::B_NODE_TREE()
{
	leaf = true;
	keyTally = 0;
	pRightBrother  = parent = NULL;
	for (unsigned int i = 0; i < DegreeTree - 1; i++) {
		strcpy_s(keysWord[i], "");
		pointers[i] = NULL;
	}
	pointers[DegreeTree - 1] = NULL;
}


B_NODE_TREE::B_NODE_TREE(char eWord[25])
{
	leaf = true;
	keyTally = 1;
	pRightBrother = parent = NULL;
	for (unsigned int i = 0; i < DegreeTree - 1; i++) {
		pointers[i] = NULL;
		strcpy_s(keysWord[i], "");
	}
	pointers[DegreeTree - 1] = NULL;
	strcpy_s(keysWord[0], eWord);
}


B_NODE_TREE::~B_NODE_TREE()
{
}

//----------------------------------------------------------------------------------------------------

// Operation

void B_NODE_TREE::deleteKeyPointer(const int& index){
	for (int i = index; i < DegreeTree - 1; i++){
		strcpy_s(keysWord[i], "");
		pointers[i + 1] = NULL;
	}
}

int B_NODE_TREE::posOfFirstKeyGreaterEqual(char eWord[25]) {
	int i = 0;
	while (i < keyTally && strcmp(keysWord[i], eWord) < 0) {
		i++;
	}
	return i;
}

void B_NODE_TREE::insertKeyNonFull(char eWord[25], const int& pos, B_NODE_TREE* pChild) {
	keyTally++;
	if (pos != DegreeTree - 2){
		int i = keyTally - 1;
		while (i > pos) {
			strcpy_s(keysWord[i], keysWord[i - 1]);
			pointers[i + 1] = pointers[i];
			i--;
		}
	}
	pointers[pos + 1] = pChild;
	if (pChild){
		pChild->parent = this;
	}
	strcpy_s(keysWord[pos], eWord);
}

void B_NODE_TREE::splitNode(B_NODE_TREE* node2, const int& mid, const int& postInsert,
	char eWord[25], B_NODE_TREE* pChild){
	if (postInsert <= mid){
		// Copy mid+1 -> DegreeTree - 2
		int iNode2 = 0;
		for (int i = mid; i < DegreeTree - 1; i++){
			strcpy_s(node2->keysWord[iNode2], this->keysWord[i]);
			node2->pointers[iNode2] = this->pointers[i];
			iNode2++;
		}
		node2->pointers[iNode2] = this->pointers[DegreeTree - 1];

		// insert eWord into mid
		this->keyTally--;
		this->insertKeyNonFull(eWord, postInsert, pChild);

		// update new pointer for node2
		if (postInsert == mid){
			node2->pointers[0] = pChild;
			if (pChild)
				pChild->parent = node2;
		}
	}
	else{
		int iNode2 = 0;
		for (int i = mid + 1; i < DegreeTree - 1; i++){
			strcpy_s(node2->keysWord[iNode2], this->keysWord[i]);
			node2->pointers[iNode2] = this->pointers[i];
			iNode2++;
		}
		node2->pointers[iNode2] = this->pointers[DegreeTree - 1];
		// insert eWord into mid
		node2->keyTally--;
		node2->insertKeyNonFull(eWord, postInsert - mid - 1, pChild);
	}
}

void B_NODE_TREE::updateLeafNode(){
	for (int i = 0; i <= keyTally; i++){
		if (pointers[i]){
			leaf = false;
			return;
		}
	}
}

void B_NODE_TREE::updateParent(){
	for (unsigned int i = 0; i <= keyTally; i++){
		if (pointers[i]){
			pointers[i]->parent = this;
		}
		else{
			break;
		}
	}
}

B_NODE_TREE* B_NODE_TREE::getNode(const int& index){
	if (index <= keyTally && index >= 0)
		return this->pointers[index];
	return NULL;
}

double B_NODE_TREE::countPercentFillNode() const{
	return keyTally*1.0 / (DegreeTree - 1);
}





