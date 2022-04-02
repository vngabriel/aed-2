import random

f = open("avl/tests/input/4.in", "w+")
for i in range(2000):
    if i < 800:
        f.write(f"1 {random.randint(-1000, 1000)}\n")
    
    elif i == 800: 
        f.write("3\n")

    else:
        f.write(f"2 {random.randint(-1000, 1000)}\n")

f.write("3\n")
f.write("99")
f.close()
