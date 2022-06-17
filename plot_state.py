import numpy as np
import matplotlib.pyplot as plt
import sys

points_file = open(sys.argv[1])

x = []
y = []
for line in points_file:
    l = line.split(' ')
    x.append(float(l[0]))
    y.append(float(l[1]))

points_file.close()
edges_file = open(sys.argv[2])

plt.scatter(x, y, facecolor='white', edgecolor='black', linewidth=0.1, s=10, zorder=2)

nb = [i for i in range(0, len(x))]

for i, txt in enumerate(nb):
    plt.annotate(txt, (x[i], y[i]), size = 3, va='center', ha='center', bbox=dict(boxstyle='round,pad=0.25', facecolor='white', edgecolor='black', lw=0.01))

for line in edges_file:
    l = line.split(' ')
    i = int(l[0])
    j = int(l[1])
    plt.plot([x[i], x[j]], [y[i], y[j]], color='blue', linewidth=0.05, zorder=1)

# for i in range(0, len(x)):
#     for j in range(0, len(x)):
#         dist = np.sqrt((x[i] - x[j])**2 + (y[i] - y[j])**2)
#         if dist <= 15:
#             plt.plot([x[i], x[j]], [y[i], y[j]], color='black', linewidth=0.05, zorder=1)

    
edges_file.close()

plt.savefig(sys.argv[3])
