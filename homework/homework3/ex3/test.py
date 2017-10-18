import random

SIZE = 10000

f = open('rand_int.txt', 'w')
for i in range(SIZE):
    num = random.randint(-100000, 100000)
    f.write('%s=%d\n' % (str(i), num))
f.close()

f = open('rand_double.txt', 'w')
for i in range(SIZE):
    num = random.random() * 2 - 1
    f.write('%s=%f\n' % (str(i), num))
f.close()

f = open('rand_string.txt', 'w')
for i in range(SIZE):
    length = random.randint(10, 20)
    string = ''
    for j in range(length):
        string += chr(random.randint(ord('a'), ord('z')))
    f.write('%s=%s\n' % (str(i), string))
f.close()
