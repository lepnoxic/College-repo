def hash_function(given_string):
	current_hash = 5381
	for i in given_string:
		current_hash *= 33
		current_hash += ord(i)
		current_hash &= 0xFFFFFFFF
	return current_hash

print(hash_function("Hello world"))