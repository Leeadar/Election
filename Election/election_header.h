#pragma once
#include <string>
#include <iostream>
#include <typeinfo>
#include <map>
#include "district_header.h"
#include "united_district_header.h"
#include "divided_district_header.h"

using namespace std;

class Nor_Election;
class Sim_Election;

class Election
{
protected: // Fields:
	map<int, Citizen*> citizens; // Citizens map
	DynamicArray<Party*> parties; // Parties array
	DynamicArray<District*> districts; // Districts array
	int day, month, year; // Election date
	int citizensCounter, partiesCounter, districtsCounter; // How many citizens / parties / districts there are
	int votersNum; // How many people have voted

public: // Ctors:
	Election(int day, int month, int year);
	Election(Election& other) = delete;
	const Election& operator=(const Election& other);
	virtual ~Election();
	enum eType { NORMAL, SIMPLE };

public: // Getters:
	int get_votersNum() const{ return votersNum; };
	int get_day() const { return day; };
	int get_month() const { return month; };
	int get_year() const { return year; };
	int get_citizensCounter() const { return citizensCounter; };
	int get_partiesCounter() const { return partiesCounter; };
	int get_districtsCounter() const { return districtsCounter; };
	map<int, Citizen*> get_citizens() { return citizens; };
	DynamicArray<Party*> get_parties() { return parties; };
	DynamicArray<District*> get_districts() { return districts; };
	District* get_district(int i) { return districts[i - 1]; };
	Party* get_party(int i) { return parties[i - 1]; };

public: // Methodes:
	void setDistrictsCounter() { districtsCounter++; };
	void setPartiesCounter() { partiesCounter++; };
	void addDistrict(string name, int electors, int type);
	void addCitizen(string name, int id, int birthYear, int districtId);
	void addParty(string name, Citizen *person);
	void isElectorOrCandidate(Citizen* person);
	void addElector(Citizen* person, Party* party, int districtId);
	void printDistricts() const;
	void printCitizens() const;
	void printParties() const;
	void vote(int id, int partyId);
	bool isEnoughElectors(int districtID);
	partySort** sortParties(DynamicArray<int> resaultCheck);
	virtual void result() {}; // override
	void resetVotes();
	void printDate() const;
	Citizen& operator[](int idx) { return *citizens[idx]; };
	int getDaysInMonth(int month);
	void deleteDistrictLoad(int districtID);

public: // File Methodes:
	void saveEelection(ofstream& out_file);
	virtual void saveTypeElection(ofstream& out_file) {}; // override
	void loadEelection(ifstream& in_file);
	District* loadDistrict(ifstream& in_file);
	Party* loadParty(ifstream& in_file);
	void checkInfile(ifstream& in_file);
	void checkOutfile(ofstream& out_file);
};