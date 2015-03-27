/***********************************************************
* Author:					Leander Rodriguez
* Date Created:				02/10/14
* Last Modification Date:	02/16/14
* Lab Number:				CST 229 Lab 1
* Filename:					machine.cpp
*
* Overview:
*	This program will read in a description of a Deterministic 
* 	Finite Automata Machine. It then reads in a set of input 
*	strings (interactively) and determines whether or not a
*	particular string is acceptable by the machine.
*
* Input:
*	The input will consist of a list of states, a set of alpha-
* 	bet letters, a start state, a set of final state(s), and a
*	set of transition functions.  The input is read in from a 
*	text file.  The text file is in the format of:
*	0 1
*	0
*	0
*	0
*	0 0 1
*	1 0 0
*
* Output:
*	The output of this program will prompt the user for a file
*	name.  The program will then display the current state of
* 	machine and prompt the user for input. The program will then
*	output whether the string entered by the user is accepted or
*	not, while also displaying the current state of the machine
*	based on whether the string was accepted or not.  An example
*	of the output to the screen will have the form:
*
*	Enter machine file name: _
*
*	Please enter input or 'quit' to exit:
*	String accepted.
*
************************************************************/

#include  "machine.h"

/**************************************************************
* Purpose:  Reads in file name, opens file, stores file data, 
*			and calls Machine().
*                 
* Entry:	The user inputed file name
*
* Exit:		When user wants to quit program
****************************************************************/
cDFA::cDFA(const string &fileName)
{
	ifstream in(fileName);				// open file
	
	if (!in)							// check if file opened properly
	{
		cout << "*** Error opening file '"
			<< fileName
			<< "' ***"
			<< endl;

		exit(EXIT_FAILURE);
	}

	string line;						// used to hold line read-in

	getline(in, line);					// read-in line from file
	ParseLine(m_states, line);

	getline(in, line);					// read-in line from file
	ParseLine(m_language, line);		// store data in vector

	getline(in, line);					// read-in line from file
	m_startState = line;				// store data in string

	getline(in, line);					// read-in line from file
	ParseLine(m_finalState, line);		// store data in vector

	while (!in.eof())					// loop until end of file
	{
		string str;						// used to hold string read-in
		vector<string> temp;			// used to store elements of parsed string

		getline(in, line);				// read-in line from file
		ParseLine(temp, line);			// store data in vector

		m_transitions[temp[0]][temp[1]] = temp[2];  // store data in map
	}

	in.close();							// close file

	string input;						// used to hold user input

	do									// prompt user for input and print
	{									// if its acceptable

		cout << "Please enter input or 'quit' to exit: ";
		cin >> input;				

		if (input == "quit")			// break out of loop
			break;

		bool result = Machine(input);	// calls Machine() returns acceptability

		if (result)						// prints acceptability of string
		{
			cout << "String accepted.\n" << endl;
		}
		else
		{
			cout << "String not accepted. \n" << endl;
		}

	} while (input != "quit");
}

/**************************************************************
* Purpose:  To parse line read in from file and store it
*			
* Entry:	Current line being read in from file and the vector 
*			that will store the line's parsed elements
*
* Exit:		Parsed elements are stored in current vector until
*			the end of the line read-in is reached
****************************************************************/
const void cDFA::ParseLine(vector<string>& currentV, const string& line) const
{
	string str;							// used to hold stream characters
	stringstream ss(line);				// extracts characters from string
	while (ss >> str)					// loops through string stream
	{
		currentV.push_back(str);		// stores stream characters into container
	}
}

/**************************************************************
* Purpose:  Determines if the user input is an acceptable string 
*			
* Entry:	Current userInput is passed in
*
* Exit:		Upon length of user input string, returns if user input 
*			is acceptable(true), or not acceptable (false).  Prints 
*			error if user input is not in the language.
*
****************************************************************/
bool cDFA::Machine(const string& userInput)
{
	bool result = false;				// used to hold bool state
	m_currentState = m_startState;		// current machine state is set

	// loop through user input string
	for (unsigned i = 0; i < userInput.length(); i++)
	{
		string s = userInput.substr(i, 1);	// used to hold single character from user string

		// searches through machine acceptable language for user's parsed character, stores
		// iterator position
		vector<string>::iterator inputIter = find(m_language.begin(), m_language.end(), s);


		if (inputIter != m_language.end())	// checks if an iterator position was found in language
		{
			stringstream ss;				// used to hold current string stream
			string str;						// used to hold current character
			ss << userInput[i];				// retreives character from stream buffer
			ss >> str;						// extraction of character to str string

			m_currentState = m_transitions[m_currentState][str];	// machine state is set

			if (m_currentState == "")		// check machine is in a valid state
				return result;
		}
		else								// prints error returns bool state
		{
			cout << "Oops! That input is not in the language." << endl;
			return result;
		}
	}

	// checks if current state is a final machine state
	result = any_of(m_finalState.begin(), m_finalState.end(), [&](string str) {
		return (str == m_currentState);
		});

	return result;							// returns bool state/string acceptability
}

