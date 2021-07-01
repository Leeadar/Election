#include "divided_district_header.h"

Div_District::Div_District(string newName, int nameSize, int districtId, int electors) : District(newName, nameSize, districtId, electors)
{
}

Div_District:: ~Div_District()
{
}

// Returning the array with the given electors to each party
DynamicArray<int> Div_District::resultsCheck()
{
	return this->electorsPerParty;
}

// Print the electors given to each party - assuming PS is sorted
void Div_District::printResault(partySort** ps, DynamicArray<Party*> p)
{
	for (int i = 0; i < this->votePartiesCounter; i++)
	{
		if (electorsPerParty[ps[i]->partyId] > 0)
		{
			cout << p[ps[i]->partyId]->getCandidate()->getName() << " - gets " << electorsPerParty[ps[i]->partyId] << " electors." << endl;
		}
	}
	printResults();
}

// Print district
ostream& operator<<(ostream& os, const Div_District& district)
{
	const Div_District* divided = dynamic_cast<const Div_District*>(&district);
	os << divided->name << ", " << "ID: " << divided->districtId << ", " << divided->electors << " electors, Type - divided district.";
	return os;
}

void Div_District::saveDistrictType(ofstream& out_file)
{
	dType type = DIVIDED;
	out_file.write((char*)&type, sizeof(dType));
}

void Div_District::printType() const
{
	cout << ", Type - Devided District." << endl;
}