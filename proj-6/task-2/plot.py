import matplotlib.pyplot as plt

filename_input = input("Enter filename to read from: ")
filename_output = input("Enter output filename: ")

with open(filename_input) as f:
    lines = f.readlines()
    x = [int(line.split()[0]) for line in lines]
    y = [int(line.split()[1]) for line in lines]

plt.plot(x, y, marker=".")
plt.savefig(filename_output)