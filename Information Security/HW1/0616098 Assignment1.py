from Crypto.Cipher import AES, PKCS1_OAEP, ARC4, Salsa20
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from Crypto.PublicKey import RSA
from Crypto import Random
from Crypto.Hash import HMAC, SHA, SHA256, SHA512, CMAC
import os
import time
import matplotlib.pyplot as plt
import gc

# define size(unit: bytes)
symmetric_key_size = 32
iv_size = 16


# create file of specific size
def genSizeFile(fileName, fileSize):
	filePath = fileName + ".txt"
	data_size = 0
	# letter only allowed lowercase, digits, or uppercase
	letters = string.ascii_lowercase + string.digits + string.ascii_uppercase
	with open(filePath, "w", encoding = "utf8") as f:
		while data_size < fileSize:
			# randomly generate letter and write in
			f.write((random.choice(letters)))
			data_size = os.path.getsize(filePath)
	f.close()


# create file of specific size simply
def genSizeFile_simple(fileName, fileSize):
	filePath = fileName + ".txt"
	data_size = 0
	# letter only allowed lowercase, digits, or uppercase
	letters = string.ascii_lowercase + string.digits + string.ascii_uppercase
	with open(filePath, "w", encoding = "utf8") as f:
		while fileSize - data_size > 16:
			num_chars = 16
			# randomly generate 16 same letter and write in
			f.write((random.choice(letters)) * num_chars)
			data_size = os.path.getsize(filePath)
		num_chars = fileSize - data_size
		f.write((random.choice(letters)) * num_chars)
	f.close()


# 1 symmetric cipher with 3 mode of operations
def AES_256_CBC(commom_plaintext):
	# CBC
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_AES_256_CBC = commom_plaintext.encode('UTF-8')
	# create key by random bytes
	key_AES_256_CBC = get_random_bytes(symmetric_key_size)
	# create iv by random bytes
	iv_AES_256_CBC = get_random_bytes(iv_size)
	# create encryption cipher
	enc_cipher_AES_256_CBC = AES.new(key_AES_256_CBC, AES.MODE_CBC, iv_AES_256_CBC)
	# padding
	pad_plaintext_AES_256_CBC = pad(plaintext_AES_256_CBC, 16, style = 'pkcs7')
	start = time.process_time()
	# encryption
	ciphertext_AES_256_CBC = enc_cipher_AES_256_CBC.encrypt(pad_plaintext_AES_256_CBC)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_AES_256_CBC, key_AES_256_CBC, iv_AES_256_CBC, enc_cipher_AES_256_CBC, pad_plaintext_AES_256_CBC, ciphertext_AES_256_CBC
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


def AES_256_CFB(commom_plaintext):
	# CFB
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_AES_256_CFB = commom_plaintext.encode('UTF-8')
	# create key by random bytes
	key_AES_256_CFB = get_random_bytes(symmetric_key_size)
	# create iv by random bytes
	iv_AES_256_CFB = get_random_bytes(iv_size)
	# create encryption cipher
	enc_cipher_AES_256_CFB = AES.new(key_AES_256_CFB, AES.MODE_CFB, iv_AES_256_CFB)
	# padding
	pad_plaintext_AES_256_CFB = pad(plaintext_AES_256_CFB, 16, style = 'pkcs7')
	start = time.process_time()
	# encryption
	ciphertext_AES_256_CFB = enc_cipher_AES_256_CFB.encrypt(pad_plaintext_AES_256_CFB)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_AES_256_CFB, key_AES_256_CFB, iv_AES_256_CFB, enc_cipher_AES_256_CFB, pad_plaintext_AES_256_CFB, ciphertext_AES_256_CFB
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


def AES_256_CTR(commom_plaintext):
	# CTR
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_AES_256_CTR = commom_plaintext.encode('UTF-8')
	# create key by random bytes
	key_AES_256_CTR = get_random_bytes(symmetric_key_size)
	# create encryption cipher
	enc_cipher_AES_256_CTR = AES.new(key_AES_256_CTR, AES.MODE_CTR)
	# padding
	pad_plaintext_AES_256_CTR = pad(plaintext_AES_256_CTR, 16, style = 'pkcs7')
	start = time.process_time()
	# encryption
	ciphertext_AES_256_CTR = enc_cipher_AES_256_CTR.encrypt(pad_plaintext_AES_256_CTR)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_AES_256_CTR, key_AES_256_CTR, enc_cipher_AES_256_CTR, pad_plaintext_AES_256_CTR, ciphertext_AES_256_CTR
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


