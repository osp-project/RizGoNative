#define OS_RNG_AVAILABLE
#define CRYPTOPP_DISABLE_ASM

#include <aes.h>
#include <string>
#include <array>
#include <algorithm>
#include <base64.h>
#include <cryptopp/rsa.h>
#include <cryptopp-pem/pem.h>
#include <cryptopp/base64.h>
#include <cryptopp/osrng.h>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>

using byte = unsigned char;

// 一个用PKCS7填充方案填充文本的函数
std::string pkcs7_pad(const std::string& text, int block_size) {
    int pad_len = block_size - (text.size() % block_size); // 计算填充长度
    char pad_char = static_cast<char>(pad_len); // 把填充长度转换成一个字符
    std::string padded_text = text; // 复制原始文本
    padded_text.append(pad_len, pad_char); // 在文本末尾追加填充字符
    return padded_text; // 返回填充后的文本
}

// 一个用AES-256 CBC模式加密文本并返回base64编码密文的函数
std::string aes_256_cbc_encrypt(const std::string& key, const std::string& iv, const std::string& text) {
    struct AES_ctx ctx; // 创建一个AES上下文
    AES_init_ctx_iv(&ctx, reinterpret_cast<const uint8_t*>(key.data()), reinterpret_cast<const uint8_t*>(iv.data())); // 用密钥和初始向量初始化上下文
    std::string padded_text = pkcs7_pad(text, 16); // 用PKCS7填充方案填充文本
    uint8_t* buffer = new uint8_t[padded_text.size()]; // 分配一个缓冲区来存储加密数据
    std::copy(padded_text.begin(), padded_text.end(), buffer); // 把填充后的文本复制到缓冲区
    AES_CBC_encrypt_buffer(&ctx, buffer, padded_text.size()); // 用AES-256 CBC模式加密缓冲区
    std::string base64_ciphertext = base64_encode(buffer, padded_text.size()); // 用base64编码加密后的缓冲区
    delete[] buffer; // 释放缓冲区内存
    return base64_ciphertext; // 返回base64编码的密文
}

// 一个用cryptopp计算字符串md5的函数
std::string md5_hash(const std::string& text) {
    CryptoPP::MD5 hash; // 创建一个MD5哈希对象
    byte digest[CryptoPP::MD5::DIGESTSIZE]; // 分配一个字节数组来存储摘要
    hash.CalculateDigest(digest, reinterpret_cast<const byte*>(text.data()), text.size()); // 计算字符串的摘要
    CryptoPP::HexEncoder encoder; // 创建一个十六进制编码器对象
    std::string output; // 创建一个字符串来存储输出
    encoder.Attach(new CryptoPP::StringSink(output)); // 把输出字符串附加到编码器上
    encoder.Put(digest, sizeof(digest)); // 把摘要放入编码器中
    encoder.MessageEnd(); // 结束消息处理
    return output; // 返回十六进制编码的摘要
}

// 输入PEM私钥文件的内容（std::string）和要加密的明文（std::string）
// 返回base64编码的加密结果（std::string）
std::string rsa_encrypt_pkcs1(const std::string& pem_private_key, const std::string& plain_text)
{
    // 创建RSA公钥对象
    CryptoPP::RSA::PrivateKey private_key;
    // 从PEM字符串中加载公钥
    CryptoPP::StringSource ss(pem_private_key, true);
    CryptoPP::PEM_Load(ss, private_key);
    // 创建PKCS1 v1.5加密方案对象
    CryptoPP::RSAES_PKCS1v15_Encryptor encryptor(private_key);
    // 创建随机数生成器
    CryptoPP::AutoSeededRandomPool rng;
    // 创建密文缓冲区
    std::string cipher_text;
    // 使用公钥和PKCS1 v1.5方案加密明文
    CryptoPP::StringSource(plain_text, true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::StringSink(cipher_text)));
    // 对密文进行base64编码
    std::string base64_cipher_text = base64_encode((BYTE*)cipher_text.data(), cipher_text.size());
    // 返回base64编码的密文
    return base64_cipher_text;
}