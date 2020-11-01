#!/bin/python3

"""
Questions préliminaires:
1. On peut distinguer les classes "Grille" et "Cellule".
2. Dans la classe "Cellule" on peut trouver les méthodes est_vivant(), set_voisins(), get_voisins(), naitre(), mourir(), 
   basculer(), calcule_etat_futur() ainsi que la méthde __str__() pour un affichage par print plus pratique.
   Dans la classe "Grille" on peut trouver les méthodes dans_grille(), setXY(), getXY(), get_largeur(), get_longueur(), 
   est_voisin(), get_voisin(), affecte_voisins(), remplir_alea(), jeu(), actualise() et __str__ pour les mêmes raisons.
3. On représente le voisinage d'une cellule dans la classe "Cellule" et le calculer dans la classe "Grille".
4. Une cellule qui ne se trouve pas dans l'un des bords possède 8 voisines, dans le cas contraire elle a 3 voisines.
5. Ces cases ne sont tout simplement pas représentés dans la matrice contenant les cellules. Elle ne sont donc pas considérées.
"""

from random import random
from time import sleep

class Cellule:
    def est_vivant(self):
        return self.__actuel
    
    def set_voisins(self, voisins):
        self.__voisins = voisins

    def get_voisins(self):
        return self.__voisins

    def naitre(self):
        self.__futur = True

    def mourir(self):
        self.__futur = False

    def basculer(self):
        self.__actuel = self.__futur

    def calcule_etat_futur(self):
        #if len(self.__voisins) > 0: print(len(self.__voisins))
        if self.__actuel:
            self.__futur = len(self.__voisins) == 2 or len(self.__voisins) == 3
        else:
            self.__futur = len(self.__voisins) == 3

    def __str__(self):
        """
        La méthode __str__ est pratique car elle permet d'afficher le retour de cette méthode quand print(c) avec c de type Cellule est appellée.
        Ainsi, ce sera pratique pour l'affichage de la grille
        """
        if self.__actuel:
            return "X"
        else:
            return "-"

    def __init__(self):
        self.__actuel = False
        self.__futur = False
        self.__voisins = None

class Grille:
    def dans_grille(self, x, y):
        return x >= 0 and x < self.longueur and y >= 0 and y < self.largeur

    def setXY(self, x, y, c):
        self.matrix[x][y] = c

    def getXY(self, x, y):
        return self.matrix[x][y]

    def get_largeur(self):
        return self.largeur

    def get_longueur(self):
        return self.longueur

    def est_voisin(self, a, b):
        if a == b or not self.dans_grille(a[0], a[1]) or not self.dans_grille(b[0], b[1]): return False
        return self.getXY(b[0], b[1]).est_vivant()

    def get_voisins(self, c):
        voisins = []
        for i in range(-1, 2):
            for j in range(-1, 2):
                if self.est_voisin(c, (c[0] + i, c[1] + j)): voisins.append((c[0] + i, c[1] + j))
        return voisins

    def affecte_voisins(self):
        for i in range(self.longueur):
            for j in range(self.largeur):
                self.matrix[i][j].set_voisins(self.get_voisins((i, j)))

    def remplir_alea(self, taux):
        for x in range(self.longueur):
            for y in range(self.largeur):
                if random() >= (1 - taux/100):
                    self.matrix[x][y].naitre()
                    self.matrix[x][y].basculer()

    def jeu(self):
        for x in range(self.longueur):
            for y in range(self.largeur):
                self.matrix[x][y].calcule_etat_futur()

    def actualise(self):
        for x in range(self.longueur):
            for y in range(self.largeur):
                self.matrix[x][y].basculer()

    def __str__(self):
        tmpm = [[None for x in range(self.longueur)] for y in range(self.largeur)]

        for x in range(self.longueur):
            for y in range(self.largeur):
                tmpm[y][x] = self.matrix[x][y]

        text = ""
        for x in tmpm:
            for y in x:
                text += str(y)
            text += '\n'
        return text

    def __init__(self, L, l):
        self.largeur = l
        self.longueur = L
        self.matrix = [[Cellule() for y in range(self.largeur)] for x in range(self.longueur)]

def effacer_ecran():
    print("\u001B[H\u001BJ")

if __name__ == "__main__":
    g = Grille(50, 50)

    """g.getXY(20, 20).naitre()
    g.getXY(20, 21).naitre()
    g.getXY(20, 22).naitre()

    g.getXY(20, 26).naitre()
    g.getXY(20, 27).naitre()
    g.getXY(20, 28).naitre()

    g.getXY(18, 24).naitre()
    g.getXY(17, 24).naitre()
    g.getXY(16, 24).naitre()

    g.getXY(22, 24).naitre()
    g.getXY(23, 24).naitre()
    g.getXY(24, 24).naitre()

    g.actualise()"""
    g.remplir_alea(25)

    for i in range(1000):
        effacer_ecran()
        print(g)
        g.affecte_voisins()
        g.jeu()
        g.actualise()
        sleep(0.1)