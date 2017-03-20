# create small size files

import os
import shutil

# get current path
pwd = os.getcwd()

# delete existing test files
if os.path.exists(pwd+"/testfiles"):
    shutil.rmtree(pwd+"/testfiles")

# create testfiles folder
os.makedirs(pwd+"/testfiles")

sizes_KB = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512]
for size in sizes_KB:
    with open(pwd+'/testfiles/f'+str(size)+"KB"+".txt", 'wb') as f:
        buff = 'K' * size * 1024
        f.write(buff)

sizes_MB = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512]
for size in sizes_MB:
    with open(pwd+'/testfiles/f'+str(size)+"MB"+".txt", 'wb') as f:
        buff = 'M' * size * 1024 * 1024
        f.write(buff)
