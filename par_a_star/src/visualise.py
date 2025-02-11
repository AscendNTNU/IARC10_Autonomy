import numpy as np
import matplotlib.pyplot as plt


bitmap = np.loadtxt("bitmap.txt")
mine_map = np.loadtxt("minemap.txt")

print("Marked points in bitmap", np.sum(bitmap == 0))
print("Sum of mine map: ", np.sum(mine_map))

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 8))


ax1.imshow(mine_map, cmap="inferno")

path = np.loadtxt("output.txt")

bitmap += 2 * path

ax2.imshow(bitmap, cmap="inferno")
fig.tight_layout()


plt.show()