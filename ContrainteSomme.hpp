#pragma once
#include <vector>
#include "Contrainte.hpp"

class ContrainteSomme : public Contrainte{
	private:
		int m_resultat;
	public:
		ContrainteSomme(std::vector<Variable> variables, int arite, int resultat);
		bool evaluation();
		int getResultat();
		void setResultat(int value);
};