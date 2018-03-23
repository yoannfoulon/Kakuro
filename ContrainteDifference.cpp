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

void ContrainteDifference::remove(Variable *v){
	bool isInVars = false;
	for(unsigned i = 0; i < this->getVariables().size(); ++i){
		if(this->getVariables()[i]->getIdentifier() == v->getIdentifier()){
			isInVars = true;
			break;
		}
	}
	if(isInVars){
		for(unsigned i = 0; i < this->getVariables().size(); ++i){
			if(this->getVariables()[i]->getIdentifier() != v->getIdentifier()){
				this->getVariables()[i]->removeFromDomain(v->getValue());
			}
		}
	}
}


