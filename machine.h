/***********************************************************
* Author:					Leander Rodriguez
* Date Created:				02/10/14
* Last Modification Date:	02/16/14
* Lab Number:				CST 229 Lab 1
* Filename:					machine.h
*
************************************************************/

#ifndef  MACHINE_H
#define  MACHINE_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

/************************************************************************
* Class: cDFA
*
* Constructors:	
*	cDFA() 
*		Reads in file name, opens file, stores file data, calls Machine(),
*		and displays Machine()'s results.
*
* Mutators:
*	bool Machine()
*		Determines if the user input is an acceptable string and returns
*		if it is acceptable  or not acceptable.
*
* Methods:		
*	const void ParseLine() const;
*		This method parses lines read in from input file and stores the
*		parsed values.
*
*************************************************************************/

class cDFA
{
public:

	// Default Constructor
	cDFA(const string &docFileName);

	// Determines whether the user input is an acceptable string
	bool Machine(const string& input);

private:

	string	m_startState,	// machine starting state
			m_currentState;	// current state of machine

	vector<string>	m_states,		// holds all machine states
					m_language,		// holds the acceptable alphabet letters
					m_finalState;	// holds all final machine states

	map<string, map<string, string>> m_transitions;	// holds the machine states and transition functions

	// Parses line from file and stores it
	const void ParseLine(vector<string>& currentV, const string& line) const;
};


#endif