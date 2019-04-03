import numpy as np 
import matplotlib.pyplot as plt


def f(x,y):
    return x**2 * y**2 * np.exp(-x**2-y**2)

def trayec(x,y):
    return 0


datos = np.loadtxt("resultados/Trayectoria_1.txt")
x1 = datos[:,1]
y1 = datos[:,2]
z1 = datos[:,3]

x = np.linspace(-5, 5,100)
y = np.linspace(-5, 5,100)

X, Y = np.meshgrid(x, y)
Z = f(X, Y)

X1 , Y1 = np.meshgrid(x1, y1)
Z1 = trayec(X1, Y1)


plt.contour(X, Y, Z)
plt.plot(x1, y1)
plt.show()