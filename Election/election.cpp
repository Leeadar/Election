#include "election_header.h"
#include "merge_sort.h"

Election::Election(int day, int month, int year)
{
	if (year <= 0)
	{
		throw invalid_argument("ERROR - Non positive number.");
	}
	if (month < 1 || month > 12)
	{
		throw invalid_argument("ERROR - Month invalid.");
	}
	int dayInMonth = getDaysInMonth(month);
	if (day > dayInMonth)
	{
		string str = "Error - in month " + to_string(month) + " there are only " + to_string(dayInMonth) + " days.";
		throw invalid_argument(str);
	}

	this->day = day;
	this->month = month;
	this->year = year;
	this->citizensCounter = 0;
	this->partiesCounter = 0;
	this->districtsCounter = 0;
	this->votersNum = 0;
}

Election::~Election()
{
	for (int i = 0; i < partiesCounter; i++)
	{
		delete parties[i];
	}
	for (int i = 0; i < districtsCounter; i++)
	{
		delete districts[i];
	}
	for (auto i = citizens.begin(); i != citizens.end(); i++)
	{
		delete i->second;
	}
}

// Operator "="
const Election& Election::operator=(const Election& other)
{
	if (this != &other)
	{
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
		this->citizensCounter = other.citizensCounter;
		this->partiesCounter = other.partiesCounter;
		this->districtsCounter = other.districtsCounter;
		this->votersNum = other.votersNum;

		citizens.clear();
		parties.clear();
		districts.clear();
		citizens = other.citizens;
		parties = other.parties;
		districts = other.districts;
	}
	return *this;
}

// Adds a district and updates the amount of districts in the election
void Election::addDistrict(string name, int electors, int type)
{
	District* district;
	if (type == 1)
	{
		district = new Uni_District(name, name.length(), this->districtsCounter+1, electors);
	}
	else if (type == 2)
	{
		district = new Div_District(name, name.length(), this->districtsCounter + 1, electors);
	}
	districts.push_back(district);
	district->setVotesSize(this->partiesCounter);
	setDistrictsCounter(); // increase the amount of total districts by 1
}

// Adds a citizen to the elections & to the district
void Election::addCitizen(string name, int id, int birthYear, int districtId)
{
	Citizen* person = new Citizen(name, id, birthYear, districts[districtId-1]);
	// Add to the ELECTION citizen array:
	citizens[person->getId()] = person;
	// Add to the DISTRICT citizen array:
	districts[(person->getDistrict())->get_districtId() - 1]->addCitizen(person);
	this->citizensCounter++;
}

// Adds a new party
void Election::addParty(string name, Citizen *person)
{
	isElectorOrCandidate(person); // Check person is valid
	this->partiesCounter++; // Update party counter
	Party* newParty = new Party(name, this->partiesCounter, person); // create new party
	parties.push_back(newParty); // Add to the ELECTION parties array
	for (int i = 0; i < districtsCounter; i++) // Updates the number of parties in each district
	{
		districts[i]->setVotesSize(this->partiesCounter);
	}
}

// Adds elector to a party
void Election::addElector(Citizen* person, Party* party, int districtId)
{
	isElectorOrCandidate(person);
	parties[party->getPartyID() - 1]->addElector(person, districtId); // add to the party's electors list
}

// Checks if the citizen is not allready a party candidate OR elector
void Election::isElectorOrCandidate(Citizen* person)
{
	for (int i = 0; i < partiesCounter; i++) // Checks if citizen is already an elector or candidate in each party
	{
		if (parties[i]->isElectorOrCand(person))
		{
			throw invalid_argument("ERROR - The citizen is already an elector / candidate.");
		}
	}
}

// Adds ONE VOTE to a party
void Election::vote(int id, int partyId)
{
	Citizen* person = nullptr;
	if (citizens.count(id) == 1) // Check person exists
	{
		person = citizens.find(id)->second;
	}
	else
	{
		throw invalid_argument("ERROR - No citizen with that ID.");
	}
	if (person->getVote() == true) // Check the citizen hasnt voted yet
	{
		throw invalid_argument("ERROR - The citizen has already voted.");
	}
	if (partyId > partiesCounter || partiesCounter <= 0)
	{
		throw invalid_argument("ERROR -  The Party does not exist.");
	}
	districts[(person->getDistrict())->get_districtId()-1]->addOneVote(partyId); // adds vote to district
	this->votersNum++;
	person->setVote(true); // set the citizen has already voted
	cout << "Thank you for your vote !  #VOTE" << this->year << endl << endl;
}

// Checks if there is enough electors on the district
bool Election::isEnoughElectors(int districtID)
{
	DynamicArray<int> electorsPerParty = districts[districtID - 1]->getElectorsPerParty();

	for (int i = 0; i < partiesCounter; i++) // Check there is enough electors
	{
		if (!parties[i]->isPartyHasEnoughElectors(districtID, electorsPerParty[i]))
		{
			return false;
		}
	}
	return true;
}

