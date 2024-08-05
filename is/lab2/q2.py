from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import base64

def encrypt_aes(key: str, data: str) -> str:
    key_bytes = bytes.fromhex(key)
    cipher = AES.new(key_bytes, AES.MODE_ECB)
    padded_data = pad(data.encode(), AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)
    return base64.b64encode(encrypted_data).decode('utf-8')

def decrypt_aes(key: str, encrypted_data: str) -> str:
    key_bytes = bytes.fromhex(key)
    cipher = AES.new(key_bytes, AES.MODE_ECB)
    encrypted_data_bytes = base64.b64decode(encrypted_data)
    padded_data = cipher.decrypt(encrypted_data_bytes)
    return unpad(padded_data, AES.block_size).decode('utf-8')

if __name__ == "__main__":
    key = "0123456789ABCDEF0123456789ABCDEF"  # 32 hex chars = 16 bytes
    plaintext = "Sensitive Information"

    encrypted = encrypt_aes(key, plaintext)
    print(f"Encrypted: {encrypted}")

    decrypted = decrypt_aes(key, encrypted)
    print(f"Decrypted: {decrypted}")
