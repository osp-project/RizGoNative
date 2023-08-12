#include "esp_http_server.h"
#include <string>
#include <map>

// 定义一个函数，传入 req 和 key ，返回 value
char* get_req_query(httpd_req_t *req) {
    // 获取查询字符串长度
    size_t query_len = httpd_req_get_url_query_len(req);
    // 如果查询字符串为空或不存在，返回 NULL
    if (query_len == 0) {
        return NULL;
    }
    // 分配一个合适大小的缓冲区来存储查询字符串（长度加 1）
    char *query = (char*)malloc(query_len + 1);
    // 如果内存分配失败，返回 NULL
    if (query == NULL) {
        return NULL;
    }
    // 获取查询字符串内容
    esp_err_t err = httpd_req_get_url_query_str(req, query, query_len + 1);
    // 如果获取失败，释放内存并返回 NULL
    if (err != ESP_OK) {
        free(query);
        return NULL;
    }

    return query;
}

// 定义一个函数，参数是两个char *类型的字符串
std::string get_value(char *str, char *key) {
    // 定义一个map容器，用来存储键值对
    std::map<std::string, std::string> kv_map;
    // 定义两个std::string类型的变量，用来转换char *类型的字符串
    std::string s(str), k(key);
    // 定义两个变量，用来记录键值对的起始和结束位置
    size_t start = 0, end = 0;
    // 循环遍历字符串，直到找不到&符号为止
    while ((end = s.find('&', start)) != std::string::npos) {
        // 找到=符号的位置
        size_t pos = s.find('=', start);
        // 如果找到了=符号，并且它在&符号之前
        if (pos != std::string::npos && pos < end) {
        // 截取键和值的子字符串，并插入到map容器中
        kv_map.insert({s.substr(start, pos - start), s.substr(pos + 1, end - pos - 1)});
        }
        // 更新起始位置为&符号之后的位置
        start = end + 1;
    }
    // 处理最后一个键值对，如果没有&符号，那么结束位置就是字符串的末尾
    end = s.length();
    // 找到=符号的位置
    size_t pos = s.find('=', start);
    // 如果找到了=符号，并且它在结束位置之前
    if (pos != std::string::npos && pos < end) {
        // 截取键和值的子字符串，并插入到map容器中
        kv_map.insert({s.substr(start, pos - start), s.substr(pos + 1, end - pos - 1)});
    }
    // 在map容器中查找给定的键，如果找到了，就返回对应的值，否则返回空字符串
    auto it = kv_map.find(k);
    if (it != kv_map.end()) {
        return it->second;
    } else {
        return "";
    }
}