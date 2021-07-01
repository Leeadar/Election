/* --------------------------------------
	C++ Project - 3
	This project made by:
	Leead Arbetman - 206018574
	Tomer Ahimeir  - 316157205
-----------------------------------------  */

#include "election_header.h"
#include "simple_election_header.h"
#include "normal_election_header.h"
#include "dynamic_array.h"


/// Functions Decleration:
void citizenInput(Election* electionRound);
void districtInput(Election* electionRound);
void electorInput(Election* electionRound);
void partyInput(Election* electionRound);
void saveElection(Election* electionRound);
void voteInput(Election* electionRound);
int getNumber(string askFromUser);
int getBirthYear(int electionYear);
int getCitizenId();
int getDistrictType();
int getElectionType();
int getMonth();
int getDay(int month);
int getDaysInMonth(int month);
Election* loadElection();
Election* createElection();
void printMenu();
Citizen* createElector(int id, int partyId, int districtId, Election* electionRound);


/// Main:
int main(void)
{
	Election* electionRound = nullptr;
	Election* tempElection = nullptr;
	string name;
	int choise; // User input
	bool finish = false, cont = true; // Finish program
	enum firstMenu { ZERO = 0, NEW_ELECTION, LOAD_ELECTION, EXIT };
	enum secondMenu { DEFAULT = 0, ADD_DISTRICT, ADD_CITIZEN, ADD_PARTY, ADD_ELECTOR, DISPLAY_DISTRICT, DISPLAY_CITIZEN, DISPLAY_PARTY, VOTE, RESULT, FINISH, SAVE, LOAD };
	ifstream in_file; // Load file

	/// Choose create / load election:
	while (!finish)
	{
		cout << "Choose an option: " << endl << "1 - Create new election round" << endl << "2 - Load existing election" << endl << "3 - Exit" << endl;
		cin >> choise;
		switch (choise)
		{
		case NEW_ELECTION:
			finish = true;
			try
			{
				electionRound = createElection();
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what() << endl;
			}
			catch (exception & ex)
			{
				cout << ex.what() << endl <<endl;
				finish = false;
			}

			break;

		case LOAD_ELECTION:
			try
			{
				electionRound = loadElection();
				finish = true;
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what() << endl;
			}
			catch (exception & ex)
			{
				cout << endl << "Load file - " << ex.what() << endl << endl;
			}
			break;

		case EXIT:
			finish = true;
			cont = false;
			break;

		default:
			cout << endl << "Wrong input, please try again" << endl;
		}
	}
	finish = false;

	/// Election main menu:
	while (!finish && cont)
	{
		printMenu();
		cin >> choise;
		switch (choise) {
		case ADD_DISTRICT:
			if (typeid(*electionRound) == typeid(Nor_Election))
			{
				try
				{
					districtInput(electionRound);
				}
				catch (bad_alloc & ex)
				{
					cout << ex.what() << endl;
				}
				catch (exception & ex)
				{
					cout << endl << ex.what() << endl;
				}
			}
			else
			{
				cout << endl << "You cant add a district" << endl;
			}
			break;

		case ADD_CITIZEN:
			try 
			{
				citizenInput(electionRound);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what() << endl;
			}
			catch (exception& ex)
			{
				cout << endl << ex.what() << endl;
			}
			break;

		case ADD_PARTY:
			try
			{
				partyInput(electionRound);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what() << endl;
			}
			catch (exception & ex)
			{
				cout << endl << ex.what()  << endl;
			}
			break;

		case ADD_ELECTOR:
			try
			{
				electorInput(electionRound);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what() << endl;
			}
			catch (exception & ex)
			{
				cout << endl << ex.what() << endl;
			}
			break;

		case DISPLAY_DISTRICT:
			try
			{
				electionRound->printDistricts();
			}
			catch (exception & ex)
			{
				cout << endl  << ex.what()  << endl;
			}
			break;

		case DISPLAY_CITIZEN:
			try
			{
				electionRound->printCitizens();
			}
			catch (exception & ex)
			{
				cout << endl << ex.what() << endl;
			}
			break;

		case DISPLAY_PARTY:
			try
			{
				electionRound->printParties();
			}
			catch (exception & ex)
			{
				cout << endl << ex.what()  << endl;
			}
			break;

		case VOTE:
			try
			{
				voteInput(electionRound);
			}
			catch (exception & ex)
			{
				cout << endl << ex.what() << endl;
			}
			break;

		case RESULT:
			try
			{
				electionRound->printDate();
				electionRound->result();
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what() << endl;
			}
			catch (exception & ex)
			{
				cout << endl << ex.what() << endl ;
			}
			electionRound->resetVotes();
			break;

		case FINISH:
			finish = true;
			break;

		case SAVE:
			try
			{
				saveElection(electionRound);
			}
			catch (exception & ex)
			{
				cout << endl << ex.what() << endl ;
			}
			break;

		case LOAD:
			try
			{
				tempElection = loadElection(); // Load election & check if valid
				delete electionRound;
				electionRound = tempElection;
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what() << endl;
			}
			catch (exception & ex)
			{
				cout << endl << "Load file - " << ex.what() << endl << endl;
			}
			break;

		default:
			cout << "Wrong input, please try again." << endl << endl;
		}
	}
}