// The function prints all the districts
void Election::printDistricts() const
{
	cout << endl;
	if (districtsCounter == 0)
	{
		throw invalid_argument("Error - There Are No Districts.");
	}
	for (int i = 0; i < districtsCounter; i++)
	{
		cout << *districts[i];
		districts[i]->printType();
	}
	cout << endl;
}

// The function prints all the citizens
void Election::printCitizens() const
{
	cout << endl;
	if (citizensCounter == 0)
	{
		throw invalid_argument("Error - There Are No Citizens.");
	}
	for (auto i = citizens.begin(); i != citizens.end(); i++)
	{
		cout << *(i->second) << endl;
	}
	cout << endl;
}

// The function prints all the parties
void Election::printParties() const
{
	cout << endl;
	if (partiesCounter == 0)
	{
		throw invalid_argument("Error - There Are No Parties.");
	}
	for (int i = 0; i < partiesCounter; i++)
	{
		cout << *parties[i];
		parties[i]->printElectors();
	}
	cout << endl;
}

// Reset votes after election
void Election::resetVotes()
{
	cout << endl << "Reset Election Data." << endl;
	for (auto itr = citizens.begin(); itr != citizens.end(); itr++)
	{
		itr->second->setVote(false);
	}
	for (int i = 0; i < partiesCounter; i++)
	{
		parties[i]->reset();
	}
	for (int i = 0; i < districtsCounter; i++)
	{
		districts[i]->reset();
	}
	this->votersNum = 0;
}

// Return a PartySort sorted array
partySort** Election::sortParties(DynamicArray<int> resaultCheck)
{
	partySort** partyResaultArr = new partySort * [partiesCounter];
	partySort* tempParty = nullptr;
	for (int i = 0; i < partiesCounter; i++) // Create parties array - for the future sort
	{
		tempParty = new partySort[1];
		tempParty->partyId = i;
		tempParty->electors = resaultCheck[i];
		partyResaultArr[i] = tempParty;
	}
	mergeSort(partyResaultArr, partiesCounter); // sort the results
	return partyResaultArr;
}

// Prints date
void Election::printDate() const
{
	cout << endl << "Election date: " << this->day << "/" << this->month << "/" << this->year << endl;
}

// Save Election
void Election::saveEelection(ofstream& out_file)
{
	try {
		// Save election type:
		saveTypeElection(out_file);
		checkOutfile(out_file);
		// Save amount of votes:
		out_file.write((char*)&votersNum, sizeof(int));
		checkOutfile(out_file);

		// Save District array:
		out_file.write((char*)&districtsCounter, sizeof(int));
		checkOutfile(out_file);
		for (int i = 0; i < this->districtsCounter; i++)
		{
			districts[i]->saveDistrict(out_file);
			checkOutfile(out_file);
		}

		// Save Parties array:
		out_file.write((char*)&partiesCounter, sizeof(int));
		checkOutfile(out_file);
		for (int i = 0; i < partiesCounter; i++)
		{
			parties[i]->saveParty(out_file);
			checkOutfile(out_file);
		}

		cout << endl << "Election saved." << endl;
	}
	catch (exception & ex)
	{
		cout << endl << ex.what() << endl;
	}
}

// Load Election
void Election::loadEelection(ifstream& in_file)
{
	int len, id, yearOfBirth, districtId, counterD;
	string name;
	bool vote;

	in_file.read((char*)&this->votersNum, sizeof(int));
	checkInfile(in_file);
	citizens.clear(); // Check file & delete everything in case of an error
	Citizen* person;

	/// Districts load:
	in_file.read((char*)&this->districtsCounter, sizeof(int));
	checkInfile(in_file); // Check file & delete everything in case of an error
	districts.clear();
	for (int i = 0; i < this->districtsCounter; i++)
	{
		districts.push_back(loadDistrict(in_file)); // Create district
		// Add citizens to district:
		counterD = districts[i]->get_citizenCount(); // To know hw many citizens there is
		districts[i]->set_citizenCount(0); // Make the counter of the citizen zero, because its increase it on addCitizen
		for (int j = 0; j < counterD; j++) // Citizens create
		{
			getline(in_file, name, '\0');
			in_file.read((char*)&id, sizeof(int));
			in_file.read((char*)&yearOfBirth, sizeof(int));
			in_file.read((char*)&districtId, sizeof(int));
			checkInfile(in_file); // Check file & delete everything in case of an error
			person = new Citizen(name, id, yearOfBirth, districts[i]);
			citizens[person->getId()] = person;
			districts[(person->getDistrict())->get_districtId() - 1]->addCitizen(person);
			this->citizensCounter++;
			in_file.read((char*)&vote, sizeof(bool));
			checkInfile(in_file); // Check file & delete everything in case of an error
			person->setVote(vote); // Set the citizen voted or not
		}
	}

	/// Parties load:
	in_file.read((char*)&this->partiesCounter, sizeof(int));
	checkInfile(in_file); // Check file & delete everything in case of an error
	parties.clear();
	for (int i = 0; i < partiesCounter; i++)
	{
		parties.push_back(loadParty(in_file));
	}

	cout << endl << "Election loaded." << endl << endl;
	return;
}

