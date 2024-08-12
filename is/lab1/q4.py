# Hill cipher
import numpy as np

alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def matrix_mod_inv(key_matrix, mod):
    det = int(round(np.linalg.det(key_matrix))) 
    det_inv = pow(det, -1, mod) 
    adjugate = np.round(det * np.linalg.inv(key_matrix)).astype(int)
    return ((det_inv * adjugate) % mod)

def encrypt(plaintext, key):
    plaintext_matrix = np.array([alpha.index(c) for c in plaintext]).reshape(-1, len(key)).T
    ct_matrix = np.dot(key, plaintext_matrix) % len(alpha)
    return ''.join(alpha[int(ct_matrix[i, j])] for j in range(ct_matrix.shape[1]) for i in range(ct_matrix.shape[0]))

def decrypt(ciphertext, key):
    key_inv = matrix_mod_inv(key, len(alpha))
    ct_matrix = np.array([alpha.index(c) for c in ciphertext]).reshape(-1, len(key_inv)).T
    pt_matrix = np.dot(key_inv, ct_matrix) % len(alpha)
    return ''.join(alpha[int(pt_matrix[i, j])] for j in range(pt_matrix.shape[1]) for i in range(pt_matrix.shape[0]))

key = [[3, 3], [2, 7]]
plaintext = "We live in an insecure world".replace(" ", "").upper()
while len(plaintext) % len(key) != 0 : plaintext += 'X' # padding
print("PT: " + plaintext)
print("CT: " + encrypt(plaintext, key))
print("PT: " + decrypt(encrypt(plaintext, key), key))
