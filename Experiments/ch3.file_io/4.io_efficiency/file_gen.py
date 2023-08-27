import os
import random

def generate_random_file(file_path, file_size):
    with open(file_path, 'wb') as f:
        for _ in range(file_size):
            f.write(bytes([random.randint(0, 255)]))

if __name__ == "__main__":
    file_size = 524288 * 16
    file_path = "random_file.bin"
    generate_random_file(file_path, file_size)
    print(f"Random file of size {file_size} bytes generated at '{file_path}'.")

