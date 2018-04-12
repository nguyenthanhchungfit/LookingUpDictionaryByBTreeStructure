
#include "IO_STREAM.h"



bool readAndCreateDictionary(const string&path, B_TREE*dic){
	fstream myFile;
	char eWord[25];
	myFile.open(path, ios::in);
	if (myFile){
		string temp = "";
		while (1){
			temp = "";
			getline(myFile, temp);
			if (temp.size() == 0) break;
			strcpy_s(eWord, temp.c_str());
			dic->insertWord(eWord);
		}
		myFile.close();
		return true;
	}
	return false;
}

void writeInforTree(fstream& outFile, B_TREE*dic){
	outFile << "--Tree info" << endl;
	outFile << "+ Number of nodes: " << dic->countNode() << endl;
	outFile << "+ Size of each node: " << dic->sizeNode() << endl;
	outFile << "+ Max keys in each node: " << dic->maxNumberOfKeysInNode() << endl;
	outFile << "+ Min keys in each node: " << dic->minNumberOfKeysInNode() << endl;
	outFile << setprecision(4) << "+ Average fullfill: (%): " << dic->averageFullFillNode() << endl;
	outFile << "+ Number of leaf-nodes: " << dic->numberOfLeaf_Node() << endl;
	outFile << "+ Height of tree: " << dic->height() << endl;
}

void writeSearchKey(fstream& outFile, fstream& textFile, B_TREE*dic){
	outFile << "--Spelling result" << endl;
	char keyWord[25];
	string keyStr = "";
	string path = "";
	while (textFile >> keyStr){
		path = "R";
		unsigned int lastChaIndex = keyStr.size() - 1;
		if (keyStr[lastChaIndex] == '.' || keyStr[lastChaIndex] == ','){
			keyStr.erase(lastChaIndex);
		}
		strcpy_s(keyWord, keyStr.c_str());
		if (dic->searchKey(keyWord, path) == false){
			outFile<< "+ " << keyStr << ": " << path << endl;
		}
	}

}

bool writeResult(const string&pathOut, const string& pathText, B_TREE*dic){
	fstream outFile;
	fstream textFile;
	outFile.open(pathOut, ios::out);
	textFile.open(pathText, ios::in);
	if (outFile){

		// write Infor
		writeInforTree(outFile, dic);
		if (textFile){
			// Write Search
			writeSearchKey(outFile, textFile, dic);
			textFile.close();
		}
		outFile.close();
		return true;
	}
	return false;
}


