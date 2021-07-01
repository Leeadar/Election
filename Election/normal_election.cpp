#include "normal_election_header.h"

Nor_Election::Nor_Election(int day, int month, int year) : Election(day, month, year)
{
	// Same as election
}

Nor_Election::~Nor_Election()
{
	// Same as election
}

/* Adds the electors to each district according to the results,
   Prints the resauls to each district,
   Caculate the general results,
   And then print them */
void Nor_Election::result()
{
	if (partiesCounter == 0 || districtsCounter == 0 || citizensCounter == 0) // if there is no parties
	{
		throw invalid_argument("Error - Election Is Not Valid !");
	}

	int districtNotValid = 0; // How many distircts dosnt have result
	int unitedWinner; // The winning is party id in each district
	DynamicArray<int> divResult;
	DynamicArray<int> resultCheck(partiesCounter); // Counts total electors to each party
	DynamicArray<int> partyTotalVotes(partiesCounter); // Counts total votes to each party
	
	//int* partyTotalVotes = new int[partiesCounter]; // Counts total votes to each party

	partySort** partyResaultArr = nullptr;
	partySort* tempParty = nullptr;

	for (int i = 0; i < partiesCounter; i++) // initiate the arrays
	{
		resultCheck.push_back(0);
		partyTotalVotes.push_back(0);
	}

	for (int i = 0; i < districtsCounter; i++)// For each district
	{
		/// Print district details:
		cout << endl << "District " << districts[i]->getName() << " :" << endl;
		districts[i]->howManyElectorsFromEachParty(); // Caculate how to give the electors

		/// Caculate the results for each party and sort the parties into a new arr:
		if (isEnoughElectors(districts[i]->getDistrictId()) && (districts[i]->getVotersCounter() > 0)) // if there is enough electors in the district
		{
			cout << "Electors: " << districts[i]->getElectorsNum() << "." << endl;
			if (typeid(*districts[i]) == typeid(Uni_District))
			{
				unitedWinner = dynamic_cast<Uni_District*>(districts[i])->resultsCheck(); // The winning party 
				cout << "District associated with: " << parties[unitedWinner]->getCandidate()->getName() << "." << endl;
				parties[unitedWinner]->setElectorsWonCounter(districts[i]->getElectorsNum()); // Adding the amount of district electors to party
				resultCheck[unitedWinner] += districts[i]->getElectorsNum(); // Add the result to the general count
				dynamic_cast<Uni_District*>(districts[i])->printResults(); // prinf result
			}
			else if (typeid(*districts[i]) == typeid(Div_District))
			{
				divResult = dynamic_cast<Div_District*>(districts[i])->resultsCheck(); // How many electors to each party
				partyResaultArr = sortParties(divResult); // Sort the given electors to each party
				for (int i = 0; i < partiesCounter; i++)
				{
					parties[i]->setElectorsWonCounter(divResult[i]);
					resultCheck[i] += divResult[i];
				}
				dynamic_cast<Div_District*>(districts[i])->printResault(partyResaultArr, parties); // print result
				delete[] partyResaultArr;
			}
			/// For both type of districts - adds the result to the general result
			electorsFromPartyToDistrict(districts[i]->getDistrictId()); // Add the electors to the district
			for (int j = 0; j < partiesCounter; j++)
			{
				partyTotalVotes[j] += districts[i]->getPartyVotes(j);
			}
		}
		else
		{
			cout << "District results are not valid !" << endl;
			districtNotValid++;
		}
	}

	if (districtNotValid == districtsCounter) // All districts dont have resault
	{
		throw invalid_argument("Error - Election Is Not Valid !");
	}

	/// Sort the results:
	partyResaultArr = sortParties(resultCheck);

	/// Print finale resaults:
	cout << endl << "~~~~~~~~   The Elections Results   ~~~~~~~~" << endl << endl;
	for (int j = 0; j < partiesCounter; j++)
	{
		cout << j + 1 << ". Party: " << parties[partyResaultArr[j]->partyId]->getPartyName() << ", Electors:" << resultCheck[partyResaultArr[j]->partyId] << ", Total votes:" << partyTotalVotes[partyResaultArr[j]->partyId] << "." << endl;
		cout << "   Candidate:" << parties[partyResaultArr[j]->partyId]->getCandidate()->getName() << endl << endl;
	}

	/// Free memory:
	for (int i = 0; i < partiesCounter; i++)
	{
		delete[] partyResaultArr[i];
	}
	delete[] partyResaultArr;
}

// Copy the electors of each party to the correct district according to the results in the district
bool Nor_Election::electorsFromPartyToDistrict(int districtID)
{
	int index = 0;
	Citizen** citizens = nullptr;
	int counter = 0;
	int limit = districts[districtID - 1]->getElectorsNum();
	DynamicArray<int> electorsPerParty;

	electorsPerParty = districts[districtID - 1]->getElectorsPerParty(); // Get the array of electors giving

	cout <<endl<< "Elector List:" << endl;
	for (int i = 0; i < partiesCounter; i++)
	{
		citizens = parties[i]->electorsToParty(districtID, electorsPerParty[i]); // Return X electors from ditrict Y    |    X=electorsPerParty[i] ; Y=districtID
		if (citizens != nullptr)
		{
			for (int j = 0; j < electorsPerParty[i]; j++)
			{
				if (counter < limit)
				{
					if (j==0)
					{
						cout <<" From party " << parties[i]->getPartyName() << ":" << endl;
					}
					districts[districtID - 1]->addElector(citizens[j]);
					cout << " - "<<*citizens[j] << endl; // print elector
				}
				counter++;
			}
			delete[] citizens;
			citizens = nullptr;
		}
	}
	cout << endl;
	return true;
}

void Nor_Election::saveTypeElection(ofstream& out_file)
{
	eType type = NORMAL;
	out_file.write((char*)&type, sizeof(eType));
	out_file.write((char*)&year, sizeof(int));
	out_file.write((char*)&month, sizeof(int));
	out_file.write((char*)&day, sizeof(int));
}