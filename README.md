# RizGoNative
RizServer的嵌入式版本，适用于ESP32全系芯片（Maybe support esp8266?），更多消息待公开

## 开源项目
多亏了一些开源项目，RizGoNative才得以实现如今的效果，我真诚地感谢它们：

[tiny-AES-c](https://github.com/kokke/tiny-AES-c) - Small portable AES128/192/256 in C 

[CryptoPP](https://github.com/weidai11/cryptopp) - free C++ class library of cryptographic schemes

[CryptoPP-PEM](https://github.com/noloader/cryptopp-pem) - PEM parsing of keys and parameters for Crypto++ project

[ESP-IDF](https://github.com/espressif/esp-idf) - Espressif IoT Development Framework. Official development framework for Espressif SoCs. 

我对`CryptoPP`做出了如下改动：

1. 修改了`osrng.h`，移除了一些有关`NONBLOCKING_RNG_AVAILABLE` `BLOCKING_RNG_AVAILABLE` `OS_RNG_AVAILABLE`等define的检测限制，ESP32与ESP8266等单片机显然不支持上述的RNG功能，便无法通过检测，因此我强制移除了这些检测，让程序强制执行下去，即便我明确的知道这样可能导致加密结果是不安全的，但能跑起来就行，并且对于本项目的实际需求而言，也不需要什么安全性

2. 修改了`osrng.cpp`，同上，移除了一些限制检测，使得程序能够在ESP32与ESP8266等单片机上运行

我对`CryptoPP-PEM`做出了如下改动：

1. 修改了`pem_common.cpp` `pem_read.cpp` `pem_write.cpp`这3个CPP文件，让它们对`aes.h`头文件的引用指向`cryptopp/aes.h`，从而避免冲突等问题出现