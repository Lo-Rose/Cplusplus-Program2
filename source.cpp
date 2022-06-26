#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;



/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void menu() { // Menu method
	int userInput = 0;
	string line;
	string itemName;
	int quantity;
	string str;
	//Display menu
	cout << "------------------Menu------------------" << endl;
	cout << "1: Produce a list of all items purchased with quantities\n2: Display how many times an item was sold\n3: Produce a histogram of sales data\n4: Exit\n\nEnter your selection as a number 1, 2, 3 or 4: " << endl;
	cout << "----------------------------------------" << endl;
	do {  
		cin >> userInput;  // Variable to store user input
		if (userInput == 1) {  // If user enters 1
			cout << "Items and quantities sold today:\n" << endl; // Ask for user to enter a number
			CallProcedure("CountAll");  // Print items and quantity sold
			menu();
		}
		else if (userInput == 2) { // If user enters 2
			cout << "Enter item name: " << endl; // Prompt for specific item and store it
			
			cin >> str; // Read input into variable
			cout << endl << "Printing Sales for " << str << ":" << endl;
			cout << str << ": " << callIntFunc("CountNumInstances", str) << endl << endl; // Call function with item input	
			menu();
		}
		else if (userInput == 3) { // If user enters 3
			// Write the appropriate counts from the input file to the output file
			cout << "Writing items with quantities sold today to a file: " << endl;
			CallProcedure("ItemWriteFile");
			
			cout << endl << endl;

			ifstream fileInput("frequency.dat");
			string item;
			int count;

			while (getline(fileInput, line)) {
				istringstream iss(line);
				
				if (!(iss >> item >> count)) {
					break;
				}
				cout << item << " " << string(count, '*') << endl;
			}
			cout << endl << endl;

			menu();
		}
		else if (userInput == 4) { // If user enters 4
			cout << "Exiting the program.." << endl; // Display message
			break; // End program
		}
		else { // If user enters any other number besides 1 2 3 or 4, display error and menu again
			cout << "\nError: Enter only number: 1, 2, 3, or 4" << endl << endl;
			cout << "1: Display a multiplication table\n2: Double a value\n3: Exit\nEnter your selection as a number 1, 2, or 3: " << endl;
		}
	} 		while (userInput > 4 || userInput < 1);
} 


int main() {
	// Call the user menu
	menu();
}