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

#========================================
# create test files for contention test
#========================================

# delete existing folder
if os.path.exists(pwd+"/testfiles_con"):
    shutil.rmtree(pwd+"/testfiles_con")

# create contention testfiles folder
os.makedirs(pwd+"/testfiles_con")

for i in range(20):
    with open(pwd+'/testfiles_con/f'+"64MB_"+str(i)+".txt", 'wb') as f:
        buff = 'M' * 64 * 1024 * 1024
        f.write(buff)
