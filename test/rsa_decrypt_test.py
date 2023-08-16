# 导入rsa库
import rsa
import base64

# 从文件中读取公钥
with open('test/public.pem', 'rb') as f:
    pub_key = rsa.PublicKey.load_pkcs1_openssl_pem(f.read())

# 待解密的base64编码的数据
b64_data = 'hEtHuWzViwmcEBmhCm9bN3lxki9OtUSI9wqUQw0S9B67TvMuUQ9ePKNgF0Nzj2GikPSuX81bwY5OAabgD5mJixzycQBmWAaTtZeKgOBKmFJsUVSdBujf6Zc1j4FbCPq0sUmRoKqtOdGaznzL3fSPM1N5IlBxb128krk1IeabgTUIstErtVdojArnahgc/Nfk08KTedvt5nhIb1zK3+Q4Iei2zp/VxU+Ui2920L7iQJg7er2Qe0UEFWp4Vm2jiRFrh7sFVrrU3JS3WQ5B4uJjn8Zgs6HE2r1viXaAuzRLTBSi2bOoBtir7H/yuyhXoRVAO/fctHHWZBHWkAl9xukiv5tFHl/LLq0EC9kNMGeUDnaakmmtdj/ywpJ8kh/okBcoWZKH2byuSxg0oRNX5wnEMtmlsHq6O6Et5L8CPfdssI7TLrRNV6R3uxzk5OnWYo7bXai2mnSlRgZ4i+zXbPolkdTZSyopVwd+I4RS0OAwUHfODqIDjoBCbgqYOgAG/VqP7uCA5rxfNpAsdaPxiHIwJDW3BQP1QvlCYw81UCiYzIujf1UcLpSFNNLGuROWD2/1rjJ6cjtYJgcbSIxXbVOQp4Q/BigE8sIaOj6rZRO+nggtfsgmVO4fHKc55MnGkv8DomSuDYrZFshJ7JW/edJa5s7aP7FTRJpcU+65sNJdvvE='

# 将base64编码的数据转换为字节
data = base64.b64decode(b64_data)

# 使用公钥解密数据
decrypted = rsa.decrypt(data, pub_key)

# 将解密后的字节转换为字符串
message = decrypted.decode()

# 输出结果
print('解密后的消息:', message)