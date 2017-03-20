import matplotlib.pyplot as plt

file_size_GB = [i for i in range(1,13)]
#from 4k
time_ns = [870.79, 840.80, 821.26, 805.22, 849.76, 833.00, 838.40, 815.97, 825.81, 7236.74, 7233.34, 6969.73]
#from 8k
#time_us_rand = [12277.3400, 12927.527000, 12334.6500, 11994.6350, 12837.87431, 13099.234, 14614.3423, 12228.11, 12752.662, 11211.649, 13200.223, 11900.235, 12165.7981, 11976.7330, 14665.229, 11233.79434, 11521.7766, 12532.632, 11523.899, 10988.70656, 11205.6403, 11923.047]

plt .plot(file_size_GB, time_ns)
#plt .plot(file_size, time_us_rand)

# plt.legend(['sequential', 'random'], loc='upper left',prop={'size':20})

plt.xlabel("File size (GB)", fontsize=25)
plt.ylabel("Average per block access time (ns)", fontsize=25)

plt.title("File system cache measurement test", fontsize=25)

plt.tick_params(axis="both", which="major", labelsize=23)
plt.tick_params(axis="both", which="minor", labelsize=23)

plt.show()
