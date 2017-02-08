import matplotlib.pyplot as plt

num_args = [0,1,2,3,4,5,6,7]
cycles = [39.69, 39.73, 40.22, 41.41, 42.05, 43.33, 43.23, 44.02]

plt .plot(num_args, cycles)

plt.xlabel("Number of arguments", fontsize=25)
plt.ylabel("Avg cycles (100000 iterations)", fontsize=25)

plt.title("Procedure call overhead, Num of args vs CPU cycles", fontsize=25)

plt.tick_params(axis="both", which="major", labelsize=23)
plt.tick_params(axis="both", which="minor", labelsize=23)

plt.show()
