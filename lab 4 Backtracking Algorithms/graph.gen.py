import random
n = 100
num_of_lines = int(((n*(n-1))/2) * 0.6)
def linegen(n, num_of_lines):
    for i in range(num_of_lines):
        a = str(random.randint(1, n))
        b = str(random.randint(1, n))
        c = a + " " + b + "\n"
        c.join(" ")
        f.write(c)

f = open("cmake-build-debug/graph", "w")
linegen(n, num_of_lines)
f.close()