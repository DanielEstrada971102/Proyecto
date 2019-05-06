import numpy as np
import matplotlib.pyplot as plt
from sys import argv


def V(x, y):
    return x ** 2 * y ** 2 * np.exp(- x ** 2 - y ** 2)


def main():

    t0, x0, y0, vx0, vy0, E = np.loadtxt("resultados/Trayectoria_0.txt", unpack = True)
    t1, x1, y1, vx1, vy1, E1 = np.loadtxt("resultados/Trayectoria_1.txt", unpack = True)
    t2, x2, y2, vx2, vy2, E2 = np.loadtxt("resultados/Trayectoria_2.txt", unpack = True)
    t3, x3, y3, vx3, vy3, E3 = np.loadtxt("resultados/Trayectoria_3.txt", unpack = True)

    x = np.linspace(-4, 4, 600)
    y = np.linspace(-4, 4, 600)
    X, Y = np.meshgrid(x, y)
    Z = V(X, Y)

    plt.contour(X, Y, Z, colors='k')
    plt.plot(x0, y0, color='blue', label='b =' + argv[1])
    plt.plot(x1, y1, color='green', label='b =' + argv[2])
    plt.plot(x2, y2, color='tomato', label='b =' + argv[3])
    plt.plot(x3, y3, color='darkmagenta', label='b =' + argv[4])
    plt.xlabel(r'$x$', fontsize=16)
    plt.ylabel(r'$y$', fontsize=16)
    plt.xlim(-3, 3)
    plt.ylim(-3, 3)
    plt.legend(fontsize=14)
    plt.grid()
    plt.title(r"Trayecotorias con $\frac{E}{E_m} = $" + argv[5], fontsize=18)
    plt.show()

    plt.plot(t0, E, 'k')
    plt.title(u"Gráfico de conservación de la energía", fontsize=18)
    plt.xlabel("t", fontsize=16)
    plt.ylabel(r"$E - E_0$", fontsize=16)
    plt.grid(True)
    plt.show()


if __name__ == '__main__':
    main()
