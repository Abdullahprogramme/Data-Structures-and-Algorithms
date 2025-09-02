# Generates n random integers between -10000 and 10000
import random

def generate(filename, n):
    with open(filename, 'w') as f:
        for _ in range(n):
            f.write(f"{random.randint(-10000, 10000)}\n")

if __name__ == "__main__":
    sizes = [500, 1000, 2000, 4000, 8000, 16000]
    for n in sizes:
        generate(f"input_{n}.txt", n)
    print("Input files generated.")
