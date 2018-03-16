#include <vector>
#include "Variable.hpp"
#include "Contrainte.hpp"
#include "ContrainteSomme.hpp"
#include "ContrainteDifference.hpp"

#ifndef PARSER_H
#define PARSER_H

void parse (char * nom_fichier, std::vector<Variable*> &globalVars, std::vector<Contrainte*> &globalContraintes, std::vector<int> domain);

/* fonctions à compléter pour remplir vos structures de données */

void Variable_Parser (int num, std::vector<Variable*> &globalVars, std::vector<int> domain);      /* fonction permettant la création d'une nouvelle variable ayant pour numéro num */
void Contrainte_Difference (int var1, int var2, std::vector<Contrainte*> &globalContraintes, std::vector<int> domain);  /* fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2*/
void Contrainte_Somme (int portee[], int arite, int val, std::vector<Contrainte*> &globalContraintes, std::vector<int> domain);  /* fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant
                                                              dans le tableau portee de taille arite et dont la valeur est val */

#endif
