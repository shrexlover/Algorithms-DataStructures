import random
import string
def namegen():
    arr = []
    for i in range(12):
        arr.append(random.choice(string.ascii_letters))
    name = ''.join(arr)
    return name
def linegen(f):
    var1 = namegen()
    var2 = namegen()
    var3 = str(random.randint(1000000, 9999999))
    f.write(var1)
    f.write(' ')
    f.write(var2)
    f.write(' ')
    f.write(var3)
    f.write('\n')


file = open('main/namelist', "w+")
for i in range(10000):
    linegen(file)
file.close()