# 1 asymmetric cipher
def RSA_2048(commom_plaintext):
	#RSA
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_RSA_2048 = commom_plaintext.encode("utf-8")
	# create key
	key_RSA_2048 = RSA.generate(2048)
	# create private key
	private_key_RSA_2048 = key_RSA_2048.export_key()
	# create public key
	public_key_RSA_2048 = key_RSA_2048.publickey().export_key()
	# create key for PKCS1_OAEP
	recipient_key_RSA_2048 = RSA.import_key(public_key_RSA_2048)
	# create encryption cipher
	enc_cipher_RSA_2048 = PKCS1_OAEP.new(recipient_key_RSA_2048)
	# ciphertext is too large, so using list with append to collect it
	ciphertext_RSA_2048 = []
	# plaintext's length can't be longer than the RSA modulus (in bytes) minus 11, 2048 / 8 - 11 = 245
	length = 200	
	enc_time = 0
	# reference: https://blog.csdn.net/orangleliu/article/details/72964948
	# partition and encryption seperately
	for i in range(0, len(plaintext_RSA_2048), length):
		start = time.process_time()
		# encryption
		ciphertext = enc_cipher_RSA_2048.encrypt(plaintext_RSA_2048[i : i + length])
		end = time.process_time()
		# merging seperated ciphertext
		ciphertext_RSA_2048.append(str(ciphertext))
		# enc_time = sum of the (time after encryption minus time before encryption)
		enc_time += (end - start)
	#ciphertext_RSA_2048 = "".join(ciphertext_RSA_2048)
	# delete variables to release memory space
	del plaintext_RSA_2048, key_RSA_2048, private_key_RSA_2048, public_key_RSA_2048, recipient_key_RSA_2048, enc_cipher_RSA_2048, ciphertext_RSA_2048
	gc.collect()
	# return enc_time
	return enc_time


# 2 stream cipher
def ARC4_enc(commom_plaintext):
	# ARC4
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_ARC4 = commom_plaintext.encode('UTF-8')
	# create key by random bytes
	key_ARC4 = get_random_bytes(16)
		# nonce = Random.new().read(16)
		# tempkey = SHA.new(key_ARC4 + nonce).digest()
	# create encryption cipher
	enc_cipher_ARC4 = ARC4.new(key_ARC4)
	# padding
	pad_plaintext_ARC4 = pad(plaintext_ARC4, 16, style = 'pkcs7')
	start = time.process_time()
	# encryption
	ciphertext_ARC4 = enc_cipher_ARC4.encrypt(pad_plaintext_ARC4)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_ARC4, key_ARC4, enc_cipher_ARC4, pad_plaintext_ARC4, ciphertext_ARC4
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


def Salsa20_enc(commom_plaintext):
	# Salsa20
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_Salsa20 = commom_plaintext.encode('UTF-8')
	# create key by random bytes
	key_Salsa20 = get_random_bytes(16)
	# create encryption cipher
	enc_cipher_Salsa20 = Salsa20.new(key = key_Salsa20)
	# padding
	pad_plaintext_Salsa20 = pad(plaintext_Salsa20, 16, style = 'pkcs7')
	start = time.process_time()
	# encryption
	ciphertext_Salsa20 = enc_cipher_Salsa20.encrypt(pad_plaintext_Salsa20)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_Salsa20, key_Salsa20, enc_cipher_Salsa20, pad_plaintext_Salsa20, ciphertext_Salsa20
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


# 2 hash function
def SHA_256(commom_plaintext):
	# SHA-256
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_SHA256 = commom_plaintext.encode('UTF-8')
	# padding
	pad_plaintext_SHA256 = pad(plaintext_SHA256, 16, style = 'pkcs7')
	# create hash function
	hash_SHA256 = SHA256.new()
	start = time.process_time()
	hash_SHA256.update(pad_plaintext_SHA256)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_SHA256, hash_SHA256, pad_plaintext_SHA256
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


def SHA_512(commom_plaintext):
	# SHA-512
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_SHA512 = commom_plaintext.encode('UTF-8')
	# padding
	pad_plaintext_SHA512 = pad(plaintext_SHA512, 16, style = 'pkcs7')
	# create hash function
	hash_SHA512 = SHA512.new()
	start = time.process_time()
	hash_SHA512.update(pad_plaintext_SHA512)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_SHA512, hash_SHA512, pad_plaintext_SHA512
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


