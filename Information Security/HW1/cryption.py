from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from binascii import b2a_base64, a2b_base64, b2a_hex, a2b_hex 
import binascii
from Crypto import Random
import os
import random
import string

#http://callmesurprise.github.io/2016/11/19/Python%E7%94%9F%E6%88%90%E6%8C%87%E5%AE%9A%E5%A4%A7%E5%B0%8F%E6%96%87%E4%BB%B6/
#https://pynative.com/python-generate-random-string/
#https://stackoverflow.com/questions/2257441/random-string-generation-with-upper-case-letters-and-digits
def genSizeFile(fileName, fileSize):
	#file path
	filePath = "Data" + fileName + ".txt"
	# 生成固定大小的文件
	# date size
	data_size = 0
	letters = string.ascii_lowercase + string.digits + string.ascii_uppercase
	with open(filePath, "w", encoding = "utf8") as f:
		while data_size < fileSize:
			#f.write(str(round(random.uniform(-1000, 1000),2)))
			f.write((random.choice(letters)))
			data_size = os.path.getsize(filePath)
	# print(os.path.getsize(filePath))

# start here.
#genSizeFile("Random_Data", 32 * 1024 * 1024 + 7)

def add_16(data):
	return data + '!' * (16 - len(data) % 16)

key = 'Sixteen byte key'
data = 'test123456'
key = key.encode('UTF-8')
data = data.encode('UTF-8')
iv = Random.new().read(AES.block_size)
print('AES.block_size = ', AES.block_size)
print('iv = ', iv)

#ECB
print('ECB:')
key_ECB = get_random_bytes(16)
print('key_ECB: ', key_ECB)
data_ECB = add_16('tesr')
data_ECB = data_ECB.encode('UTF-8')
print('before enc: ', data_ECB)
cipher_ECB = AES.new(key_ECB, AES.MODE_ECB)
tmp_ECB = cipher_ECB.encrypt(data_ECB)
print('after enc: ', tmp_ECB)
print('after dec: ', cipher_ECB.decrypt(tmp_ECB))

#CFB
print('CFB:')
key_CFB = get_random_bytes(16)
print('key_CFB: ', key_CFB)
cipher_CFB = AES.new(key_CFB, AES.MODE_CFB, iv)
data_CFB = data
print('before enc: ', data_CFB)
data_CFB = cipher_CFB.encrypt(data_CFB)
print('after enc: ', data_CFB)
tmp_CFB = binascii.b2a_hex(data_CFB)
print('turn to hex: ', tmp_CFB)
cipher_CFB = AES.new(key_CFB, AES.MODE_CFB, iv)
print('after dec: ', cipher_CFB.decrypt(binascii.a2b_hex(tmp_CFB)))


#CBC
print('CBC:')
key_CBC = get_random_bytes(16)
print('key_CBC: ', key_CBC)
data_CBC = add_16('ashen attack')
data_CBC = data_CBC.encode('UTF-8')
print('before enc: ', data_CBC)
cipher_CBC = AES.new(key_CBC, AES.MODE_CBC, iv)
data_CBC = iv + cipher_CBC.encrypt(data_CBC)
print('after enc: ', data_CBC)
print('turn to hex: ', binascii.b2a_hex(data_CBC))
cipher_CBC = AES.new(key_CFB, AES.MODE_CBC, iv)
data_CBC_l = cipher_CBC.decrypt(data_CBC)
print('after dec: ', data_CBC_l[16::])




#OFB
print('OFB:')
key_OFB = get_random_bytes(16)
print('key_OFM: ', key_OFB)
data_OFB = add_16('ashen attack')
data_OFB = data_OFB.encode('UTF-8')
print('before enc: ', data_OFB)
cipher_OFB = AES.new(key_OFB, AES.MODE_OFB, iv)
data_OFB = cipher_OFB.encrypt(data_OFB)
print('after enc: ', data_OFB)
print('turn to hex: ', binascii.b2a_hex(data_OFB))
cipher_OFB = AES.new(key_OFB, AES.MODE_OFB, iv)
print('after dec: ', cipher_OFB.decrypt(data_OFB))


#CTR
print('CTR:')
data_CTR = 'test ahsen attack'.encode()
key_CTR = get_random_bytes(16)
print('key_CTR: ', key_CTR)
cipher_CTR = AES.new(key_CTR, AES.MODE_CTR)
print('before enc: ', data_CTR)
data_CTR = cipher_CTR.encrypt(data_CTR)
print('after enc: ', data_CTR)
print('turn to hex: ', binascii.b2a_hex(data_CTR))
nonce = cipher_CTR.nonce
de_cipher_CTR = AES.new(key_CTR, AES.MODE_CTR, nonce = nonce)
de_data_CTR = de_cipher_CTR.decrypt(data_CTR)
print('after dec: ', de_data_CTR)

'''
class Prpcrypt(object):
    def __init__(self, key):
        self.mode = AES.MODE_CBC
        self.key = self.pad_key(key)

    def pad(self, text):
        text = bytes(text, encoding="utf8")
        while len(text) % 16 != 0:
            text += b'\0'
        return text

    def pad_key(self, key):
        key = bytes(key, encoding="utf8")
        while len(key) % 16 != 0:
            key += b'\0'
        return key

    def encrypt(self, text):
        texts = self.pad(text)
        aes = AES.new(self.key, self.mode,self.key)
        res = aes.encrypt(texts)
        return str(b2a_base64(res),encoding= "utf-8")

    def decrypt(self, text):
        texts = a2b_base64(self.pad(text))
        aes = AES.new(self.key, self.mode,self.key)
        res = str(aes.decrypt(texts),encoding="utf8")
        return res


if __name__ == "__main__":
    key = "fdsifekksonbn"
    text = "你好！Python"
    a = Prpcrypt(key).encrypt(text)
    b = Prpcrypt(key).decrypt(a)
    print(a)
    print(b)
    '''