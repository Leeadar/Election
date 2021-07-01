#pragma once
#include "district_header.h"

// Divided District Class - inherit from district
class Div_District : public District
{

public:
	Div_District(string name, int nameSize, int districtId, int electors);
	Div_District(const Div_District&) = delete;
	const Div_District& operator=(const Div_District&) = delete;
	virtual ~Div_District();

public:
	DynamicArray<int> resultsCheck();
	void printResault(partySort** ps, DynamicArray<Party*> p);
	friend ostream& operator<<(ostream& os, const Div_District& district);
	virtual void saveDistrictType(ofstream& out_file);
	virtual void printType() const override;
};
