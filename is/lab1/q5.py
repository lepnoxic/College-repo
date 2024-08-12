"""
John is reading a mystery book involving cryptography. In one part of the book, the author
gives a ciphertext "CIW" and two paragraphs later the author tells the reader that this is a shift
cipher and the plaintext is "yes". In the next chapter, the hero found a tablet in a cave with
"XVIEWYWI" engraved on it. John immediately found the actual meaning of the ciphertext.
Identify the type of attack and plaintext

The following is a known plaintext attack
"""

alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

pt1 = "YES"
ct1 = "CIW"

# Calculate all shifts in the cipher pair and check if all are equal
shifts = []
for i in range(len(pt1)):
    shifts.append((alpha.index(pt1[i]) - alpha.index(ct1[i])) % len(alpha))
assert all(s == shifts[0] for s in shifts)
print("Shift: " + str(shifts[0]))

# Decrypt for plaintext
ct2 = "XVIEWYWI"
pt2 = ""

for i in ct2:
    pt2 += alpha[(alpha.index(i) + shifts[0]) % len(alpha)]

print("Plaintext: " + pt2)
