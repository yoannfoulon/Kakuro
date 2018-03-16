#pragma once
#include <vector>
#include "Contrainte.hpp"

class ContrainteDifference : public Contrainte{
	private:
	public:
		ContrainteDifference(std::vector<Variable*> variables, int arite);
		bool evaluation();
		std::string getType();
};
