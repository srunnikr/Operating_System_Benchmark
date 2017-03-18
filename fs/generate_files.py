import os

pwd = os.getcwd()

sizes = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
for size in sizes:
    with open(pwd+'/testfiles/f'+str(size)+".txt", 'wb') as f:
        buff = 'a'*size * 1024
        f.write(buff)