# 2 MAC
def HMAC_SHA256(commom_plaintext):
	# HMAC
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_HMAC_SHA256 = commom_plaintext.encode('UTF-8')
	# create key by random bytes
	key_HMAC_SHA256 = get_random_bytes(16)
	# padding
	pad_plaintext_HMAC_SHA256 = pad(plaintext_HMAC_SHA256, 16, style = 'pkcs7')
	# create MAC
	hash_HMAC_SHA256 = HMAC.new(key_HMAC_SHA256, digestmod = SHA256)
	start = time.process_time()
	# MAC
	hash_HMAC_SHA256.update(pad_plaintext_HMAC_SHA256)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_HMAC_SHA256, key_HMAC_SHA256, hash_HMAC_SHA256, pad_plaintext_HMAC_SHA256
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


def CMAC_AES(commom_plaintext):
	# CMAC
	# Encode to 'UTF-8' from 'bytes' type
	plaintext_CMAC_AES = commom_plaintext.encode('UTF-8')
	# create key by random bytes
	key_CMAC_AES = get_random_bytes(16)
	# padding
	pad_plaintext_CMAC_AES = pad(plaintext_CMAC_AES, 16, style = 'pkcs7')
	# create MAC
	hash_CMAC_AES = CMAC.new(key_CMAC_AES, ciphermod = AES)
	start = time.process_time()
	# MAC
	hash_CMAC_AES.update(pad_plaintext_CMAC_AES)
	end = time.process_time()
	# delete variables to release memory space
	del plaintext_CMAC_AES, key_CMAC_AES, hash_CMAC_AES, pad_plaintext_CMAC_AES
	gc.collect()
	# return enc_time = time after encryption minus time before encryption, and record it
	return end - start


def main():
	# 1MB = 1024 * 1024 bytes
	M = 1024 * 1024

	# file_size records the file size(unit: MB)
	file_size = []
	# enc_time is the list that records the time the cipher cost to encrypt
	# 1 symmetric cipher with 3 mode of operations
	AES_256_CBC_enc_time = []
	AES_256_CFB_enc_time = []
	AES_256_CTR_enc_time = []
	# 1 asymmetric cipher
	RSA_2048_enc_time = []
	# 2 stream cipher
	ARC4_enc_time = []
	Salsa20_enc_time = []
	# 2 hash function
	SHA256_enc_time = []
	SHA512_enc_time = []
	# 2 MAC
	HMAC_SHA256_enc_time = []
	CMAC_AES_enc_time = []


	# create file of 8 ~ 56 MB
	for i in range(8, 60, 8):
		filename = str(i) + 'MB'
		# If file isn't exist -> create
		if os.path.isfile(filename + '.txt') != True:
			genSizeFile(filename, i * M + 7)
		# records the file size(unit: MB)
		file_size.append(i)
		# Load the data in the file and assign to commom_plaintext
		filePath = filename + ".txt"
		f = open(filePath, 'r')
		commom_plaintext = f.read()
		f.close()
		print(filename)


		# record the time the cipher cost to encrypt
		# 1 symmetric cipher with 3 mode of operations
		AES_256_CBC_enc_time.append(AES_256_CBC(commom_plaintext))
		AES_256_CFB_enc_time.append(AES_256_CFB(commom_plaintext))
		AES_256_CTR_enc_time.append(AES_256_CTR(commom_plaintext))
		# 1 asymmetric cipher
		RSA_2048_enc_time.append(RSA_2048(commom_plaintext))
		# 2 stream cipher
		ARC4_enc_time.append(ARC4_enc(commom_plaintext))
		Salsa20_enc_time.append(Salsa20_enc(commom_plaintext))
		# 2 hash function
		SHA256_enc_time.append(SHA_256(commom_plaintext))
		SHA512_enc_time.append(SHA_512(commom_plaintext))
		# 2 MAC
		HMAC_SHA256_enc_time.append(HMAC_SHA256(commom_plaintext))
		CMAC_AES_enc_time.append(CMAC_AES(commom_plaintext))


	# draw the plot with different style
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

	# set scale of x, y coordinate
	plt.xticks(file_size, fontsize = 15)
	plt.yticks(fontsize = 15)
	# mark x, y coordinate(labelpad means the distance between the label and the image)
	plt.xlabel("File size(MB)", fontsize = 20, labelpad = 15)
	plt.ylabel("Encryption time(sec)", fontsize = 20, labelpad = 20)
	# show the legend
	plt.legend(loc = "upper left", fontsize = 20)
	plt.show()

if __name__ == "__main__":
	main()