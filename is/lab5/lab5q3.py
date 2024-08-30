import hashlib
import time


with open('word-list.txt', 'rb') as file:
	wordlist = [i.strip() for i in file.readlines()]

start_time = time.time()
sha256_hashes = []
for i in wordlist:
	sha256_hashes.append(hashlib.sha256(i).hexdigest())
sha256_time = time.time() - start_time

if (len(set(sha256_hashes)) != len(sha256_hashes)):
	print('Hash collision detected in sha256')
else:
	print('No hash collision detected in sha256')


start_time = time.time()
sha1_hashes = []
for i in wordlist:
	sha1_hashes.append(hashlib.sha1(i).hexdigest())
sha1_time = time.time() - start_time


if (len(set(sha1_hashes)) != len(sha1_hashes)):
	print('Hash collision detected in sha1')
else:
	print('No hash collision detected in sha1')

start_time = time.time()
md5_hashes = []
for i in wordlist:
	md5_hashes.append(hashlib.md5(i).hexdigest())
md5_time = time.time() - start_time


if (len(set(md5_hashes)) != len(md5_hashes)):
	print('Hash collision detected in md5')
else:
	print('No hash collision detected in md5')


print(f'Time taken to generate SHA256 hashes: {sha256_time:.6f}')
print(f'Time taken to generate SHA1 hashes: {sha1_time:.6f}')
print(f'Time taken to generate MD5 hashes: {md5_time:.6f}')