import numpy as np
import matplotlib.pyplot as plt


def main():
    b, phi, t = np.loadtxt('resultados/S_variables.txt', unpack=True)

    plt.scatter(b, t, s=0.05, c='k', label=r'$ E/E_{max} = 0.26$')
    plt.xlabel(r'$b$', fontsize=16)
    plt.ylabel(r'$t$', fontsize=16)
    plt.title(r"Tiempo de escape")
    plt.legend(loc="best", fontsize=14)
    plt.show()

    plt.scatter(b, phi, s=0.05, c='k', label=r'$ E/E_{max} = 0.26$')
    plt.xlabel(r'$b$ ', fontsize=16)
    plt.ylabel(r'$\Phi (rad) $', fontsize=16)
    plt.ylim(ymin=-np.pi / 2, ymax=np.pi / 2)
    plt.title(u"Ángulo de dispersión")
    plt.legend(loc="best", fontsize=14)
    plt.show()


if __name__ == '__main__':
    main()
