import numpy as np
import matplotlib.pyplot as plt


def main():
    E, nPuntos = np.loadtxt('resultados/nPuntos_energy.txt', unpack=True)

    plt.plot(E, nPuntos, 'k')
    plt.xlabel(r'$\frac{E}{E_m}$', fontsize=16)
    plt.ylabel(u'# de puntos Irregulares', fontsize=14)
    plt.vlines(1.16, 0, np.max(nPuntos), colors='red', linestyles='dashed', label=r'$ E = 1.16 E_m $')
    plt.title(u"Diagrama de bifurcación", fontsize=18)
    plt.legend(loc="best", fontsize=14)
    plt.show()


if __name__ == '__main__':
    main()
