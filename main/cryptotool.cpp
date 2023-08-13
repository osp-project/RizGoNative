#include <aes.h>
#include <string>
#include <array>
#include <algorithm>
#include <base64.h>

// A function to pad the text with PKCS7 padding scheme
std::string pkcs7_pad(const std::string& text, int block_size) {
    int pad_len = block_size - (text.size() % block_size); // Calculate the padding length
    char pad_char = static_cast<char>(pad_len); // Convert the padding length to a char
    std::string padded_text = text; // Copy the original text
    padded_text.append(pad_len, pad_char); // Append the padding char to the end of the text
    return padded_text; // Return the padded text
}

// A function to encrypt the text with AES-256 CBC mode and return the base64 encoded ciphertext
std::string aes_256_cbc_encrypt(const std::string& key, const std::string& iv, const std::string& text) {
    struct AES_ctx ctx; // Create an AES context
    AES_init_ctx_iv(&ctx, reinterpret_cast<const uint8_t*>(key.data()), reinterpret_cast<const uint8_t*>(iv.data())); // Initialize the context with the key and iv
    std::string padded_text = pkcs7_pad(text, 16); // Pad the text with PKCS7 padding scheme
    uint8_t* buffer = new uint8_t[padded_text.size()]; // Allocate a buffer to store the encrypted data
    std::copy(padded_text.begin(), padded_text.end(), buffer); // Copy the padded text to the buffer
    AES_CBC_encrypt_buffer(&ctx, buffer, padded_text.size()); // Encrypt the buffer with AES-256 CBC mode
    std::string base64_ciphertext = base64_encode(buffer, padded_text.size()); // Encode the encrypted buffer with base64
    delete[] buffer; // Free the buffer memory
    return base64_ciphertext; // Return the base64 encoded ciphertext
}