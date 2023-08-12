#ifndef SYS_MEM_TOOL_H // 防止头文件重复包含
#define SYS_MEM_TOOL_H

#include "esp_system.h" // 包含esp_system.h头文件

// 声明三个外部函数，与.cpp文件中的定义相同
extern size_t get_free_heap_size();
extern size_t get_min_free_heap_size();
extern void print_mem_info();

#endif