import string
lowercase_alpha = string.ascii_lowercase
uppercase_alpha = string.ascii_uppercase

def additive_encrypt(message : str, key : int):
    cipher = ""
    for i in message:
        if i.islower():
            cipher += lowercase_alpha[(lowercase_alpha.find(i) + key) % len(lowercase_alpha)]
        elif i.isupper():
            cipher += uppercase_alpha[(uppercase_alpha.find(i) + key) % len(uppercase_alpha)]
        else:
            cipher += i
    return cipher

def additive_decrypt(cipher : str, key : int):
    message = ""
    for i in cipher:
        if i.islower():
            message += lowercase_alpha[(lowercase_alpha.find(i) - key) % len(lowercase_alpha)]
        elif i.isupper():
            message += uppercase_alpha[(uppercase_alpha.find(i) - key) % len(uppercase_alpha)]
        else:
            message += i
    return message

def multiplicative_encrypt(message : str, key : int):
    cipher = ""
    for i in message:
        if i.islower():
            cipher += lowercase_alpha[(lowercase_alpha.find(i) * key) % len(lowercase_alpha)]
        elif i.isupper():
            cipher += uppercase_alpha[(uppercase_alpha.find(i) * key) % len(uppercase_alpha)]
        else:
            cipher += i
    return cipher

def multiplicative_decrypt(cipher : str, key : int):
    message = ""
    for i in cipher:
        if i.islower():
            message += lowercase_alpha[(lowercase_alpha.find(i) * pow(key, -1, len(lowercase_alpha))) % len(lowercase_alpha)]
        elif i.isupper():
            message += uppercase_alpha[(uppercase_alpha.find(i) * pow(key, -1, len(uppercase_alpha))) % len(uppercase_alpha)]
        else:
            message += i
    return message

def affine_encrypt(message : str, a : int, b: int):
    cipher = ""
    for i in message:
        if i.islower():
            cipher += lowercase_alpha[((lowercase_alpha.find(i) * a) + b) % len(lowercase_alpha)]
        elif i.isupper():
            cipher += uppercase_alpha[((uppercase_alpha.find(i) * a) + b) % len(uppercase_alpha)]
        else:
            cipher += i
    return cipher

def affine_decrypt(cipher : str, a : int, b : int):
    message = ""
    for i in cipher:
        if i.islower():
            message += lowercase_alpha[((lowercase_alpha.find(i) - b) * pow(a, -1, len(lowercase_alpha))) % len(lowercase_alpha)]
        elif i.isupper():
            message += uppercase_alpha[((uppercase_alpha.find(i) - b) * pow(a, -1, len(uppercase_alpha))) % len(uppercase_alpha)]
        else:
            message += i
    return message

message = "I am learning information security"
print("Additive encrypted: " + additive_encrypt(message, 20))
print("Additive decrypted: " + additive_decrypt(additive_encrypt(message, 20), 20))
print("Multiple encrypted: " + multiplicative_encrypt(message, 15))
print("Multiple decrypted: " + multiplicative_decrypt(multiplicative_encrypt(message, 15), 15))
print("Affine encrypted: " + affine_encrypt(message, 15, 20))
print("Affine decrypted: " + affine_decrypt(affine_encrypt(message, 15, 20), 15, 20))