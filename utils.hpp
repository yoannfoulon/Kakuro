#include <vector>
#include "Variable.hpp"
#include "Contrainte.hpp"
#include "ContrainteSomme.hpp"
#include "ContrainteDifference.hpp"

#ifndef UTILS_H
#define UTILS_H

void displayCSP(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes);
bool isConsistant(std::vector<Contrainte*> globalContraintes);
bool isCompleted(std::vector<Variable*> solutions);

#endif