#pip install pycryptodome

# 导入所需的库
import base64
import hashlib
from Crypto.Cipher import AES

# 定义一个AES加密类
class AESCipher(object):
    def __init__(self, key):
        self.bs = AES.block_size # 获取AES的块大小
        self.key = hashlib.sha256(key.encode()).digest() # 使用SHA-256对密钥进行哈希

    def decrypt(self, enc, iv):
        enc = base64.b64decode(enc) # 对base64字符串进行解码
        cipher = AES.new(self.key, AES.MODE_CBC, iv) # 创建一个AES实例，使用CBC模式和传入的iv
        return self._unpad(cipher.decrypt(enc)).decode('utf-8') # 对密文进行解密，并去除填充，返回utf-8编码的字符串

    def _unpad(self, s):
        return s[:-s[-1]] # 去除PKCS7填充，即去除最后一个字节对应数量的字节

# 创建一个AES加密类的实例，传入密钥
aes = AESCipher("abcdefghijklmnopqrstuvwxyz012345")

print("AES实例已创建")

# 调用decrypt方法，传入base64字符串和iv，得到解密后的明文
plaintext = aes.decrypt("CI2O5vxpRlU7+60A64gVGA==","asasasasasasasas")

# 打印明文
print(plaintext)