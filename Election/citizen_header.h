#pragma once
#include <iostream>
#include "district_header.h"

using namespace std;
class District;

class Citizen
{
private: // Fields:
	string name;
	District* district; // Pointer to district
	int id, yearOfBirth;
	bool vote; // Is the citizen voted

public: // Ctors:
	Citizen(const string newName, int id, int yearOfBirth, District* district);
	Citizen(const Citizen&) = delete;
	void operator=(const District&) = delete;
	~Citizen();

public: // Methodes:
	const string getName() const { return name; };
	int getId() const { return id; };
	int getYear() const { return yearOfBirth; };
	District* getDistrict() { return district; };
	bool getVote() { return vote; };
	void setVote(bool status) { vote = status; };
	friend ostream& operator<<(ostream& os, const Citizen& citizen);

public: // File Methodes:
	void saveCitizen(ofstream& out_file);
};
