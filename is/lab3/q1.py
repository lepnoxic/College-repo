"""
Using RSA, encrypt the message "Asymmetric Encryption" with the public key (n, e). Then
decrypt the ciphertext with the private key (n, d) to verify the original message.
"""

from Crypto.Util.number import bytes_to_long, long_to_bytes, inverse, getPrime

message = "Asymmetric Encryption"
m = bytes_to_long(message.encode())
p = getPrime(1024)
q = getPrime(1024)

e = 65537
n = p * q

ct = pow(m, e, n)
print("CT: ", ct)
print("n:", n)
print("e:", e)

phi = (p - 1) * (q - 1)
d = inverse(e, phi)

print("d:", d)
dt = pow(ct, d, n)
print(long_to_bytes(dt).decode())
