import string

lowercase_alpha = string.ascii_lowercase
uppercase_alpha = string.ascii_uppercase

def vignere_encrypt(message: str, key: str) -> str:
    cipher = []
    for i in range(len(message)):
        if message[i].islower():
            cipher.append(lowercase_alpha[(lowercase_alpha.find(message[i]) + lowercase_alpha.find(key[i % len(key)])) % len(lowercase_alpha)])
        elif message[i].isupper():
            cipher.append(uppercase_alpha[(uppercase_alpha.find(message[i]) + uppercase_alpha.find(key[i % len(key)])) % len(uppercase_alpha)])
        else:
            cipher.append(message[i])
    return ''.join(cipher)

def vignere_decrypt(cipher: str, key: str) -> str:
    message = []
    for i in range(len(cipher)):
        if cipher[i].islower():
            message.append(lowercase_alpha[(lowercase_alpha.find(cipher[i]) - lowercase_alpha.find(key[i % len(key)])) % len(lowercase_alpha)])
        elif cipher[i].isupper():
            message.append(uppercase_alpha[(uppercase_alpha.find(cipher[i]) - uppercase_alpha.find(key[i % len(key)])) % len(uppercase_alpha)])
        else:
            message.append(cipher[i])
    return ''.join(message)

def autokey_encrypt(message: str, key: int) -> str:
    initial_key = lowercase_alpha[key]
    cipher_key = initial_key + message[:-1]
    return vignere_encrypt(message, cipher_key)

def autokey_decrypt(cipher: str, key: int) -> str:
    initial_key = lowercase_alpha[key]
    cipher_key = initial_key
    message = []
    for i in range(len(cipher)):
        if cipher[i].islower():
            decoded_char = lowercase_alpha[(lowercase_alpha.find(cipher[i]) - lowercase_alpha.find(cipher_key[i])) % len(lowercase_alpha)]
            message.append(decoded_char)
        elif cipher[i].isupper():
            decoded_char = uppercase_alpha[(uppercase_alpha.find(cipher[i]) - uppercase_alpha.find(cipher_key[i])) % len(uppercase_alpha)]
            message.append(decoded_char)
        else:
            message.append(cipher[i])
        cipher_key += message[-1]
    return ''.join(message)

message = "the house is being sold tonight"
key = "dollars"

print(vignere_encrypt(message, key))
print(vignere_decrypt(vignere_encrypt(message, key), key))
print(autokey_encrypt(message, 7))
print(autokey_decrypt(autokey_encrypt(message, 7), 7))
