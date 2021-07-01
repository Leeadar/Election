#pragma once
#include "election_header.h"

// Simple Election Class - inherit from election
class Sim_Election : public Election
{
public:
	Sim_Election(int day, int month, int year, int electors);
	Sim_Election(const Sim_Election&) = delete;
	const Sim_Election& operator=(const Sim_Election&) = delete;
	virtual ~Sim_Election();

public:
	virtual void result() override;
	bool electorsFromPartyToDistrict();
	virtual void saveTypeElection(ofstream& out_file) override;
};