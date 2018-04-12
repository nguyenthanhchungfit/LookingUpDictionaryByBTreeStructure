#pragma once
#include <fstream>
#include <string>
#include <iomanip>
#include "B_TREE.H"


// Đọc eWord từ file với đường dẫn path và chèn vào từ điển
bool readAndCreateDictionary(const string&path, B_TREE*dic);

// Ghi ra file thông tin của cây từ điển 
void writeInforTree(fstream& outFile, B_TREE*dic);

// Ghi ra file các từ khóa không tìm kiếm thấy trong dic ở file textFile
void writeSearchKey(fstream& outFile, fstream& textFile, B_TREE*dic);

// Ghi ra file kết quả
bool writeResult(const string&pathOut, const string& pathText, B_TREE*dic);



