#pragma once
#include <string>
#include <iostream>
#include "citizen_header.h"
#include "party_header.h"
#include "dynamic_array.h"

using namespace std;
class Citizen;
class Party;

struct partySort { // List of parties - for sort and present the results
	int partyId;
	int electors;
};

class District
{
protected: // Fields:
	string name;
	int districtId, electors, citizenCount, votePartiesCounter, votersCounter;
	DynamicArray<Citizen*> citizenList;
	DynamicArray<Citizen*> electorsList;
	DynamicArray<int> votes; // Counts the votes for each party
	DynamicArray<int> electorsPerParty;  // How many electors won in each party

public: // Ctors:
	District(const string newName, int nameSize, int districtId, int electors);
	District(const District& other);
	const District& operator=(const District& other);
	virtual ~District();
	enum dType { DIVIDED, UNITED };

public: // Getters
	int get_districtId() const { return districtId; };
	int get_electors() const { return electors; };
	int get_citizenCount() const { return citizenCount; };
	int get_votePartiesCounter() const { return votePartiesCounter; };
	int get_votersCounter() const { return votersCounter; };
	int getPartyVotes(int partyIndex) const { return votes[partyIndex]; };
	DynamicArray<int> get_votes() { return votes; };
	DynamicArray<int> get_electorsPerParty() { return electorsPerParty; };
	DynamicArray<Citizen*> get_citizenList() { return citizenList; };
	DynamicArray<Citizen*> get_electorsList() { return electorsList; };

public: // Setters
	void set_citizenCount(int x) { this->citizenCount = x; };
	void set_votePartiesCounter(int x) { this->votePartiesCounter = x; };
	void set_votersCounter(int x) { this->votersCounter = x; };
	void set_votes(DynamicArray<int> x) { votes.clear(); votes = x; };

public: // Methodes
	int getDistrictId() const { return districtId; };
	int getVotersCounter() const { return votersCounter; };
	DynamicArray<int> getElectorsPerParty() const { return electorsPerParty; };
	int getElectorsNum() const { return electors; };
	const string getName() const { return name; };
	void addCitizen(Citizen* person);
	void addElector(Citizen* person);
	void setVotesSize(int partiesNumber);
	void addOneVote(int partyNum);
	void howManyElectorsFromEachParty();
	void printResults() const;
	void reset();
	friend ostream& operator<<(ostream& os, const District& district);
	virtual void printType() const {};

public: // save
	virtual void saveDistrictType(ofstream& out_file);
	void saveDistrict(ofstream& out_file);
};