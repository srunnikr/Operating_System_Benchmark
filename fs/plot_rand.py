import matplotlib.pyplot as plt

file_size = [i for i in range(13,34)]

time_us_rand = [0, 246.200000, 228.790000, 268.706500, 233.333750 , 274.273438, 229.107219, 218.144172 , 260.806023, 219.992699, 222.335074, 225.082348 , 245.701518, 230.634941 , 232.086556, 230.603404 , 237.678186, 234.086253, 233.604617, 232.543789, 0 ,0]

plt .plot(file_size, time_us)

plt.xlabel("File size (log 2)", fontsize=25)
plt.ylabel("Average per block access time (us)", fontsize=25)

plt.title("File system random read", fontsize=25)

plt.tick_params(axis="both", which="major", labelsize=23)
plt.tick_params(axis="both", which="minor", labelsize=23)
plt.yscale('log')

plt.show()
