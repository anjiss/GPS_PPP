#pragma once
#include "Equation_database.h"
#include "Matrix.h"

class Adjustment_PPP
{
public:
	Adjustment_PPP(Equation_database a);
	~Adjustment_PPP();

public:
	Equation_database ppp;
};