/// Functions Implementation:
// Prints menu
void printMenu()
{
	cout << endl << "Choose an option:" << endl;
	cout << "1. Add district" << endl;
	cout << "2. Add citizen" << endl;
	cout << "3. Add party" << endl;
	cout << "4. Add citizen as an elector" << endl;
	cout << "5. Print all districts" << endl;
	cout << "6. Print all citizens" << endl;
	cout << "7. Print all parties" << endl;
	cout << "8. Vote" << endl;
	cout << "9. Election results" << endl;
	cout << "10. Exit" << endl;
	cout << "11. Save elction round" << endl;
	cout << "12. Load elction round" << endl << endl;
}

// Get district from user
void districtInput(Election* electionRound)
{
	int electors, type;
	District* district = nullptr;
	string name;

	cout << "Enter district name: " << endl;
	cin.ignore();
	getline(cin, name);
	electors = getNumber("number of Electors");
	type = getDistrictType();
	electionRound->addDistrict(name, electors, type);
}

// Get citizen from user
void citizenInput(Election* electionRound)
{
	string name;
	int id, birthYear, districtId;
	int idExist;
	Citizen* person = nullptr;

	cout << "Enter citizen name: " << endl;
	cin.ignore();
	getline(cin, name);
	id = getCitizenId();
	birthYear = getBirthYear(electionRound->get_year());
	if (typeid(*electionRound) == typeid(Nor_Election))
	{
		districtId = getNumber("ID of the district");
	}
	else if (typeid(*electionRound) == typeid(Sim_Election))
	{
		districtId = 1;
	}
	idExist = electionRound->get_citizens().count(id);
	if (idExist == 1) // If person exists with the same id
	{
		throw invalid_argument("ERROR - There is a person with this ID");
	}
	if (districtId > electionRound->get_districtsCounter()) // Check if the district exists
	{
		throw invalid_argument("ERROR - the district does not exists");
	}
	else
	{
		electionRound->addCitizen(name, id, birthYear, districtId);
	}
}

// Get elector from user
void electorInput(Election* electionRound)
{
	Citizen* person = nullptr;
	Party* party = nullptr;
	int districtId;
	int id = getNumber("ID of the elector");
	int partyId = getNumber("ID of the party");
	if (typeid(*electionRound) == typeid(Nor_Election))
		districtId = getNumber("ID of the district");
	else
		districtId = 1;
	person = createElector(id, partyId, districtId, electionRound);
	if (person != nullptr)
	{
		party = electionRound->get_party(partyId);
		electionRound->addElector(person, party, districtId);
	}
}

// Get party from user
void partyInput(Election* electionRound)
{
	string name;
	int citizenId;
	Party* party = nullptr;
	Citizen* person = nullptr;

	cout << "Enter party name: " << endl;
	cin.ignore();
	getline(cin, name);
	citizenId = getNumber("ID of the party candidate");
	if (electionRound->get_citizens().count(citizenId) == 1)
	{
		person = electionRound->get_citizens().find(citizenId)->second;
	}
	else
	{
		throw invalid_argument("ERROR - Candidate is not valid - no citizen with that ID.");
	}
	electionRound->addParty(name, person);
}

// Get vote from user
void voteInput(Election* electionRound)
{
	int id, partyId;
	id = getNumber("ID of the voter");
	partyId = getNumber("ID of the party you want to vote to");
	electionRound->vote(id, partyId);
}

// Get save from user
void saveElection(Election* electionRound)
{
	string name;
	ofstream outFile;

	cout << "Enter file name: ";
	cin.ignore();
	getline(cin, name);
	outFile.open(name, ios::binary);
	electionRound->saveEelection(outFile);
	outFile.close();
}

