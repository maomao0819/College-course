from Crypto.Cipher import AES, ARC4, PKCS1_OAEP
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from Crypto.PublicKey import RSA
from Crypto import Random
from Crypto.Hash import HMAC, SHA, SHA256, SHA512
import os
from binascii import b2a_base64, a2b_base64, b2a_hex, a2b_hex 
import binascii
import random
import string
from Crypto.Cipher import Salsa20
from Crypto.Hash import CMAC

#http://callmesurprise.github.io/2016/11/19/Python%E7%94%9F%E6%88%90%E6%8C%87%E5%AE%9A%E5%A4%A7%E5%B0%8F%E6%96%87%E4%BB%B6/
#https://pynative.com/python-generate-random-string/
#https://stackoverflow.com/questions/2257441/random-string-generation-with-upper-case-letters-and-digits
def genSizeFile(fileName, fileSize):
	#file path
	filePath = fileName + ".txt"
	# 生成固定大小的文件
	# date size
	data_size = 0
	letters = string.ascii_lowercase + string.digits + string.ascii_uppercase
	with open(filePath, "w", encoding = "utf8") as f:
		while data_size < fileSize:
			#f.write(str(round(random.uniform(-1000, 1000),2)))
			f.write((random.choice(letters)))
			data_size = os.path.getsize(filePath)
	f.close()
	# print(os.path.getsize(filePath))

genSizeFile("Assignment 1", 32 * 1024 * 1024 + 7)


symmetric_key_size = 32
iv_size = 16


# CBC
print('CBC:')
data_CBC = 'maomao and tzuyu and winni'
data_CBC = data_CBC.encode('UTF-8')
key_CBC = get_random_bytes(symmetric_key_size)
print('key_CBC: ', key_CBC)
iv_CBC = get_random_bytes(iv_size)
print('iv_CBC: ', iv_CBC)
print('before enc: ', data_CBC.decode("utf-8"))
enc_cipher_CBC = AES.new(key_CBC, AES.MODE_CBC, iv_CBC)
ciphertext_CBC = enc_cipher_CBC.encrypt(pad(data_CBC, 16, style = 'pkcs7'))
print('CipherText: ', ciphertext_CBC)
dec_cipher_CBC = AES.new(key_CBC, AES.MODE_CBC, iv_CBC)
plaintext_CBC = unpad(dec_cipher_CBC.decrypt(ciphertext_CBC), 16, style = 'pkcs7')
print('PlainText: ', plaintext_CBC.decode("utf-8"))


# CFB
print('CFB:')
data_CFB = 'maomao and winni and tzuyu'
data_CFB = data_CFB.encode('UTF-8')
key_CFB = get_random_bytes(symmetric_key_size)
print('key_CFB: ', key_CFB)
iv_CFB = get_random_bytes(iv_size)
print('iv_CFB: ', iv_CFB)
print('before enc: ', data_CFB.decode("utf-8"))
enc_cipher_CFB = AES.new(key_CFB, AES.MODE_CFB, iv_CFB)
ciphertext_CFB = enc_cipher_CFB.encrypt(pad(data_CFB, 16, style = 'pkcs7'))
print('CipherText: ', ciphertext_CFB)
dec_cipher_CFB = AES.new(key_CFB, AES.MODE_CFB, iv_CFB)
plaintext_CFB = unpad(dec_cipher_CFB.decrypt(ciphertext_CFB), 16, style = 'pkcs7')
print('PlainText: ', plaintext_CFB.decode("utf-8"))


# CTR
print('CTR:')
data_CTR = 'winni and maomao and tzuyu'
data_CTR = data_CTR.encode('UTF-8')
key_CTR = get_random_bytes(symmetric_key_size)
print('key_CTR: ', key_CTR)
iv_CTR = get_random_bytes(iv_size)
print('iv_CTR: ', iv_CTR)
print('before enc: ', data_CTR.decode("utf-8"))
enc_cipher_CTR = AES.new(key_CTR, AES.MODE_CTR)
ciphertext_CTR = enc_cipher_CTR.encrypt(pad(data_CTR, 16, style = 'pkcs7'))
print('CipherText: ', ciphertext_CTR)
dec_cipher_CTR = AES.new(key_CTR, AES.MODE_CTR, nonce = enc_cipher_CTR.nonce)
plaintext_CTR = unpad(dec_cipher_CTR.decrypt(ciphertext_CTR), 16, style = 'pkcs7')
print('PlainText: ', plaintext_CTR.decode("utf-8"))

