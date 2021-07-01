#pragma once
#include "election_header.h"

// Normal Election Class - inherit from election
class Nor_Election : public Election
{

public:
	Nor_Election(int day, int month, int year);
	Nor_Election(const Nor_Election&) = delete;
	const Nor_Election& operator=(const Nor_Election&) = delete;
	virtual ~Nor_Election();

public:
	virtual void result() override;
	bool electorsFromPartyToDistrict(int districtID);
	virtual void saveTypeElection(ofstream& out_file) override;
};
