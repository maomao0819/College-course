from Crypto.Cipher import AES, ARC4, PKCS1_OAEP, Salsa20, PKCS1_v1_5
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from Crypto.PublicKey import RSA
from Crypto import Random
from Crypto.Hash import HMAC, SHA, SHA256, SHA512, CMAC
import os
from binascii import b2a_base64, a2b_base64, b2a_hex, a2b_hex 
import binascii
import random
import string
import time
import matplotlib.pyplot as plt
import gc
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
	# https://ithelp.ithome.com.tw/articles/10161708
	# https://codertw.com/%E7%A8%8B%E5%BC%8F%E8%AA%9E%E8%A8%80/368604/
	with open(filePath, "w", encoding = "utf8") as f:
		while data_size < fileSize:
			#f.write(str(round(random.uniform(-1000, 1000),2)))
			f.write((random.choice(letters)))
			data_size = os.path.getsize(filePath)
	f.close()
	# print(os.path.getsize(filePath))

M = 1024 * 1024

symmetric_key_size = 32
iv_size = 16

file_size = []
AES_256_CBC_enc_time = []
AES_256_CFB_enc_time = []
AES_256_CTR_enc_time = []
RSA_2048_enc_time = []
ARC4_enc_time = []
Salsa20_enc_time = []
SHA256_enc_time = []
SHA512_enc_time = []
HMAC_SHA256_enc_time = []
CMAC_AES_enc_time = []

