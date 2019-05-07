import numpy as np
import matplotlib.pyplot as plt
from sys import argv


def V(x, y):
    return x ** 2 * y ** 2 * np.exp(- x ** 2 - y ** 2)


def main():

    option = float(argv[1])

    if option == 1:

        t0, x0, y0, vx0, vy0, E = np.loadtxt("results/Trayectoria_0.txt", unpack = True)
        t1, x1, y1, vx1, vy1, E1 = np.loadtxt("results/Trayectoria_1.txt", unpack = True)
        t2, x2, y2, vx2, vy2, E2 = np.loadtxt("results/Trayectoria_2.txt", unpack = True)
        t3, x3, y3, vx3, vy3, E3 = np.loadtxt("results/Trayectoria_3.txt", unpack = True)

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

    if option == 2:
        b, phi, t = np.loadtxt('results/S_variables.txt', unpack=True)

        plt.scatter(b, t, s=0.05, c='k', label=r'$ E/E_{max} =$' + argv[2])
        plt.xlabel(r'$b$', fontsize=16)
        plt.ylabel(r'$t_e$', fontsize=16)
        plt.title(r"Tiempo de escape", fontsize=18)
        plt.legend(loc="best", fontsize=14)
        plt.show()

        plt.scatter(b, phi, s=0.05, c='k', label=r'$ E/E_{max} = $' + argv[2])
        plt.xlabel(r'$b$ ', fontsize=16)
        plt.ylabel(r'$\Phi (rad) $', fontsize=16)
        plt.ylim(-np.pi / 2, np.pi / 2)
        plt.title(u"Ángulo de dispersión", fontsize=18)
        plt.legend(loc="best", fontsize=14)
        plt.show()

    if option == 3:
        E, nPuntos = np.loadtxt('results/nPuntos_energy.txt', unpack=True)
        i = len(nPuntos) - 1

        while (nPuntos[i] == 0):
            i -= 1

        plt.plot(E, nPuntos, 'k')
        plt.xlabel(r'$\frac{E}{E_m}$', fontsize=16)
        plt.ylabel(u'# de puntos Irregulares', fontsize=14)
        plt.vlines(1.16, 0, np.max(nPuntos), colors='red', linestyles='dashed', label=r'$ E = %.2lf E_m $'%(E[i]))
        plt.title(u"Diagrama de bifurcación", fontsize=18)
        plt.legend(loc="best", fontsize=14)
        plt.show()


if __name__ == '__main__':
    main()
