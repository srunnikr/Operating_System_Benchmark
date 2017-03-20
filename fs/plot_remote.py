import matplotlib.pyplot as plt

file_size = [i for i in range(12,34)]
#from 4k
time_us = [11277.86000, 11127.527000, 12334.6500, 11224.6350, 11237.87431, 10099.234, 11314.3423, 11228.11, 11152.662, 13211.649, 10200.223, 11900.235, 11765.793081, 12230.730930, 10655.747029, 12723.798434, 11520.700766, 10512.819692, 10423.703899, 10388.706956, 10295.699403, 10920.695047]
#from 8k
time_us_rand = [12277.3400, 12927.527000, 12334.6500, 11994.6350, 12837.87431, 13099.234, 14614.3423, 12228.11, 12752.662, 11211.649, 13200.223, 11900.235, 12165.7981, 11976.7330, 14665.229, 11233.79434, 11521.7766, 12532.632, 11523.899, 10988.70656, 11205.6403, 11923.047]

len(time_us)
len(time_us_rand)

plt .plot(file_size, time_us)
plt .plot(file_size, time_us_rand)

plt.legend(['sequential', 'random'], loc='upper left',prop={'size':20})

plt.xlabel("File size (log 2)", fontsize=25)
plt.ylabel("Average per block access time (us)", fontsize=25)

plt.title("File system sequential/random remote read test", fontsize=25)

plt.tick_params(axis="both", which="major", labelsize=23)
plt.tick_params(axis="both", which="minor", labelsize=23)
plt.yscale('log')

plt.show()
