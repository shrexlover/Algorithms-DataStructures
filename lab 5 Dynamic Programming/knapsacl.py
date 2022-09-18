import random
n = 100
num_of_lines = 100
def linegen(n, num_of_lines):
    for i in range(num_of_lines):
        a = str(i)
        b = str(random.randint(1, 20))
        c = a + " " + b + "\n"
        c.join(" ")
        f.write(c)

f = open("graph", "w")
linegen(n, num_of_lines)
f.close()