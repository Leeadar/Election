#pragma once
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include "citizen_header.h"

using namespace std;
class Citizen;

// Struct of all electors:
struct electorData {
	Citizen* citizen;
	int districtID;
};

class Party
{
private: // Fields:
	string name;
	int partyId, electorsWon;
	Citizen* candidate;
	list<electorData*> electorsList; // List of electors

public: // Ctors:
	Party(const string newName, int partyId, Citizen* candidate);
	Party(const Party&) = delete;
	const Party& operator=(const Party&) = delete;
	~Party();

public: // Methodes:
	Citizen* getCandidate() { return candidate; };
	int getPartyID() const { return partyId; };
	Citizen** electorsToParty(int districtID, int amount);
	void setElectorsWonCounter(int x);
	void reset() { electorsWon = 0; };
	const string getPartyName() const { return name; };
	void addElector(Citizen* elector, int districtID);
	void printElectors() const;
	void printElectors(int X) const;
	bool isElectorOrCand(Citizen* elector);
	bool isPartyHasEnoughElectors(int districtID, int amount);
	friend ostream& operator<<(ostream& os, const Party& party);
	int numOfElectors();
	void sortElectors();
	//static bool compareElectors(electorData*& t1, electorData*& t2);

public: // Save party
	void saveParty(ofstream& out_file);
};
