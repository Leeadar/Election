#include "party_header.h"

Party::Party(const string newName, int partyId, Citizen* candidate)
{
	if (partyId < 0)
	{
		throw invalid_argument("ERROR - Party Load");
	}
	this->name = newName;
	this->partyId = partyId;
	this->electorsWon = 0;
	this->candidate = candidate;
}

Party::~Party()
{
	electorsList.clear();
}

// This func adds elector to the electors list into a sorted list by district ID
void Party::addElector(Citizen* elector, int districtID)
{
	electorData* el = new electorData;
	el->citizen = elector;
	el->districtID = districtID;
	list<electorData*>::iterator itr = electorsList.begin();

	while (itr != electorsList.end() && (*itr)->districtID < districtID)
	{
		itr++;
	}
	electorsList.insert(itr, el);
}

// This func checks if citizen already an elector or candidate
bool Party::isElectorOrCand(Citizen* elector)
{
	list<electorData*>::iterator itr;
	if (elector == this->candidate)
	{
		return true;
	}
	for (itr = electorsList.begin(); itr != electorsList.end(); itr++)
	{
		if ((*itr)->citizen->getId() == elector->getId())
		{
			return true;
		}
	}
	return false;
}

// Compare 2 electors
bool compareElectors(electorData*& t1, electorData*& t2)
{
	if ((t1)->districtID < (t2)->districtID)
		return false;
	else
		return true;
}

// Sort the electors list by district
void Party::sortElectors()
{
	list<electorData*>::iterator start = electorsList.begin();
	list<electorData*>::iterator end = electorsList.end();
	//sort(electorsList.begin(), electorsList.end(), compareElectors);
	electorsList.sort(compareElectors);
}

// Adds electors to the party
Citizen** Party::electorsToParty(int districtID, int amount)
{
	list<electorData*>::iterator itr = electorsList.begin();
	int i = 0;
	if (amount == 0)
		return nullptr;

	Citizen** electorsArray = new Citizen * [amount];

	while (i < amount)
	{
		if ((*itr)->districtID == districtID)
		{
			electorsArray[i] = (*itr)->citizen;
			i++;
		}
		itr++;
	}

	return electorsArray;
}

// Checks that the party have enough electors for be in the district
bool Party::isPartyHasEnoughElectors(int districtID, int amount)
{
	list<electorData*>::iterator itr = electorsList.begin();
	int count = 0;

	while (itr != electorsList.end() && (*itr)->districtID <= districtID)
	{
		if ((*itr)->districtID == districtID)
		{
			count++;
		}
		itr++;
	}
	return (count >= amount);
}

// Print all the party electors
void Party::printElectors() const
{
	list<electorData*>::iterator itr;
	cout << "Electors List:" << endl;
	for (auto itr = electorsList.begin(); itr != electorsList.end(); itr++)
	{
		cout << "Elector of district: " << (*itr)->districtID << ", " << *((*itr)->citizen) << endl;
	}

	cout << endl;
}

// Print X the party electors
void Party::printElectors(int X) const
{
	list<electorData*>::iterator itr;
	int counter = 0;
	cout << "   Electors List:" << endl;
	for (auto itr = electorsList.begin(); itr != electorsList.end(); itr++)
	{
		if (counter < X)
		{
			cout << "   Elector: " << *((*itr)->citizen) << endl;
		}
		counter++;
	}
	cout << endl;
}

void Party::setElectorsWonCounter(int x)
{
	if (x<0)
	{
		throw invalid_argument("Error with electors calculation.");
	}
	else
	{
		electorsWon += x;
	}
}

// Print party
ostream& operator<<(ostream& os, const Party& p)
{
	os << "Party: " << p.name << ", Party ID:" << p.partyId << endl << "Candidate: " << *(p.candidate) << endl;
	return os;
}

// Save party to file
void Party::saveParty(ofstream& out_file)
{
	list<electorData*>::iterator itr = electorsList.begin();
	int candidateID = candidate->getId();
	int id;
	int electorsNum = numOfElectors();

	// Save fields:
	out_file.write(name.c_str(), name.length() + 1);
	out_file.write((char*)&candidateID, sizeof(int));
	out_file.write((char*)&this->partyId, sizeof(int));

	// Save electors list:
	out_file.write((char*)&electorsNum, sizeof(int));
	while (itr != electorsList.end())
	{
		id = (*itr)->citizen->getId();
		out_file.write((char*)&id, sizeof(int));
		out_file.write((char*) & (*itr)->districtID, sizeof(int));
		itr++;
	}
}

// Return how many electors the party have of all districts
int Party::numOfElectors()
{
	return electorsList.size();
}