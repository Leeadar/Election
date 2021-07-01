#include "district_header.h"

District::District(const string newName, int nameSize, int districtId, int electors)
{
	if (electors <= 0)
	{
		throw invalid_argument("ERROR - Not Enoght Electors.");
	}
	this->name = newName;
	this->districtId = districtId;
	this->electors = electors;
	this->votersCounter = 0;
	this->citizenCount = 0;
	this->votePartiesCounter = 0;
}

 District::District(const District& other)
 {
	this->name = other.name;
	this->districtId = other.districtId;
	this->electors = other.electors;
	this->votersCounter = other.votersCounter;
	this->citizenCount = other.citizenCount;
	this->votePartiesCounter = other.votePartiesCounter;

	this->votes = other.votes;
	this->electorsPerParty = other.electorsPerParty;
	this->citizenList = other.citizenList;
	this->electorsList = other.electorsList;
}

District::~District()
{
}

// Adds citizen to the citizen list array
void District::addCitizen(Citizen* person)
{
	this->citizenList.push_back(person);
	this->citizenCount++;
}

// Set the votes array to a new size accoarding to the parties number
void District::setVotesSize(int partiesNumber)
{
	for (int i = votePartiesCounter; i < partiesNumber; i++)
	{
		votes.push_back(0);
	}
	this->votePartiesCounter = partiesNumber;
}

// Add ONE citizen vote
void District::addOneVote(int partyNum)
{
	if (partyNum < 0)
	{
		throw invalid_argument("Error with vote.");
	}
	this->votes[partyNum - 1] += 1;
	this->votersCounter++;
}

// Adds elector to the district
void District::addElector(Citizen* person)
{
	electorsList.push_back(person);
}

// Set into electorsPerParty - how many electors to give to each party
void District::howManyElectorsFromEachParty()
{
	float counter = 0;
	float electorRate = static_cast<float>(votersCounter) / static_cast<float>(electors); // How many votes for 1 electors
	int indexMax = 0;
	DynamicArray<float> floatArr(votePartiesCounter);

	electorsPerParty.clear();

	// Set arrays:
	for (int i = 0; i < votePartiesCounter; i++)
	{
		electorsPerParty.push_back(0);
		floatArr.push_back(static_cast<float>(votes[i])); // Cast the array from int to float
	}

	for (int i = 0; i < votePartiesCounter; i++)
	{
		while (floatArr[i] - electorRate > 0)
		{
			floatArr[i] -= electorRate;
			electorsPerParty[i]++;
			counter++;
		}
	}

	while (counter < electors)
	{
		indexMax = floatArr.findMax();
		floatArr[indexMax] = 0;
		electorsPerParty[indexMax]++;
		counter++;
	}

	floatArr.clear();
}

// Print the election result of the district
void District::printResults() const
{
	cout << "Vote rate in the district: " << (static_cast<float>(votersCounter)) / (static_cast<float>(citizenCount)) * 100 << "%" << endl;
	for (int i = 0; i < votePartiesCounter; i++)
	{
		cout << "Party ID - " << i + 1 << ": Total Votes - " << votes[i] << ", Vote Percent - " << (static_cast<float>(votes[i]) / static_cast<float>(votersCounter)) * 100 << "%" << endl;
	}
}

// Reset the district for a new election
void District::reset()
{
	for (int i = 0; i < votePartiesCounter; i++)
	{
		this->votes[i] = 0;
	}

	this->votersCounter = 0;
}

// Operator '='
const District& District::operator=(const District& other)
{
	if (this != &other)
	{
		name = other.name;
		this->districtId = other.districtId;
		this->electors = other.electors;
		this->votersCounter = other.votersCounter;
		this->citizenCount = other.citizenCount;
		this->votePartiesCounter = other.votePartiesCounter;

		this->votes.clear();
		this->electorsPerParty.clear();
		this->citizenList.clear();
		this->electorsList.clear();

		this->votes = other.votes;
		this->electorsPerParty = other.electorsPerParty;
		this->citizenList = other.citizenList;
		this->electorsList = other.electorsList;
	}
	return *this;
}

// Print district
ostream& operator<<(ostream& os, const District& district)
{
	os << district.name << ", " << "ID: " << district.districtId << ", " << district.electors << " Electors";
	return os;
}

// Save distirct type to file
void District::saveDistrictType(ofstream& out_file)
{
	// Calling to the func in the dirved class
}

// Save district to file
void District::saveDistrict(ofstream& out_file)
{
	// Save district type:
	saveDistrictType(out_file);

	// Save fields:
	out_file.write(name.c_str(), name.length() + 1);
	out_file.write((char*)&this->electors, sizeof(int));
	out_file.write((char*)&this->districtId, sizeof(int));
	out_file.write((char*)&this->citizenCount, sizeof(int));
	out_file.write((char*)&this->votePartiesCounter, sizeof(int));
	out_file.write((char*)&this->votersCounter, sizeof(int));
	// Save vote array:
	for (int i = 0; i < votePartiesCounter; i++)
	{
		out_file.write((char*)&this->votes[i], sizeof(int));
	}
	// Save citizens array:
	for (int i = 0; i < citizenCount; i++)
	{
		citizenList[i]->saveCitizen(out_file);
	}
}
