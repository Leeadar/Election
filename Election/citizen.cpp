#include "citizen_header.h"

Citizen::Citizen(const string newName, int id, int yearOfBirth, District* district)
{
	if ((id / 100000000) > 10 || (id / 100000000) < 1)
	{
		throw invalid_argument("Id Not Valid");
	}
	this->name = newName;
	this->id = id;
	this->yearOfBirth = yearOfBirth;
	this->district = district;
	this->vote = false;
}

Citizen::~Citizen() {}

// Prints citizen
ostream& operator<<(ostream& os, const Citizen& citizen)
{
	os << "Name: " << citizen.name << ", ID: " << citizen.id << ", Year Of Birth: "
		<< citizen.yearOfBirth << ", District:" << citizen.district->getName();
	return os;
}

void Citizen::saveCitizen(ofstream& out_file)
{
	int id = this->district->getDistrictId();
	out_file.write(name.c_str(), name.length() + 1);
	out_file.write((char*)&this->id, sizeof(int));
	out_file.write((char*)&this->yearOfBirth, sizeof(int));
	out_file.write((char*)&this->id, sizeof(int));
	out_file.write((char*)&this->vote, sizeof(bool));
}