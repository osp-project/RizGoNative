#include <mbedtls/aes.h>
#include <string>
#include <array>
#include <algorithm>
#include <base64.h>

// 定义一个常量，表示 key 的长度（位）
constexpr size_t KEY_LENGTH = 256;

// 定义一个常量，表示 aes 的块大小（字节）
constexpr size_t AES_BLOCK_SIZE = 16;

// 定义一个 aes 上下文
mbedtls_aes_context aes;

bool aesinit = false;

// 定义一个加密函数，接受 std::string 类型的 key, iv, 和明文，并返回 std::string 类型的密文
std::string EncryptAes(const std::string& key, const std::string& iv, const std::string& plaintext) {
    //printf("AES Encrypt > 被调用\n");

    // 转换 key 和 iv 为 std::array<uint8_t, AES_BLOCK_SIZE>
    std::array<uint8_t, AES_BLOCK_SIZE> key_uint8;
    std::array<uint8_t, AES_BLOCK_SIZE> iv_uint8;
    std::copy_n(key.begin(), AES_BLOCK_SIZE, key_uint8.begin());
    std::copy_n(iv.begin(), AES_BLOCK_SIZE, iv_uint8.begin());

    // 转换 plaintext 为 uint8_t*
    size_t len = plaintext.size();
    uint8_t* plaintext_uint8 = new uint8_t[len];
    std::copy_n(plaintext.begin(), len, plaintext_uint8);

    //printf("AES Encrypt > 初始化完成\n");

    // 对 plaintext 进行填充，使其长度为 AES_BLOCK_SIZE 的倍数
    uint8_t padByte = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    len += padByte;
    uint8_t* padded_plaintext = new uint8_t[len];
    std::copy_n(plaintext_uint8, len - padByte, padded_plaintext);
    std::fill_n(padded_plaintext + len - padByte, padByte, padByte);
    delete[] plaintext_uint8;

    //printf("AES Encrypt > 明文填充完毕\n");

    if(!aesinit){
        // 初始化 aes 上下文
        mbedtls_aes_init(&aes);
        aesinit = true;
    }

    // 设置加密密钥
    mbedtls_aes_setkey_enc(&aes, key_uint8.data(), KEY_LENGTH);

    //printf("AES Encrypt > mbedtls组件初始化完毕\n");

    // 定义一个输出数组
    uint8_t* output = new uint8_t[len];

    // 执行加密操作
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, len, iv_uint8.data(), padded_plaintext, output);

    delete[] padded_plaintext;

    // 使用 base64 编码库将输出数组转换为 std::string 类型
    std::string ciphertext = base64_encode(output, len);

    delete[] output;

    // 返回密文字符串
    return ciphertext;

}