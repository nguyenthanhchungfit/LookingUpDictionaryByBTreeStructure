#include "B_TREE.h"


// Constructor, Destructor

B_TREE::B_TREE()
{
	root = NULL;
}

B_TREE::B_TREE(const B_TREE&)
{

}

void B_TREE::sRemoveAllNode(B_NODE_TREE *&p){
	if (p != NULL){
		for (int i = 0; i <= p->keyTally; i++){
			this->sRemoveAllNode(p->pointers[i]);
		}
		delete p;
		p = NULL;
	}
}

B_TREE::~B_TREE()
{
	this->sRemoveAllNode(root);
}

//----------------------------------------------------------------------------------------------------

// Create B-TREE

B_NODE_TREE* B_TREE::findMatchLeafNode(char eWord[25])
{
	int i = 0;
	B_NODE_TREE* p = root;
	B_NODE_TREE* q = NULL;
	while (p != NULL) {
		i = p->posOfFirstKeyGreaterEqual(eWord);
		if (i < p->keyTally && strcmp(p->keysWord[i], eWord) == 0) {
			return NULL;           // Node có chứa khóa K
		}
		q = p;
		p = p->pointers[i];
	}
	return q; // Trả về node lá
}

bool B_TREE::insertWord(char eWord[25]) {
	if (root == NULL) {
		root = new B_NODE_TREE(eWord);
		return true;
	}
	else {

		// find a node leaf to insert K
		B_NODE_TREE* matchNode = this->findMatchLeafNode(eWord);
		if (matchNode == NULL) return false; // K chèn được
		B_NODE_TREE* pChild = NULL;
		while (1) {
			// find a proper position in array keys for K
			int posMatchKey = matchNode->posOfFirstKeyGreaterEqual(eWord);
			// if node is not full
			if (matchNode->keyTally < DegreeTree - 1) {
				matchNode->insertKeyNonFull(eWord, posMatchKey, pChild);
				matchNode->updateLeafNode();
				return true;
			}
			// if node is full
			else {
				/*
				else split node in node1 and node2 (node 1 = node, node2 is new)
				distribute keys and pointers evenly between node1, and node2
				and initialize properly their keyTally
				*/
				// count midIndex and update KeyTallyNode2
				B_NODE_TREE* node2 = new B_NODE_TREE();
				if (node2 == NULL) return false;
				int mid = DegreeTree / 2;
				node2->keyTally = mid;
				if (DegreeTree % 2 == 0){
					mid--;
				}
				matchNode->keyTally = mid + 1;
				matchNode->splitNode(node2, mid, posMatchKey, eWord, pChild);

				// K = the last key of node1;
				strcpy_s(eWord, 25, matchNode->keysWord[matchNode->keyTally - 1]);
				matchNode->keyTally--;
				// Delete key and pointer of node
				matchNode->deleteKeyPointer(mid);
				matchNode->updateLeafNode();
				node2->updateLeafNode();

				matchNode->updateParent();
				node2->updateParent();

				// Update Brother
				node2->pRightBrother = matchNode->pRightBrother;
				matchNode->pRightBrother = node2;

				/*
				if node was the root
				create a new root as parent of node1 and node2;
				put K and pointers to node1 and node2 in the root, and set its keyTally to 1;
				return;
				*/
				if (root == matchNode){
					B_NODE_TREE* newRoot = new B_NODE_TREE(eWord);
					if (newRoot == NULL) return false;
					matchNode->parent = node2->parent = newRoot;
					newRoot->pointers[0] = matchNode;
					newRoot->pointers[1] = node2;
					root = newRoot;
					root->updateLeafNode();
					return true;
				}
				else{ // not root
					//else node = its parent; // process the node's parent;
					matchNode = matchNode->parent;
					pChild = node2;
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------

// Count node
unsigned int B_TREE::countNode(){
	B_NODE_TREE *p = root;
	B_NODE_TREE* q = NULL;
	unsigned int numberNode = 0;
	while (p){
		q = p;
		while (q){
			numberNode++;
			q = q->pRightBrother;
		}
		p = p->pointers[0];
	}
	return numberNode;
}

// count Average Full Fill
double B_TREE::sCountPercentFillNode(){
	B_NODE_TREE *p = root;
	B_NODE_TREE* q = NULL;
	double countFill = 0;
	while (p){
		q = p;
		while (q){
			countFill += q->countPercentFillNode();
			q = q->pRightBrother;
		}
		p = p->pointers[0];
	}
	return countFill;
}

double B_TREE::averageFullFillNode(){
	double sumPercent = this->sCountPercentFillNode();
	unsigned int nNode = this->countNode();
	return (sumPercent / nNode) * 100;
}


// count the max numbers of key in a node
unsigned short int B_TREE::maxNumberOfKeysInNode(){
	B_NODE_TREE *p = root;
	B_NODE_TREE* q = NULL;
	unsigned short int maxNode = 0;
	while (p){
		q = p;
		while (q){
			if (maxNode < q->keyTally)
				maxNode = q->keyTally;
			q = q->pRightBrother;
		}
		p = p->pointers[0];
	}
	return maxNode;
}


// count the min numbers of key in a node
unsigned short int B_TREE::minNumberOfKeysInNode(){
	B_NODE_TREE *p = root;
	B_NODE_TREE* q = NULL;
	unsigned short int minNode = DegreeTree - 1;
	while (p){
		q = p;
		while (q){
			if (minNode > q->keyTally)
				minNode = q->keyTally;
			q = q->pRightBrother;
		}
		p = p->pointers[0];
	}
	return minNode;
}


// Height
unsigned short int B_TREE::height(){
	B_NODE_TREE* p = root;
	unsigned short int h = 0;
	while (p){
		h++;
		p = p->pointers[0];
	}
	return h;
}


// Search
bool B_TREE::searchKey(char eWord[25], string& path){
	//return this->sSearchKey(root, eWord);
	int i = 0;
	B_NODE_TREE* p = root;
	while (p != NULL) {
		i = p->posOfFirstKeyGreaterEqual(eWord);
		if (i< p->keyTally && strcmp(p->keysWord[i], eWord) == 0) {
			return true;           // Node có chứa khóa K
		}	
		path = path + " " + to_string(i);
		p = p->pointers[i];
	}
	return false;
}


// Size Node
unsigned short int B_TREE::sizeNode(){
	return sizeof(B_NODE_TREE);
}


// Count Leaf Node
unsigned int B_TREE::numberOfLeaf_Node(){
	B_NODE_TREE* p = root;
	// find leaf node
	while (p){
		if (p->leaf) break;
		p = p->pointers[0];
	}
	unsigned int count = 0;
	B_NODE_TREE* q = p;
	while (q){
		count++;
		q = q->pRightBrother;
	}
	return count;
}



