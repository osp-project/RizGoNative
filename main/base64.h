// 假设您的.h文件名为base64.h
#ifndef BASE64_H // 防止头文件重复包含
#define BASE64_H

#include <string> // 包含string头文件
#include <vector> // 包含vector头文件

typedef unsigned char BYTE; // 定义BYTE类型为unsigned char

// 声明两个全局函数，与.cpp文件中的定义相同
std::string base64_encode(BYTE const* buf, unsigned int bufLen);
std::vector<BYTE> base64_decode(std::string const& encoded_string);

#endif
