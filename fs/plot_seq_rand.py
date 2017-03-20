import matplotlib.pyplot as plt

file_size = [i for i in range(12,34)]
#from 4k
time_us = [266.846000, 237.527000, 134.299000, 65.594250, 37.591000, 16.344313, 14.544438, 8.118875, 2.657352, 1.688977, 1.814758, 0.931732, 0.793081, 0.730930, 0.747029, 0.798434, 0.700766, 0.819692, 0.703899, 0.706956, 0.699403, 0.695047]
#from 8k
time_us_rand = [226.12, 246.200000, 228.790000, 268.706500, 233.333750 , 274.273438, 229.107219, 218.144172 , 260.806023, 219.992699, 222.335074, 225.082348 , 245.701518, 230.634941 , 232.086556, 230.603404 , 237.678186, 234.086253, 233.604617, 232.543789, 231.34, 241.2]

len(time_us)
len(time_us_rand)

plt .plot(file_size, time_us)
plt .plot(file_size, time_us_rand)

plt.legend(['sequential', 'random'], loc='upper left',prop={'size':20})

plt.xlabel("File size (log 2)", fontsize=25)
plt.ylabel("Average per block access time (us)", fontsize=25)

plt.title("File system sequential/random read test", fontsize=25)

plt.tick_params(axis="both", which="major", labelsize=23)
plt.tick_params(axis="both", which="minor", labelsize=23)
plt.yscale('log')

plt.show()
