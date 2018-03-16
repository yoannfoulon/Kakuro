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
