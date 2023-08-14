#include "esp_http_server.h"
#include <serverhandler.cpp>

//定义一个创建 HTTP 服务器的函数
httpd_handle_t start_webserver(void)
{
    printf("正在启动HttpServer\n");
    httpd_config_t config = HTTPD_DEFAULT_CONFIG(); //获取默认的 HTTP 服务器配置
    httpd_handle_t server = NULL; //定义 HTTP 服务器的句柄
    if (httpd_start(&server, &config) == ESP_OK) { //创建 HTTP 服务器的实例
        //注册 URI 处理程序
        httpd_register_uri_handler(server, &hello_get);
        httpd_register_uri_handler(server, &echo_post);
        httpd_register_uri_handler(server, &aes_test_get);
        httpd_register_uri_handler(server, &rsa_test_get);
    }
    printf("HttpServer已启动\n");
    return server; //返回 HTTP 服务器的句柄
}

//定义一个停止 HTTP 服务器的函数
void stop_webserver(httpd_handle_t server)
{
    if (server) {
        //停止 HTTP 服务器，并释放相关资源
        httpd_stop(server);
    }
}