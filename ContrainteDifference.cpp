#include "ContrainteDifference.hpp"

ContrainteDifference::ContrainteDifference(std::vector<Variable*> variables, int arite)
	: Contrainte::Contrainte(variables, arite){}

bool ContrainteDifference::evaluation(){
	if(this->getVariables()[0]->getValue() == this->getVariables()[1]->getValue()) return false;
	return true;
}

std::string ContrainteDifference::getType(){
	return "ContrainteDifference";
}

void ContrainteDifference::remove(Variable *currentVar, Variable *v2, int *removedSize){
	printf("Removing value %d from %d domain\n", currentVar->getValue(), v2->getIdentifier());
	v2->removeFromDomain(currentVar->getValue());
	++*removedSize;
}