#RSA
print('RSA')
key = RSA.generate(2048)
private_key = key.export_key()
file_out = open("private.pem", "wb")
file_out.write(private_key)
file_out.close()

public_key = key.publickey().export_key()
file_out = open("receiver.pem", "wb")
file_out.write(public_key)
file_out.close()

data = "I met aliens in UFO. Here is the map.".encode("utf-8")
file_out = open("encrypted_data.bin", "wb")

recipient_key = RSA.import_key(open("receiver.pem").read())
session_key = get_random_bytes(16)

# Encrypt the session key with the public RSA key
cipher_rsa = PKCS1_OAEP.new(recipient_key)
enc_session_key = cipher_rsa.encrypt(session_key)

# Encrypt the data with the AES session key
cipher_aes = AES.new(session_key, AES.MODE_EAX)
ciphertext, tag = cipher_aes.encrypt_and_digest(data)
[ file_out.write(x) for x in (enc_session_key, cipher_aes.nonce, tag, ciphertext) ]
file_out.close()

file_in = open("encrypted_data.bin", "rb")

private_key = RSA.import_key(open("private.pem").read())

enc_session_key, nonce, tag, ciphertext = \
   [ file_in.read(x) for x in (private_key.size_in_bytes(), 16, 16, -1) ]

# Decrypt the session key with the private RSA key
cipher_rsa = PKCS1_OAEP.new(private_key)
session_key = cipher_rsa.decrypt(enc_session_key)

# Decrypt the data with the AES session key
cipher_aes = AES.new(session_key, AES.MODE_EAX, nonce)
data = cipher_aes.decrypt_and_verify(ciphertext, tag)
print(data.decode("utf-8"))


# ARC4
print('ARC4:')
data_ARC4 = 'tzuyu and MAOMAO and winni'
data_ARC4 = data_ARC4.encode('UTF-8')
key_ARC4 = get_random_bytes(16)
print('key_ARC4: ', key_ARC4)
print('before enc: ', data_ARC4.decode("utf-8"))
nonce = Random.new().read(16)
tempkey = SHA.new(key_ARC4 + nonce).digest() #key is no more than 256bytes
enc_cipher_ARC4 = ARC4.new(tempkey)
ciphertext_ARC4 = enc_cipher_ARC4.encrypt(pad(data_ARC4, 16, style = 'pkcs7'))
print('CipherText: ', ciphertext_ARC4)
dec_cipher_ARC4 = ARC4.new(tempkey)
plaintext_ARC4 = unpad(dec_cipher_ARC4.decrypt(ciphertext_ARC4), 16, style = 'pkcs7')
print('PlainText: ', plaintext_ARC4.decode("utf-8"))


# Salsa20
print('Salsa20:')
data_Salsa20 = 'tzuyu and maomao and winni'
data_Salsa20 = data_Salsa20.encode('UTF-8')
key_Salsa20 = get_random_bytes(16)
print('key_Salsa20: ', key_Salsa20)
print('before enc: ', data_Salsa20.decode("utf-8"))
enc_cipher_Salsa20 = Salsa20.new(key = key_Salsa20)
msg_Salsa20 = enc_cipher_Salsa20.nonce + enc_cipher_Salsa20.encrypt(pad(data_Salsa20, 16, style = 'pkcs7'))
msg_Salsa20_nonce = msg_Salsa20[:8]
ciphertext_Salsa20 = msg_Salsa20[8:]
print('CipherText: ', ciphertext_Salsa20)
dec_cipher_Salsa20 = Salsa20.new(key = key_Salsa20, nonce = msg_Salsa20_nonce)
plaintext_Salsa20 = unpad(dec_cipher_Salsa20.decrypt(ciphertext_Salsa20), 16,  style = 'pkcs7')
print('PlainText: ', plaintext_Salsa20.decode("utf-8"))


# SHA-256
print('SHA-256')
h = SHA256.new()
h.update(b'Hello')
print(h.hexdigest())


# SHA-512
print('SHA-512')
h = SHA512.new()
h.update(b'Hello')
print(h.hexdigest())


# HMAC
print('HMAC')
secret = b'Swordfish'
hi = HMAC.new(secret, digestmod = SHA256)
hi.update(b'Hello')
print(hi.hexdigest())


# CMAC
print('CMAC')
secret = b'Sixteen byte key'
cobj = CMAC.new(secret, ciphermod = AES)
cobj.update(b'Hello')
print(cobj.hexdigest())


