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

plt.scatter(x, y, facecolor='none', edgecolor='none', linewidth=0.1, s=10, zorder=5)

nb = [i for i in range(0, len(x))]
for i, txt in enumerate(nb):
    plt.annotate(txt, (x[i], y[i]), size = 3, va='center', ha='center', bbox=dict(boxstyle='round,pad=0.25', facecolor='white', edgecolor='black', lw=0.01), zorder=6)

eps = 0.1
for line in edges_file:
    ls = line.split(' ')
    # print(ls)
    i = int(ls[0])
    j = int(ls[1])
    c = 1 - float(ls[2]) 
    a = 1 - max(float(ls[2]) - eps, 0)
    b = 1 - min(float(ls[2]) + eps, 1)
    message_type = int(ls[3][0])
    
    node_color = "black"
    line_color = "blue" if message_type == 0 else "red"
    line_thick = 0.2 if message_type == 0 else 1.4

    if float(ls[2]) != -1:
        # plt.plot([a * x[i] + (1 - a) * x[j], b * x[i] + (1 - b) * x[j]], [a * y[i] + (1 - a) * y[j], b * y[i] + (1 - b) * y[j]], color='blue', linewidth=0.75, zorder=1)
        plt.scatter(c * x[i] + (1 - c) * x[j], c * y[i] + (1 - c) * y[j], facecolor=node_color, edgecolor='black', linewidth=0.2, s=0.5, zorder=4)
    plt.plot([x[i], x[j]], [y[i], y[j]], alpha=0.25, color=line_color, linewidth=line_thick, zorder=1)

# for i in range(0, len(x)):
#     for j in range(0, len(x)):
#         dist = np.sqrt((x[i] - x[j])**2 + (y[i] - y[j])**2)
#         if dist <= 15:
#             plt.plot([x[i], x[j]], [y[i], y[j]], color='black', linewidth=0.05, zorder=1)
    
edges_file.close()

plt.savefig(sys.argv[3], dpi=300)