for i in range(8, 40, 8):
	filename = str(i) + 'MB'
	if os.path.isfile(filename + '.txt') != True:
		genSizeFile(filename, i * M + 7)
	file_size.append(i)

	filePath = filename + ".txt"
	f = open(filePath, 'r')
	data = f.read()
	f.close()

	print(filename)
	# CBC
	# https://officeguide.cc/python-measure-execution-time-tutorial-examples/
	#print('CBC:')
	data_AES_256_CBC = data.encode('UTF-8')
	key_AES_256_CBC = get_random_bytes(symmetric_key_size)
	#print('key_AES_256_CBC: ', key_AES_256_CBC)
	iv_AES_256_CBC = get_random_bytes(iv_size)
	#print('iv_AES_256_CBC: ', iv_AES_256_CBC)
	# print('b  efore enc: ', data_AES_256_CBC.decode("utf-8"))
	enc_cipher_AES_256_CBC = AES.new(key_AES_256_CBC, AES.MODE_CBC, iv_AES_256_CBC)
	pad_data_AES_256_CBC = pad(data_AES_256_CBC, 16, style = 'pkcs7')
	start = time.process_time()
	ciphertext_AES_256_CBC = enc_cipher_AES_256_CBC.encrypt(pad_data_AES_256_CBC)
	end = time.process_time()
	AES_256_CBC_enc_time.append(end - start)
	del data_AES_256_CBC, key_AES_256_CBC, iv_AES_256_CBC, enc_cipher_AES_256_CBC, pad_data_AES_256_CBC, ciphertext_AES_256_CBC
	gc.collect()
	#print("encryption time：%f sec" % (end - start))
	#print('CipherText: ', ciphertext_AES_256_CBC)
	#dec_cipher_AES_256_CBC = AES.new(key_AES_256_CBC, AES.MODE_CBC, iv_CBC)
	#plaintext_AES_256_CBC = unpad(dec_cipher_AES_256_CBC.decrypt(ciphertext_AES_256_CBC), 16, style = 'pkcs7')
	#print('PlainText: ', plaintext_AES_256_CBC.decode("utf-8"))


	# CFB
	#print('CFB:')
	data_AES_256_CFB = data.encode('UTF-8')
	key_AES_256_CFB = get_random_bytes(symmetric_key_size)
	# print('key_AES_256_CFB: ', key_AES_256_CFB)
	iv_AES_256_CFB = get_random_bytes(iv_size)
	# print('iv_AES_256_CFB: ', iv_AES_256_CFB)
	# print('before enc: ', data_AES_256_CFB.decode("utf-8"))
	enc_cipher_AES_256_CFB = AES.new(key_AES_256_CFB, AES.MODE_CFB, iv_AES_256_CFB)
	pad_data_AES_256_CFB = pad(data_AES_256_CFB, 16, style = 'pkcs7')
	start = time.process_time()
	ciphertext_AES_256_CFB = enc_cipher_AES_256_CFB.encrypt(pad_data_AES_256_CFB)
	end = time.process_time()
	AES_256_CFB_enc_time.append(end - start)
	del data_AES_256_CFB, key_AES_256_CFB, iv_AES_256_CFB, enc_cipher_AES_256_CFB, pad_data_AES_256_CFB, ciphertext_AES_256_CFB
	gc.collect()
	#print("encryption time：%f sec" % (end - start))
	# print('CipherText: ', ciphertext_AES_256_CFB)
	# dec_cipher_AES_256_CFB = AES.new(key_AES_256_CFB, AES.MODE_AES_256_CFB, iv_AES_256_CFB)
	# plaintext_AES_256_CFB = unpad(dec_cipher_AES_256_CFB.decrypt(ciphertext_AES_256_CFB), 16, style = 'pkcs7')
	# print('PlainText: ', plaintext_AES_256_CFB.decode("utf-8"))


	# CTR
	# print('CTR:')
	data_AES_256_CTR = data.encode('UTF-8')
	key_AES_256_CTR = get_random_bytes(symmetric_key_size)
	# print('key_AES_256_CTR: ', key_AES_256_CTR)
	iv_AES_256_CTR = get_random_bytes(iv_size)
	# print('iv_AES_256_CTR: ', iv_AES_256_CTR)
	# print('before enc: ', data_AES_256_CTR.decode("utf-8"))
	enc_cipher_AES_256_CTR = AES.new(key_AES_256_CTR, AES.MODE_CTR)
	pad_data_AES_256_CTR = pad(data_AES_256_CTR, 16, style = 'pkcs7')
	start = time.process_time()
	ciphertext_AES_256_CTR = enc_cipher_AES_256_CTR.encrypt(pad_data_AES_256_CTR)
	end = time.process_time()
	AES_256_CTR_enc_time.append(end - start)
	del data_AES_256_CTR, key_AES_256_CTR, iv_AES_256_CTR, enc_cipher_AES_256_CTR, pad_data_AES_256_CTR, ciphertext_AES_256_CTR
	gc.collect()
	#print("encryption time：%f sec" % (end - start))
	# print('CipherText: ', ciphertext_AES_256_CTR)
	# dec_cipher_AES_256_CTR = AES.new(key_AES_256_CTR, AES.MODE_AES_256_CTR, nonce = enc_cipher_AES_256_CTR.nonce)
	# plaintext_AES_256_CTR = unpad(dec_cipher_AES_256_CTR.decrypt(ciphertext_AES_256_CTR), 16, style = 'pkcs7')
	# print('PlainText: ', plaintext_AES_256_CTR.decode("utf-8"))

	# https://pycryptodome.readthedocs.io/en/latest/src/examples.html#encrypt-data-with-rsa
	#RSA
	# print('RSA')
	data_RSA_2048 = data.encode("utf-8")
	key_RSA_2048 = RSA.generate(2048)
	private_key_RSA_2048 = key_RSA_2048.export_key()
	public_key_RSA_2048 = key_RSA_2048.publickey().export_key()

	recipient_key_RSA_2048 = RSA.import_key(public_key_RSA_2048)
	# session_key_RSA_2048 = get_random_bytes(16)

	# # Encrypt the session key with the public RSA key
	# cipher_RSA_2048 = PKCS1_OAEP.new(recipient_key_RSA_2048)
	# enc_session_key_RSA_2048 = cipher_RSA_2048.encrypt(session_key_RSA_2048)

	# Encrypt the data with the AES session key
	
	# cipher_aes_RSA_2048 = AES.new(session_key_RSA_2048, AES.MODE_EAX)
	# ciphertext_RSA_2048, tag = cipher_aes_RSA_2048.encrypt_and_digest(data_RSA_2048)
	enc_cipher_RSA_2048 = PKCS1_OAEP.new(recipient_key_RSA_2048)
	ciphertext_RSA_2048 = []
	length = 200
	start = time.process_time()
	for i in range(0, len(data_RSA_2048), length):
		ciphertext_RSA_2048.append(enc_cipher_RSA_2048.encrypt(data_RSA_2048[i : i + length]))
	end = time.process_time()
	RSA_2048_enc_time.append(end - start)
	#print("encryption time：%f sec" % (end - start))
	del data_RSA_2048, key_RSA_2048, private_key_RSA_2048, public_key_RSA_2048, recipient_key_RSA_2048, enc_cipher_RSA_2048, ciphertext_RSA_2048
	gc.collect()

	# file_in = open("encrypted_data.bin", "rb")

	# private_key = RSA.import_key(open("private.pem").read())

	# enc_session_key, nonce, tag, ciphertext = \
	#    [ file_in.read(x) for x in (private_key.size_in_bytes(), 16, 16, -1) ]

	# # Decrypt the session key with the private RSA key
	# cipher_rsa = PKCS1_OAEP.new(private_key)
	# session_key = cipher_rsa.decrypt(enc_session_key)

	# # Decrypt the data with the AES session key
	# cipher_aes = AES.new(session_key, AES.MODE_EAX, nonce)
	# data_RSA = cipher_aes.decrypt_and_verify(ciphertext, tag)
	# print(data_RSA.decode("utf-8"))

	# ARC4
	# print('ARC4:')
	data_ARC4 = data.encode('UTF-8')
	key_ARC4 = get_random_bytes(16)
	# print('key_ARC4: ', key_ARC4)
	# print('before enc: ', data_ARC4.decode("utf-8"))
	nonce = Random.new().read(16)
	tempkey = SHA.new(key_ARC4 + nonce).digest() #key is no more than 256bytes
	enc_cipher_ARC4 = ARC4.new(tempkey)
	pad_data_ARC4 = pad(data_ARC4, 16, style = 'pkcs7')
	start = time.process_time()
	ciphertext_ARC4 = enc_cipher_ARC4.encrypt(pad_data_ARC4)
	end = time.process_time()
	ARC4_enc_time.append(end - start)
	del data_ARC4, nonce, tempkey, key_ARC4, enc_cipher_ARC4, pad_data_ARC4, ciphertext_ARC4
	gc.collect()
	#print("encryption time：%f sec" % (end - start))
	# print('CipherText: ', ciphertext_ARC4)
	# dec_cipher_ARC4 = ARC4.new(tempkey)
	# plaintext_ARC4 = unpad(dec_cipher_ARC4.decrypt(ciphertext_ARC4), 16, style = 'pkcs7')
	# print('PlainText: ', plaintext_ARC4.decode("utf-8"))


	# Salsa20
	# print('Salsa20:')
	data_Salsa20 = data.encode('UTF-8')
	key_Salsa20 = get_random_bytes(16)
	# print('key_Salsa20: ', key_Salsa20)
	# print('before enc: ', data_Salsa20.decode("utf-8"))
	enc_cipher_Salsa20 = Salsa20.new(key = key_Salsa20)
	pad_data_Salsa20 = pad(data_Salsa20, 16, style = 'pkcs7')
	start = time.process_time()
	ciphertext_Salsa20 = enc_cipher_Salsa20.encrypt(pad_data_Salsa20)
	end = time.process_time()
	msg_Salsa20 = enc_cipher_Salsa20.nonce + ciphertext_Salsa20
	msg_Salsa20_nonce = msg_Salsa20[:8]
	ciphertext_Salsa20 = msg_Salsa20[8:]
	Salsa20_enc_time.append(end - start)
	del data_Salsa20, key_Salsa20, enc_cipher_Salsa20, pad_data_Salsa20, ciphertext_Salsa20, msg_Salsa20, msg_Salsa20_nonce
	gc.collect()
	#print("encryption time：%f sec" % (end - start))
	# print('CipherText: ', ciphertext_Salsa20)
	# dec_cipher_Salsa20 = Salsa20.new(key = key_Salsa20, nonce = msg_Salsa20_nonce)
	# plaintext_Salsa20 = unpad(dec_cipher_Salsa20.decrypt(ciphertext_Salsa20), 16,  style = 'pkcs7')
	# print('PlainText: ', plaintext_Salsa20.decode("utf-8"))


	# SHA-256
	# print('SHA-256')
	data_SHA256 = data.encode('UTF-8')
	pad_data_SHA256 = pad(data_SHA256, 16, style = 'pkcs7')
	hash_SHA256 = SHA256.new()
	start = time.process_time()
	hash_SHA256.update(pad_data_SHA256)
	# print(hash_SHA256.hexdigest())
	end = time.process_time()
	SHA256_enc_time.append(end - start)
	#print("encryption time：%f sec" % (end - start))
	del data_SHA256, hash_SHA256, pad_data_SHA256
	gc.collect()

	# SHA-512
	# print('SHA-512')
	data_SHA512 = data.encode('UTF-8')
	pad_data_SHA512 = pad(data_SHA512, 16, style = 'pkcs7')
	hash_SHA512 = SHA512.new()
	start = time.process_time()
	hash_SHA512.update(pad_data_SHA512)
	# print(hash_SHA512.hexdigest())
	end = time.process_time()
	SHA512_enc_time.append(end - start)
	#print("encryption time：%f sec" % (end - start))
	del data_SHA512, hash_SHA512, pad_data_SHA512
	gc.collect()

	# HMAC
	# print('HMAC')
	data_HMAC_SHA256 = data.encode('UTF-8')
	key_HMAC_SHA256 = get_random_bytes(16)
	pad_data_HMAC_SHA256 = pad(data_HMAC_SHA256, 16, style = 'pkcs7')
	hash_HMAC_SHA256 = HMAC.new(key_HMAC_SHA256, digestmod = SHA256)
	start = time.process_time()
	hash_HMAC_SHA256.update(pad_data_HMAC_SHA256)
	# print(hash_HMAC_SHA256.hexdigest())
	end = time.process_time()
	HMAC_SHA256_enc_time.append(end - start)
	#print("encryption time：%f sec" % (end - start))
	del data_HMAC_SHA256, key_HMAC_SHA256, hash_HMAC_SHA256, pad_data_HMAC_SHA256
	gc.collect()

	# CMAC
	# print('CMAC')
	data_CMAC_AES = data.encode('UTF-8')
	key_CMAC_AES = get_random_bytes(16)
	pad_data_CMAC_AES = pad(data_CMAC_AES, 16, style = 'pkcs7')
	hash_CMAC_AES = CMAC.new(key_CMAC_AES, ciphermod = AES)
	start = time.process_time()
	hash_CMAC_AES.update(pad_data_CMAC_AES)
	# print(hash_CMAC_AES.hexdigest())
	end = time.process_time()
	CMAC_AES_enc_time.append(end - start)
	#print("encryption time：%f sec" % (end - start))
	del data_CMAC_AES, key_CMAC_AES, hash_CMAC_AES, pad_data_CMAC_AES
	gc.collect()

