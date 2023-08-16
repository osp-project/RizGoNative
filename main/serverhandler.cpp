#include "esp_http_server.h"
#include <cryptotool.cpp>
#include <serverhandlerutil.cpp>
#include <sysmemtool.h>
#include <iostream>
#include <charsetutils.h>

//以下为没有什么大用的测试用途handler定义，可以不看

std::string pem_test_private_key_str = "-----BEGIN PRIVATE KEY-----\n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\n-----END PRIVATE KEY-----";


esp_err_t do_rsa_test_get_handler(httpd_req_t *req)
{
    printf("收到do_rsa测试请求\n");

    char* urlquery = get_req_query(req);

    std::string rsatext = convert_to_utf8(get_value(urlquery,"text"));

    std::cout << "收到RSA加密测试请求，text=" << rsatext << std::endl;

    std::string encrypt_ret = rsa_encrypt_pkcs1(pem_test_private_key_str,rsatext);

    httpd_resp_send(req, encrypt_ret.c_str(), HTTPD_RESP_USE_STRLEN); //发送响应内容给客户端

    std::cout << "密文返回：" << encrypt_ret << std::endl;

    print_mem_info();
    
    return ESP_OK;
}

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

    std::string encrypt_ret = aes_256_cbc_encrypt(aeskey,aesiv,aestext);

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

httpd_uri_t rsa_test_get = {
    .uri = "/do_rsa",
    .method = HTTP_GET,
    .handler = do_rsa_test_get_handler,
    .user_ctx = NULL
};

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