"""
Use a brute-force attack to decipher the following message. Assume that you know it is an
affine cipher and that the plaintext "ab" is enciphered to "GL":
XPALASXYFGFUKPXUSOGEUTKCDGEXANMGNVS
"""

from math import gcd
alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def affine_encrypt(message : str, a : int, b: int):
    cipher = ""
    for i in message:
        cipher += alpha[((alpha.find(i) * a) + b) % len(alpha)]
    return cipher

def affine_decrypt(cipher : str, a : int, b : int):
    assert gcd(len(alpha), a) == 1, "Inverse is invalid"
    message = ""
    for i in cipher:
        message += alpha[((alpha.find(i) - b) * pow(a, -1, len(alpha))) % len(alpha)]
    return message

def brute_force(pt1, ct1):
    for i in range(len(alpha)):
        if (gcd(i, len(alpha)) != 1) : continue
        for j in range(len(alpha)):
            if ct1 == affine_encrypt(pt1, i, j):
                return (i, j)

pt1 = "AB"
ct1 = "GL"

a, b = brute_force(pt1, ct1)

print("Bruteforce done:", a, b)

ct2 = "XPALASXYFGFUKPXUSOGEUTKCDGEXANMGNVS"
print(affine_decrypt(ct2, a, b))

