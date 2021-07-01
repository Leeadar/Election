#include "united_district_header.h"

Uni_District::Uni_District(string newName, int nameSize, int districtId, int electors) : District(newName, nameSize, districtId, electors)
{
}

Uni_District:: ~Uni_District()
{
}

// Calculates the winning party - return the party ID
int Uni_District::resultsCheck()
{
	return votes.findMax();
}


// Print district
ostream& operator<<(ostream& os, const Uni_District& district)
{
	const Uni_District* united = dynamic_cast<const Uni_District*>(&district);
	os << united->name << ", " << "ID: " << united->districtId << ", " << united->electors << " electors, Type - United District.";
	return os;
}

void Uni_District::saveDistrictType(ofstream& out_file)
{
	dType type = UNITED;
	out_file.write((char*)&type, sizeof(dType));
}

void Uni_District::printType() const
{
	cout << ", Type - United District." << endl;
}