La syntaxe des fichiers contenant des grilles de Kakuro est la suivante :
- Une ligne du fichier représente une ligne de la grille.
- Chaque colonne est séparée par un espace
- "." désigne une case blanche vide.
- "x\y" indique que le mot vertical aura pour somme x et le mot horizontal pour somme y.
  "\" représentera donc une case noire sans chiffre associé. "x\" et "\y" représenteront des cases noires
  ne contenant la définition que d'un mot respectivement vertical et horizontal.


L'exemple ci-dessous correspond à la grille donnée dans l'énoncé (fichier enonce.txt)

\ \ \ 5\ 18\ \
\ \ 11\6 . . \
\ \13 . . . \
\7 . . \4 . .
\ \15 . . . \