// Load District
District* Election::loadDistrict(ifstream& in_file)
{
	District* newDistrict = nullptr;
	District::dType disT;
	int len, districtID, electors, citizenCount, voteArrSize, citizenListSize, votePartiesCounter, votersCounter, vote;
	string districtName;
	DynamicArray<int> votes;
	char* cstr;
	try
	{
		in_file.read((char*)&disT, sizeof(District::dType));
		// Get district name:
		getline(in_file, districtName, '\0');
		len = districtName.length();
		checkInfile(in_file);
		// Get electors:
		in_file.read((char*)&electors, sizeof(int));
		in_file.read((char*)&districtID, sizeof(int));
		checkInfile(in_file);
		// Create district:
		if (disT == District::UNITED)
		{
			newDistrict = new Uni_District(districtName, len, districtID, electors);
		}
		else if (disT == District::DIVIDED)
		{
			newDistrict = new Div_District(districtName, len, districtID, electors);
		}
		// Get fields:
		in_file.read((char*)&citizenCount, sizeof(int));
		in_file.read((char*)&votePartiesCounter, sizeof(int));
		in_file.read((char*)&votersCounter, sizeof(int));
		checkInfile(in_file);
	}
	catch (exception & ex)
	{
		deleteDistrictLoad(districtID);// delete all districts & citizens
		throw invalid_argument("Error load file.");
	}
	try
	{
		for (int i = 0; i < votePartiesCounter; i++)
		{
			in_file.read((char*)&vote, sizeof(int));
			votes.push_back(vote);
		}
		checkInfile(in_file);
		// Set fields:
		newDistrict->set_citizenCount(citizenCount);
		newDistrict->set_votePartiesCounter(votePartiesCounter);
		newDistrict->set_votersCounter(votersCounter);
		newDistrict->set_votes(votes);
		return newDistrict;
	}
	catch (exception & ex)
	{
		deleteDistrictLoad(districtID+1); // delete all districta & citizens INCLUDE the current one
		throw invalid_argument("Error load file.");
	}
}

// Load Party
Party* Election::loadParty(ifstream& in_file)
{
	string partyName;
	int len, candidateID, partyId, electorsNum, id, districtID;
	Citizen* person;
	try
	{
		getline(in_file, partyName, '\0');
		checkInfile(in_file);
		in_file.read((char*)&candidateID, sizeof(int));
		in_file.read((char*)&partyId, sizeof(int));
		checkInfile(in_file);
	}
	catch (exception & ex)
	{
		deleteDistrictLoad(districtsCounter);// Delete previous parties & all districts & all citizens
		throw invalid_argument("Error load file.");
	}
	try
	{
		Citizen* candidate = citizens.find(candidateID)->second;
		Party* newParty = new Party(partyName, partyId, candidate);
		in_file.read((char*)&electorsNum, sizeof(int));
		for (int i = 0; i < electorsNum; i++)
		{
			in_file.read((char*)&id, sizeof(int));
			in_file.read((char*)&districtID, sizeof(int));
			checkInfile(in_file);
			person = citizens.find(id)->second;
			newParty->addElector(person, districtID); // add to the party's electors list
		}
		return newParty;
	}
	catch (exception & ex)
	{
		deleteDistrictLoad(districtsCounter);// Delete previous parties & all districts & all citizens
		// Delete parties:
		for (int i = 0; i < partyId-1; i++)
		{
			delete parties[i];
		}
		throw invalid_argument("Error load file.");
	}	
}

// Check file read
void Election::checkInfile(ifstream& in_file)
{
	if (!in_file.good())
	{
		deleteDistrictLoad(districtsCounter); // Delete all citizens & district created
		throw invalid_argument("Error in Read to File.");
	}
}

// Check file & delete everything in case of an error
void Election::checkOutfile(ofstream& out_file)
{
	if (!out_file.good())
	{
		throw invalid_argument("Error in Write to File.");
	}
}

// Return num of days in given month
int Election::getDaysInMonth(int month)
{
	if (month == 2)
	{
		return 28;
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		return 31;
	}
	else
	{
		return 30;
	}
}

// In case of Error in file load - delete district & citizens
void Election::deleteDistrictLoad(int districtID)
{
	for (int i = 0; i < districtID - 1; i++)
	{
		for (int j = 0; j < districts[i]->get_citizenCount(); j++)
		{
			delete districts[i]->get_citizenList()[j];
		}
		delete districts[i];
	}
}