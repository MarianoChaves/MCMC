import matplotlib.pyplot as plt
import numpy as np

uniform = np.random.rand(1000000)

def F_inv(x):
    return 0.5*(x**2+2*x+1)
def g(z):
    return (1/np.sqrt(z)*np.sqrt(2)/2)

x_range = np.linspace(1/2, 2, 50)

g_z = F_inv(uniform)

plt.hist(g_z, density=True, bins = x_range)
plt.plot(x_range,g(x_range))

plt.show()

