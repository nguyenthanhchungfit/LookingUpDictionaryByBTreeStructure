#include "IO_STREAM.h"

int main() {

	string dicData = "dict.txt";
	string resultPath = "result.txt";
	string textPath = "text.txt";
	
	B_TREE* dict = new B_TREE();
	readAndCreateDictionary(dicData, dict);
	writeResult(resultPath, textPath, dict);
	delete dict;


	system("pause");
	return 0;
}