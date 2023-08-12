#include "esp_system.h"

extern size_t get_free_heap_size(){
    return esp_get_free_heap_size();
}

extern size_t get_min_free_heap_size(){
    return esp_get_minimum_free_heap_size();
}

extern void print_mem_info(){
    printf("Free heap size: %u bytes\n", get_free_heap_size());
    printf("Minimum free heap size: %u bytes\n", get_min_free_heap_size());
}