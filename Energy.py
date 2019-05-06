import numpy as np
import matplotlib.pyplot as plt
from sys import argv


def main():
    E, nPuntos = np.loadtxt('resultados/nPuntos_energy.txt', unpack=True)
    i = len(nPuntos)-1

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