// Create new election round
Election* createElection()
{
	Election* electionRound = nullptr;
	int electionType, day, month, year, electors;

	cout << endl << "Create new election: " << endl;
	year = getNumber("Year");
	month = getMonth();
	day = getDay(month);

	electionType = getElectionType(); // 1 = normal ; 2 = simple
	if (electionType == 1)
	{
		electionRound = new Nor_Election(day, month, year);
	}
	else // electionType == 2
	{
		electors = getNumber("Electors");
		electionRound = new Sim_Election(day, month, year, electors);
	}
	return electionRound;
}

// Load election round
Election* loadElection()
{
	Election* electionRound = nullptr;
	string name;
	ifstream in_file;
	Election::eType typeFromFile;
	int electors, day, month, year;
	// Create file:
	cout << "Enter file name: ";
	cin >> name;
	in_file.open(name, ios::binary);
	if (!in_file)
	{
		throw invalid_argument("Error with load file.");
	}

	in_file.read((char*)&typeFromFile, sizeof(Election::eType));
	// Load date:
	in_file.read((char*)&year, sizeof(int));
	in_file.read((char*)&month, sizeof(int));
	in_file.read((char*)&day, sizeof(int));
	// Create election:
	if (typeFromFile == Election::NORMAL)
	{
		electionRound = new Nor_Election(day, month, year);
	}
	else if (typeFromFile == Election::SIMPLE)
	{
		in_file.read((char*)&electors, sizeof(int));
		electionRound = new Sim_Election(day, month, year, electors);
	}
	else
	{
		throw invalid_argument("Error with load file.");
	}

	electionRound->loadEelection(in_file);
	in_file.close();
	return electionRound;
}

// Create Elector
Citizen* createElector(int id, int partyId, int districtId, Election* electionRound)
{
	Citizen* person = nullptr;
	if (electionRound->get_citizens().count(id) == 1)
	{
		person = electionRound->get_citizens().find(id)->second;
	}
	else 
	{
		throw invalid_argument("ERROR - No citizen with that ID.");
	}

	if (districtId > electionRound->get_districtsCounter() || districtId < 1) // Check if the district exists
	{
		throw invalid_argument("ERROR - District ID is not valid.");
	}
	else if (partyId > electionRound->get_partiesCounter() || partyId < 1) // Check if the party exists
	{
		throw invalid_argument("ERROR - Party ID is not valid.");
	}
	else
	{
		return person;
	}
}

// Get int from the user
int getNumber(string askFromUser)
{
	int num;
	cout << "Enter " << askFromUser << ": " << endl;
	cin >> num;
	if (num <= 0)
	{
		throw invalid_argument("ERROR - Non positive number.");
	}
	return num;
}

// Get month from the user
int getMonth()
{
	int month;
	month = getNumber("month");
	if (month < 1 || month > 12)
	{
		throw invalid_argument("ERROR - Month invalid.");
	}
	return month;
}

// Get day from the user
int getDay(int month)
{
	int dayInMonth = getDaysInMonth(month);
	int day = getNumber("day");
	if (day > dayInMonth)
	{
		string str = "Error - in month " + to_string(month) + " there are only " + to_string(dayInMonth) + " days!";
		throw invalid_argument(str);
	}
	return day;
}

// Get ammount day in month from the user
int getDaysInMonth(int month)
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

// Get ID from the user
int getCitizenId()
{
	string num;
	cout << "Enter citizen Id: " << endl;
	cin >> num;
	if (num.length() != 9)
	{
		throw invalid_argument("ERROR - ID needs to be with 9 digits.");
	}
	for (int i = 0; i < num.length(); i++)
	{
		if (num[i] - '0' < 0 || num[i] - '0' > 9)
		{
			throw invalid_argument("ERROR - ID needs to be a number.");
		}
	}
	return stoi(num);
}

// Get district type from the user
int getDistrictType()
{
	int num;
	cout << "Enter type of the district(1 = united | 2 = divided): " << endl;
	cin >> num;
	if (num != 1 && num != 2)
	{
		throw invalid_argument("ERROR - Invalid district type.");
	}
	return num;
}

//Get year of birth from user
int getBirthYear(int electionYear)
{
	int birthYear;
	cout << "Enter Year Of Birth: " << endl;
	cin >> birthYear;

	if (birthYear <= 0 || electionYear < birthYear)
	{
		throw invalid_argument("ERROR - Birth year is not valid.");
	}

	else if (electionYear - birthYear < 18)
	{
		throw invalid_argument("ERROR - under 18 years old can't vote.");
	}
	return birthYear;
}

// Get election type
int getElectionType()
{
	int num;
	cout << "Enter election type:" << endl << "1 - Normal" << endl << "2 - Simple" << endl;
	cin >> num;
	if (num != 1 && num != 2)
	{
		throw invalid_argument("ERROR - Invalid election type.");
	}
	return num;
}