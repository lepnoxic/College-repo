# Playfair cipher
uppercase_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
ignore = 'X'
bogus = 'Z'

def create_table(key, ignore):
    order = []
    order[:] = key
    for i in uppercase_alpha:
        if i not in order:
            order.append(i)

    matrix = []
    row = []
    for i in order:
        if i == ignore: continue
        row.append(i)
        if (len(row) == 5): 
            matrix.append(row)
            row = []
    return matrix

def search(current, table):
    for i in range(len(table)):
        for j in range(len(table[0])):
            if (table[i][j] == current):
                return (i, j)

def encrypt(message, key):
    assert len(message) & 1 == 0, "message length should be even"
    splitted = []
    i = 0
    while(i < len(message)):
        if (message[i] == message[i+1]):
            splitted.append(message[i] + bogus)
            if (i + 2 < len(message)):
                splitted.append(message[i] + message[i+2])
            else:
                splitted.append(message[i] + bogus)
            i += 1
        else:
            splitted.append(message[i:i+2])
        i += 2
    table = create_table(key, ignore)
    cipher = ""
    for current in splitted:
        a, b = search(current[0], table)
        c, d = search(current[1], table)
        if (a == c):
            cipher += table[a][(b+1) % 5]
            cipher += table[c][(d+1) % 5]
        elif (b == d):
            cipher += table[(a+1) % 5][b]
            cipher += table[(c+1) % 5][d]
        else:
            cipher += table[a][d]
            cipher += table[c][b]
    return cipher

def decrypt(cipher, key):
    assert len(cipher) & 1 == 0, "cipher length should be even"
    splitted = [cipher[i:i+2] for i in range(0, len(cipher), 2)]
    table = create_table(key, ignore)
    message = ""
    for current in splitted:
        a, b = search(current[0], table)
        c, d = search(current[1], table)
        if (a == c):
            message += table[a][(b-1) % 5]
            message += table[c][(d-1) % 5]
        elif (b == d):
            message += table[(a-1) % 5][b]
            message += table[(c-1) % 5][d]
        else:
            message += table[a][d]
            message += table[c][b]
    return message

message = "The key is hidden under the door padd".replace(" ", "").upper()
key = "GUIDANCE"

print(message)
print(encrypt(message=message, key=key))
print(decrypt(encrypt(message=message, key=key), key=key))
