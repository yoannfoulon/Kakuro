#pragma once
#include <vector>
#include <string>
#include <stdlib.h>
#include "Variable.hpp"

class Contrainte{
	protected:
		std::vector<Variable*> m_variables;
		int m_arite;
	public:
		Contrainte(std::vector<Variable*>, int arite);
		virtual bool evaluation() = 0;
		std::vector<Variable*> getVariables();
		void setVariables(std::vector<Variable*> variables);
		void addVariable(Variable* variable);
		int getArite();
		void setArite(int arite);
		virtual std::string getType() = 0;
		virtual void remove(Variable *currentVar, Variable *v2, int *removedSize) = 0;
		bool isInVars(Variable *v);
};
