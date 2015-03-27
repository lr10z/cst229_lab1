/***********************************************************
* Author:					Leander Rodriguez
* Date Created:				02/10/14
* Last Modification Date:	02/16/14
* Lab Number:				CST 229 Lab 1
* Filename:					main.cpp
*
************************************************************/

#include  "machine.h"
 
using  namespace  std;

int  main()
{
	string fileName;;						// file name

	cout << "Enter machine file name: ";	// prompt for and display file name
	cin  >> fileName;
	cout << endl;

	cDFA cDFA( fileName );					// cDFA object is created

	return  EXIT_SUCCESS;					// exit program

}