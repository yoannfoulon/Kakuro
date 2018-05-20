#include <vector>
#include "Variable.hpp"
#include "Contrainte.hpp"
#include "ContrainteSomme.hpp"
#include "ContrainteDifference.hpp"
#include "utils.hpp"


std::vector<Variable*> backTrack(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes, long *nbNoeuds, long *nbTests);
std::vector<Variable*> forwardChecking(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes, long *nbNoeuds, long *nbTests, bool heuristic);
