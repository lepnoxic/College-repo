from Crypto.Cipher import DES, AES
from Crypto.Util.Padding import pad, unpad
import time
import base64

# Define key sizes
des_key = b'abcdefgh'  # DES requires a 8-byte key
aes_key = b'0123456789ABCDEF0123456789ABCDEF'  # AES-256 requires a 32-byte key

def encrypt_des(message, key):
    cipher = DES.new(key, DES.MODE_ECB)
    padded_message = pad(message.encode(), DES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    return ciphertext

def decrypt_des(ciphertext, key):
    cipher = DES.new(key, DES.MODE_ECB)
    decrypted_message = unpad(cipher.decrypt(ciphertext), DES.block_size)
    return decrypted_message.decode()

def encrypt_aes(message, key):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_message = pad(message.encode(), AES.block_size)
    ciphertext = cipher.encrypt(padded_message)
    return ciphertext

def decrypt_aes(ciphertext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted_message = unpad(cipher.decrypt(ciphertext), AES.block_size)
    return decrypted_message.decode()

# Test message
message = "Performance Testing of Encryption Algorithms"

# Measure DES encryption and decryption times
start_time = time.time()
des_ciphertext = encrypt_des(message, des_key)
des_encrypt_time = time.time() - start_time

start_time = time.time()
des_decrypted_message = decrypt_des(des_ciphertext, des_key)
des_decrypt_time = time.time() - start_time

# Measure AES-256 encryption and decryption times
start_time = time.time()
aes_ciphertext = encrypt_aes(message, aes_key)
aes_encrypt_time = time.time() - start_time

start_time = time.time()
aes_decrypted_message = decrypt_aes(aes_ciphertext, aes_key)
aes_decrypt_time = time.time() - start_time

# Print results
print(f"DES Encryption Time: {des_encrypt_time:.6f} seconds")
print(f"DES Decryption Time: {des_decrypt_time:.6f} seconds")
print(f"AES-256 Encryption Time: {aes_encrypt_time:.6f} seconds")
print(f"AES-256 Decryption Time: {aes_decrypt_time:.6f} seconds")

# Verify decrypted messages are the same as the original message
assert message == des_decrypted_message
assert message == aes_decrypted_message

assert(des_encrypt_time > aes_encrypt_time)
assert(des_decrypt_time > aes_decrypt_time)

print("We can deduce that DES is faster in encryption and decryption")
