#include "simple_election_header.h"

Sim_Election::Sim_Election(int day, int month, int year, int electors) : Election(day, month, year)
{
	string districtName = "Demo district";
	addDistrict(districtName, electors,2); // Create a demo divided district
}

Sim_Election::~Sim_Election()
{
	// Same as election
}

/* Adds the electors to the district acording to the parties result
   Caculate the general results,
   And then print them */
void Sim_Election::result()
{
	if (partiesCounter == 0 || districtsCounter == 0 || citizensCounter == 0) // if there is no parties
	{
		throw invalid_argument("Error - Election Is Not Valid.");
	}

	DynamicArray<int> divResult;
	DynamicArray<int> resultCheck(partiesCounter); // Counts total electors to each party
	DynamicArray<int> partyTotalVotes(partiesCounter); // Counts total votes to each party

	int i, tempID;
	partySort** partyResaultArr;

	for (i = 0; i < partiesCounter; i++) // initiate the arrays
	{
		resultCheck.push_back(0);
		partyTotalVotes.push_back(0);
	}

	i = 0;
	districts[i]->howManyElectorsFromEachParty(); // Caculate how to give the electors

	/// Caculate the results for each party and sort the parties into a new arr:
	if (isEnoughElectors(districts[i]->getDistrictId()) && (districts[i]->getVotersCounter() > 0)) // if there is enough electors citizens
	{
		divResult = dynamic_cast<Div_District*>(districts[i])->resultsCheck(); // How many electors to each party array
		for (int i = 0; i < partiesCounter; i++)
		{
			parties[i]->setElectorsWonCounter(divResult[i]);
			resultCheck[i] += divResult[i];
		}
		electorsFromPartyToDistrict(); // Add the electors to the district
		for (int j = 0; j < partiesCounter; j++) // Adds the result to the general result:
		{
			partyTotalVotes[j] += districts[i]->getPartyVotes(j);
		}
	}
	else
	{
		throw invalid_argument("Error - Election Is Not Valid !");
	}

	/// Sort the results:
	partyResaultArr = sortParties(resultCheck);

	/// Print finale resaults:
	cout << endl << "~~~~~~~~   The Elections Results   ~~~~~~~~" << endl << endl;
	cout << "General Vote Rate : " << static_cast<double>(static_cast<double>(votersNum) / static_cast<double>(citizensCounter)) * 100 << "%" << endl << endl; // Print vote rate

	for (int j = 0; j < partiesCounter; j++)
	{
		tempID = partyResaultArr[j]->partyId;
		cout << j + 1 << ". Party: " << parties[tempID]->getPartyName() << endl;
		cout << "   Electors: " << resultCheck[tempID] << endl;
		cout << "   Total votes: " << partyTotalVotes[tempID] << endl;
		cout << "   Vote rate: " << (static_cast<double>(partyTotalVotes[tempID]) / static_cast<double>(votersNum)) * 100 << "%" << endl;
		cout << "   Candidate: " << parties[tempID]->getCandidate()->getName() << endl;
		parties[tempID]->printElectors(resultCheck[tempID]); // Print the chosen electors
	}

	/// Free memory:
	for (int i = 0; i < partiesCounter; i++)
	{
		delete[] partyResaultArr[i];
	}
	delete[] partyResaultArr;
}

// Copy the electors of each party to the district according to the results
bool Sim_Election::electorsFromPartyToDistrict()
{
	int index = 0;
	Citizen** citizens = nullptr;
	int counter = 0;
	int limit = districts[0]->getElectorsNum();
	DynamicArray<int>  electorsPerParty;

	electorsPerParty = districts[0]->getElectorsPerParty(); // Get the array of electors giving

	for (int i = 0; i < partiesCounter; i++)
	{
		citizens = parties[i]->electorsToParty(1, electorsPerParty[i]); // Return X electors    |    X=electorsPerParty[i]
		if (citizens != nullptr)
		{
			for (int j = 0; j < electorsPerParty[i]; j++)
			{
				if (counter < limit)
				{

					districts[0]->addElector(citizens[j]);
				}
				counter++;
			}
			delete[] citizens;
			citizens = nullptr;
		}
	}

	return true;
}

// Save type of election
void Sim_Election::saveTypeElection(ofstream& out_file)
{
	eType type = SIMPLE;
	int electors = districts[0]->get_electors();
	out_file.write((char*)&type, sizeof(eType));
	out_file.write((char*)&year, sizeof(int));
	out_file.write((char*)&month, sizeof(int));
	out_file.write((char*)&day, sizeof(int));
	out_file.write((char*)&electors, sizeof(int));
}