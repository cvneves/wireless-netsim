from random import random
from random import seed
import numpy as np
import matplotlib.pyplot as plt

N = 500 
N_HOST = 100
MIN_ACCEPTED_DIST = 2.5
x_router_temp = 100 * np.random.rand(N)
y_router_temp = 100 * np.random.rand(N)
x_router = []
y_router = []

for i in range(0, N):
    mindist = np.partition(np.sqrt((x_router_temp[i] - x_router_temp)**2 + (y_router_temp[i] - y_router_temp)**2), 2)[1]
    
    if (mindist > MIN_ACCEPTED_DIST):
        x_router.append(x_router_temp[i])
        y_router.append(y_router_temp[i])

edges = set()

N1 = len(x_router)

dist = np.zeros(shape=(N1,N1))

for i in range(0,N1):
    tupl = []
    for j in range(i+1, N1):
        dist[i][j] = dist[j][i] = np.sqrt((x_router[i] - x_router[j])**2 + (y_router[i] - y_router[j])**2)

    for j in range(0, N1):
        if j == i:
            continue
        tupl.append((dist[i][j], j))

    tupl.sort()

    k_max = np.floor(random() * N / 100)
    for k, t in enumerate(tupl):
        if k > k_max:
            break
        j = t[1]
        plt.plot([x_router[i], x_router[j]], [y_router[i], y_router[j]], color='black', linewidth=0.01, zorder=1)
        edges.add((i, j))

x_host_temp = 100 * np.random.rand(N_HOST)
y_host_temp = 100 * np.random.rand(N_HOST)
x_host = []
y_host = []

for i in range(0, N_HOST):
    tempvec = np.sqrt((x_host_temp[i] - x_router)**2 + (y_host_temp[i] - y_router)**2)
    templist = []

    for j, a in enumerate(tempvec):
        templist.append((a, j))
    templist.sort()
    mindist, j = templist[0]

    if (mindist > MIN_ACCEPTED_DIST):
        x_host.append(x_host_temp[i])
        y_host.append(y_host_temp[i])
        plt.plot([x_host[-1], x_router[j]], [y_host[-1], y_router[j]], color='blue', linewidth=0.5, zorder=1)

N2 = len(x_host)

print("routers:")
for i in range(0, N1):
    print(x_router[i], y_router[i])
print("hosts:")
for i in range(0, N2):
    print(x_host[i], y_host[i])
print("edges:")
for e in edges:
    print(e[0], e[1])

plt.axis('equal')
plt.scatter(x_router, y_router, facecolor='black', edgecolor='black', linewidth=0.1, s=10, zorder=2)
plt.scatter(x_host, y_host, facecolor='white', edgecolor='black', linewidth=0.1, s=10, zorder=3)
circ = plt.Circle((0,0), 2, color='r', fill=False)
fig, ax = plt.subplots()
ax.add_patch(circ)
plt.savefig("graph.pdf")
