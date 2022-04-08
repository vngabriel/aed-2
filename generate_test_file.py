import random

inserted_numbers = []

f = open("red-black-tree/tests/input/4.in", "w+")
for i in range(20000):
    n = random.randint(-5000, 10000)
    if i < 10000 and n not in inserted_numbers:
        f.write(f"1 {n}\n")
        inserted_numbers.append(n)

    else:
        f.write(f"2 {n}\n")
        inserted_numbers.append(n)

f.write("3\n")
f.write("99")
f.close()
