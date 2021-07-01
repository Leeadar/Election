#pragma once
#include "district_header.h"

// United District Class - inherit from district
class Uni_District : public District
{

public:
	Uni_District(string name, int nameSize, int districtId, int electors);
	Uni_District(const Uni_District&) = delete;
	const Uni_District& operator=(const Uni_District&) = delete;
	virtual ~Uni_District();

public:
	int resultsCheck();
	friend ostream& operator<<(ostream& os, const Uni_District& district);
	virtual void saveDistrictType(ofstream& out_file);
	virtual void printType() const override;
};

