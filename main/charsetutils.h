#ifndef CHARSET_UTILS_H // 防止头文件重复包含
#define CHARSET_UTILS_H

#include <codecvt>
#include <string>

// 获取 ESP32-C3 的 MAC 地址并转换为一个 10 位数的 ID
std::string convert_to_utf8(const std::string& input);

#endif