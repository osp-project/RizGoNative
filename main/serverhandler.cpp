#include "esp_http_server.h"
#include <cryptotool.cpp>
#include <serverhandlerutil.cpp>
#include <sysmemtool.h>
#include <iostream>
#include <charsetutils.h>

//以下为没有什么大用的测试用途handler定义，可以不看

esp_err_t do_aes_test_get_handler(httpd_req_t *req)
{
    printf("收到do_aes测试请求\n");

    char* urlquery = get_req_query(req);

    //printf("读key\n");
    std::string aeskey = convert_to_utf8(get_value(urlquery,"key"));
    //printf("读iv\n");
    std::string aesiv = convert_to_utf8(get_value(urlquery,"iv"));
    //printf("读text\n");
    std::string aestext = convert_to_utf8(get_value(urlquery,"text"));
    //printf("调函数\n");

    std::cout << "收到AES加密测试请求，key=" << aeskey << " iv=" << aesiv << " text=" << aestext << std::endl;

    std::string encrypt_ret = EncryptAes(aeskey,aesiv,aestext);

    httpd_resp_send(req, encrypt_ret.c_str(), HTTPD_RESP_USE_STRLEN); //发送响应内容给客户端

    std::cout << "密文返回：" << encrypt_ret << std::endl;

    print_mem_info();
    
    return ESP_OK;
}

esp_err_t hello_get_handler(httpd_req_t *req)
{
    const char resp[] = "Welcome to RizGoNative\nIf you can see this message, it means RizGoNative is maybe working good. Please continue!"; //定义响应内容
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN); //发送响应内容给客户端
    return ESP_OK;
}

esp_err_t echo_post_handler(httpd_req_t *req)
{
    char content[100]; //定义接收缓冲区
    size_t recv_size = MIN(req->content_len, sizeof(content)); //获取接收数据的大小
    int ret = httpd_req_recv(req, content, recv_size); //接收客户端发送的数据
    if (ret <= 0) { 
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            //如果超时，发送 HTTP 408 错误给客户端
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }
    httpd_resp_send(req, content, recv_size); //将接收到的数据原样发送回客户端
    free(content);
    return ESP_OK;
}

httpd_uri_t aes_test_get = {
    .uri = "/do_aes",
    .method = HTTP_GET,
    .handler = do_aes_test_get_handler,
    .user_ctx = NULL
};

httpd_uri_t hello_get = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = hello_get_handler,
    .user_ctx = NULL
};

httpd_uri_t echo_post = {
    .uri = "/echo",
    .method = HTTP_POST,
    .handler = echo_post_handler,
    .user_ctx = NULL
};