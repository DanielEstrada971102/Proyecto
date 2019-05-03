import numpy as np
import matplotlib.pyplot as plt


def main():
    b, phi, t = np.loadtxt('resultados/S_variables.txt', unpack=True)

    plt.scatter(b, t, s=0.05, c='k', label=r'$ E/E_{max} = 1.2$')
    plt.xlabel(r'$b$', fontsize=16)
    plt.ylabel(r'$t_e$', fontsize=16)
    plt.title(r"Tiempo de escape",fontsize=18)
    plt.legend(loc="best", fontsize=14)
    plt.show()

    plt.scatter(b, phi, s=0.05, c='k', label=r'$ E/E_{max} = 0.26$')
    plt.xlabel(r'$b$ ', fontsize=16)
    plt.ylabel(r'$\Phi (rad) $', fontsize=16)
    plt.ylim(-np.pi / 2, np.pi / 2)
    plt.title(u"Ángulo de dispersión", fontsize=18)
    plt.legend(loc="best", fontsize=14)
    plt.show()


if __name__ == '__main__':
    main()
