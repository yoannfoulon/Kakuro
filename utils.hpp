#include <vector>
#include "Variable.hpp"
#include "Contrainte.hpp"
#include "ContrainteSomme.hpp"
#include "ContrainteDifference.hpp"

#ifndef UTILS_H
#define UTILS_H

void displayCSP(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes);
bool isConsistant(std::vector<Contrainte*> globalContraintes, long *nbTests);
bool isCompleted(std::vector<Variable*> solutions);
void checkAndRemove(Variable* v, std::vector<Contrainte*> globalContraintes, std::vector<Variable*> globalVariables, std::vector<Variable*> *variablesModifs, int *nbModif, long *nbTests);
bool emptyDomain(std::vector<Variable*> vars);

#endif