filename_enc_time = 'enc_time'
filePath_time = filename_enc_time + '.txt'
with open(filePath_time, "w", encoding = "utf8") as f:
	f.write('file_size: ' + str(file_size) + '\n')
	f.write('AES_256_CBC_enc_time: ' + str(AES_256_CBC_enc_time) + '\n')
	f.write('AES_256_CFB_enc_time: ' + str(AES_256_CFB_enc_time) + '\n')
	f.write('AES_256_CTR_enc_time: ' + str(AES_256_CTR_enc_time) + '\n')
	f.write('RSA_2048_enc_time: ' + str(RSA_2048_enc_time) + '\n')
	f.write('ARC4_enc_time: ' + str(ARC4_enc_time) + '\n')
	f.write('Salsa20_enc_time: ' + str(Salsa20_enc_time) + '\n')
	f.write('SHA256_enc_time: ' + str(SHA256_enc_time) + '\n')
	f.write('SHA512_enc_time: ' + str(SHA512_enc_time) + '\n')
	f.write('HMAC_SHA256_enc_time: ' + str(HMAC_SHA256_enc_time) + '\n')
	f.write('CMAC_AES_enc_time: ' + str(CMAC_AES_enc_time) + '\n')
f.close()


plt.plot(file_size, AES_256_CBC_enc_time, 'o--', color = 'r', label = 'AES-256-CBC', markersize = 5)
plt.plot(file_size, AES_256_CFB_enc_time, 's--', color = 'orange', label = 'AES-256-CFB', markersize = 5)
plt.plot(file_size, AES_256_CTR_enc_time, 'p--', color = 'y', label = 'AES-256-CTR', markersize = 5)
plt.plot(file_size, RSA_2048_enc_time, 'h--', color = 'lime', label = 'RSA-2048', markersize = 5)
plt.plot(file_size, ARC4_enc_time, '+--', color = 'g', label = 'ARC4', markersize = 5)
plt.plot(file_size, Salsa20_enc_time, 'D--', color = 'c', label = 'Salsa20', markersize = 5)
plt.plot(file_size, SHA256_enc_time, '*--', color = 'b', label = 'SHA256', markersize = 5)
plt.plot(file_size, SHA512_enc_time, 'o--', color = 'k', label = 'SHA512', markersize = 5)
plt.plot(file_size, HMAC_SHA256_enc_time, 's--', color = 'gray', label = 'HMAC(with SHA-256)', markersize = 5)
plt.plot(file_size, CMAC_AES_enc_time, 'p--', color = 'm', label = 'CMAC(with AES)', markersize = 5)
plt.title("Cipher encryption speeds", fontsize = 30)

# set scale
plt.xticks(file_size, fontsize = 15)
plt.yticks(fontsize = 15)

# label x coordinate(labelpad means the distance between the label and the image)
plt.xlabel("File size(MB)", fontsize = 20, labelpad = 15)
# mark y coordinate(labelpad means the distance between the label and the image)
plt.ylabel("Encryption time(sec)", fontsize = 20, labelpad = 20)

# show the location of the line
plt.legend(loc = "right", fontsize = 20)
plt.show()