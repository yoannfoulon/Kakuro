#pragma once
#include <vector>
#include <iostream>
#include "Contrainte.hpp"

class ContrainteDifference : public Contrainte{
	private:
	public:
		ContrainteDifference(std::vector<Variable*> variables, int arite);
		bool evaluation();
		std::string getType();
		void remove(Variable *currentVar, Variable *v2, int *removedSize);
};
