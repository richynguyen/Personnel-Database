// HW3.1.cpp : Defines the entry point for the console application.
// Worked with mentors
// Worked with classmate Jose Juarez

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>
#include <ratio>
//#include "ArgumentManager.h"
using namespace std;

#define MAX 10					// define MAX to int 10, for use in data array
int nodeCounter = 0;			// global declaration of nodeCounter
int indexCounter = 0;

enum Instructions 
{
	// dataArray Index guide
	// [0] = id
	// [1] = firstName
	// [2] = lastName
	// [3] = DOB, MONTH
	// [4] = DOB, DAY
	// [5] = DOB, YEAR
	// [6] = yearsWorked
	// [7] = salary
	// [8] = position
};

// node (person)
// -------------------------------------------------------------------------------------V
struct node 
{
	std::string id;
	std::string firstName;
	std::string lastName;
	std::string DOB_month;
	std::string DOB_day;
	std::string DOB_year;
	int yearsWorked;
	int salary;
	std::string position;
	int index;
	node *next;
};

// adding/updating indexes for linked list
//-------------------------------------------------------------------------------------V
void updateIndexes(node *head)
{
	node *current;
	current = head;
	int i = 0;
	while (current != NULL)
	{
		current->index = i;
		current = current->next;
		i++;
	}
}

// assigns all data to temp node
// -------------------------------------------------------------------------------------V
void assignData(string dataArray[], node *temp)
{
	temp->id = dataArray[0];
	temp->firstName = dataArray[1];
	temp->lastName = dataArray[2];
	temp->DOB_month = dataArray[3]; // +" " + dataArray[4] + " " + dataArray[5];
	temp->DOB_day = dataArray[4];
	temp->DOB_year = dataArray[5];
	temp->yearsWorked = stoi(dataArray[6]);
	temp->salary = stoi(dataArray[7]);
	temp->position = dataArray[8];
	temp->index = indexCounter;
	indexCounter++;
};

// print test node data
// -------------------------------------------------------------------------------------V
void printTest(node *temp)
{
	std::cout << "ID: " << temp->id << endl;
	std::cout << "firstName: " << temp->firstName << endl;
	std::cout << "lastName: " << temp->lastName << endl;
	std::cout << "DOB: " << temp->DOB_month << " " << temp->DOB_day << " " << temp->DOB_year <<  endl;
	std::cout << "yearsWorked: " << temp->yearsWorked << endl;
	std::cout << "salary: " << temp->salary << endl;
	std::cout << "position: " << temp->position << endl;
	std::cout << endl;
}

// print linked list
// -------------------------------------------------------------------------------------V
void printLL(node *current, node *head, ofstream &outputfile, int &printCounter, 
	int &commandCounter, int &cheat)
{
	
	current = head;
	while (current != NULL)
	{
		outputfile << current->id << " " << current->firstName << " " << current->lastName
			<< " " << current->DOB_month << " " << current->DOB_day << " " << current->DOB_year
			<< " " << current->yearsWorked << " " << current->salary
			<< " " << current->position; // << endl;
		//std::cout << current->index << endl;
		if (current != NULL)// && (cheat <= commandCounter+1))		// this needs to compare something diff
		{
			outputfile << endl;
		}
		current = current->next;
	}
	//std::cout << endl;
	/*cout << "print here: " << printCounter << endl;
	cout << "command here: " << commandCounter << endl;*/
	if (printCounter < commandCounter)		// this works
	{
		//cout << "does this work" << endl;
		outputfile << endl;
	}
	printCounter++;
}

 // add at index 0, add at beginning
 //-------------------------------------------------------------------------------------V
void addNodes(int &toggleCounter, node *&head, node *&temp, node *&fakehead, node *&current)
{
	//current = head, declared before function called in main
	
	if (toggleCounter == 0)			// toggleCounter to trick into adding a head node
	{
		/*head = temp;
		head->next = current;*/

		head = temp;
		head->next = current;
		fakehead = head;
		toggleCounter++;
	}
	else
	{
		/*current = current->next;
		head->next = temp;
		temp->next = current;*/

		current = fakehead;
		current = current->next;
		fakehead->next = temp;
		temp->next = current;
		fakehead = temp;
	}
}

// add before certain index > 0
//-------------------------------------------------------------------------------------V
void addnodebeforeIndex(node *&head, node *&temp, int addIndex)
{
	node *current = head;
	node *trailing = head;

	while (current->index != addIndex)		// transverse the list until value is found
	{
		trailing = current;
		current = current->next;
	}
	trailing->next = temp;
	temp->next = current;
	trailing = temp;
}

// add after certain index > 0
//-------------------------------------------------------------------------------------V
void addnodeafterIndex(node *&head, node *&temp, int addIndex)
{
	node *current = head;
	node *trailing = head;

	while (current->index != addIndex)		// transverse the list to find index
	{
		trailing = current;
		current = current->next;
	}

	if (current->next != NULL)		// if not the last node in the list
	{
		trailing = current;
		current = current->next;
		trailing->next = temp;
		temp->next = current;
		trailing = temp;
		//cout << current->firstName << endl;
	}
	else //(current->next == NULL)		// if the last node in the list
	{
		trailing = current;
		current = temp;
		trailing->next = current;
		current->next = nullptr;
	}
}

// add at end
//-------------------------------------------------------------------------------------V
void addEnd(node *&head, node *&temp, node *&current)
{
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = temp;
	current = temp;
	current->next = nullptr;
}

// delete ID
//-------------------------------------------------------------------------------------V
void deleteIDNode(node *&head, string deleteID)
{
	node *current = head;
	node *temp;
	node *temphead;
	node *trailing = head;

	while (current != NULL)
	{
		if (current->id == deleteID)
		{
			trailing->next = current->next;
			if (current == head)		// if deleteID is head
			{
				head = current->next;
			}
			delete(current);
			return;
		}
		trailing = current;
		current = current->next;
	}
}

// delete generic node - for deleting index to index
//-------------------------------------------------------------------------------------V
void deleteNode(node *&head, node *&delNode)		// need to pass the pointer by refrence
{													// and change the pointer after that
	node *current = head;
	node *temp;
	node *temphead;
	node *trailing = head;

	while (current != NULL)
	{
		if (current == delNode)
		{
			trailing->next = current->next;
			if (current = head)
			{
				head = current->next;
			}
			delete (current);
			updateIndexes(head);
			current = head;
			return;
		}
		else
		{
			trailing = current;
			current = current->next;
		}
	}
}

// for delete index to index, overloaded delete
//-------------------------------------------------------------------------------------V
node* deleteNode3rdCase(node *&head, node *&delNode) 
{ 
	
	node * current = head; 
	node * temp;
	node *tempHead;
	node *previous = head;
	while (current != nullptr)
	{
		if (current == delNode)
		{
			previous->next = current->next;
			if (current == head) head = current->next;
			delete current;
			nodeCounter--;
			updateIndexes(head);
			current = head;
			return previous;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

// delete index to index
//-------------------------------------------------------------------------------------V
void deleteIndextoIndex(int index1, int index2, node *&head)
{
	node *current = head;
	int i = 0;
	int j = index1;
	while (current != nullptr && i < index1)
	{
		current = current->next;
		i++;
	}
	while (current != nullptr && j <= index2)
	{
		if (current == head)
		{
			deleteNode(head, current);
			current = head;
			j++;
		}
		else if (current == head->next)
		{
			deleteNode(head, current);
			current = head->next;
			j++;
		}
		else
		{
			current = deleteNode3rdCase(head, current);
			current = current->next;
			j++;
		}
	}
}


// delete at beginning
//-------------------------------------------------------------------------------------V
void deleteAtBeginning(node *&head)
{
	node *current = head;

	// case 1: list is empty
	if (head == nullptr)
	{
		std::cout << "Empty list" << endl;
	}
	else
	{
		// case 2: list has only one node
		if (current->next == nullptr)
		{
			delete(current);
			current = nullptr;
			head = nullptr;
		}
		else
		{
			head = head->next;
			delete(current);
			current = head;
		}
	}
}

// delete at end
//-------------------------------------------------------------------------------------V
void deleteAtEnd(node *&head)
{
	node *current = head;
	node *trailing = head;

	if (head == nullptr)		// if empty list
	{
		return;
	}
	while (current != nullptr)		// transverse the list
	{
		if (current->next == nullptr)		// reaches the end
		{
			delete(current);
			trailing->next = nullptr;
			break;
		}
		else		// if not the last, then transverse the list
		{
			trailing = current;
			current = current->next;
		}
	}
}

// deleting duplicates, from geeksforgeeks
//-------------------------------------------------------------------------------------V
/* Function to remove duplicates from a
unsorted linked list */
void removeDuplicates(node *head)
{
	node *ptr1 = head;
	node *ptr2;
	node *duplicate;

	/* Pick elements one by one */
	while (ptr1 != NULL && ptr1->next != NULL)
	{
		ptr2 = ptr1;

		/* Compare the picked element with rest
		of the elements */
		while (ptr2->next != NULL)
		{
			/* If duplicate then delete it */
			if (ptr1->id == ptr2->next->id)
			{
				/* sequence of steps is important here */
				duplicate = ptr2->next;
				ptr2->next = ptr2->next->next;
				delete(duplicate);
			}
			else /* This is tricky */
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

// copy linked list function
//-------------------------------------------------------------------------------------V
void copyLL(node *&head, node *&headCopy, int &toggleCounterCopy)
{
	node *current = head;
	node *currentCopy = headCopy;

	while (current != NULL)
	{
		node *tempCopy = new node;

		if (toggleCounterCopy == 0)
		{
			//std::cout << "toggleCounterCopy == 0" << endl;
			toggleCounterCopy++;
			tempCopy->next = nullptr;
			headCopy = tempCopy;
			currentCopy = headCopy;

			currentCopy->id = current->id;
			currentCopy->firstName = current->firstName;
			currentCopy->lastName = current->lastName;
			currentCopy->DOB_month = current->DOB_month;
			currentCopy->DOB_day = current->DOB_day;
			currentCopy->DOB_year = current->DOB_year;
			currentCopy->yearsWorked = current->yearsWorked;
			currentCopy->salary = current->salary;
			currentCopy->position = current->position;
			currentCopy->index = current->index;

			/*cout << currentCopy->id << " " << currentCopy->firstName << " "
			<< currentCopy->lastName << " " << currentCopy->DOB << " "
			<< currentCopy->yearsWorked << " " << currentCopy->salary << " "
			<< currentCopy->position << endl;
			cout << currentCopy->index << endl;*/
		}
		else
		{
			tempCopy->next = nullptr;
			currentCopy->next = tempCopy;
			currentCopy = currentCopy->next;

			currentCopy->id = current->id;
			currentCopy->firstName = current->firstName;
			currentCopy->lastName = current->lastName;
			currentCopy->DOB_month = current->DOB_month;
			currentCopy->DOB_day = current->DOB_day;
			currentCopy->DOB_year = current->DOB_year;
			currentCopy->yearsWorked = current->yearsWorked;
			currentCopy->salary = current->salary;
			currentCopy->position = current->position;
			currentCopy->index = current->index;

			/*cout << currentCopy->id << " " << currentCopy->firstName << " "
				<< currentCopy->lastName << " " << currentCopy->DOB << " "
				<< currentCopy->yearsWorked << " " << currentCopy->salary << " "
				<< currentCopy->position << endl;
			cout << currentCopy->index << endl;*/
		}
		current = current->next;
	}
	//std::cout << endl;
}

// print copied list
//-------------------------------------------------------------------------------------V
void printLLcopy(node *&headCopy, ofstream &outputfile)
{
	node *currentCopy = headCopy;

	while (currentCopy != NULL)
	{
		outputfile << currentCopy->id << " " << currentCopy->firstName << " "
			<< currentCopy->lastName << " " << currentCopy->DOB_month << " "
			<< currentCopy->DOB_day << " " << currentCopy->DOB_year
			<< currentCopy->yearsWorked << " " << currentCopy->salary << " "
			<< currentCopy->position << endl;
		//std::cout << currentCopy->index << endl;
		currentCopy = currentCopy->next;
	}
	//outputfile << endl;
}

// convert linked list to array
//-------------------------------------------------------------------------------------V
void convertLLtoArray(node *head, node arr[2000], int &indexArrayCounter) {

	node *current = head;
	int i = 0;
	
	while (current != nullptr)
	{
		arr[i].id = current->id;
		arr[i].firstName = current->firstName;
		arr[i].lastName = current->lastName;
		arr[i].DOB_month = current->DOB_month;
		arr[i].DOB_day = current->DOB_day;
		arr[i].DOB_year = current->DOB_year;
		arr[i].yearsWorked = current->yearsWorked;
		arr[i].salary = current->salary;
		arr[i].position = current->position;

		////std::cout << "convert LL to array" << endl;
		//std::cout << arr[i].id << " ";
		//std::cout << arr[i].firstName << " ";
		//std::cout << arr[i].lastName << " ";
		//std::cout << arr[i].DOB << " ";
		//std::cout << arr[i].yearsWorked << " ";
		//std::cout << arr[i].salary << " ";
		//std::cout << arr[i].position << " ";
		//std::cout << endl;
	
		current = current->next;
		i++;
		indexArrayCounter++;
	}
}

// convert array to linked list
//-------------------------------------------------------------------------------------V
void convertArraytoLL(node *head, node arr[2000], int &indexArrayCounter)
{
	node *current = head;

	for (int i = 0; i < indexArrayCounter; i++)
	{
		current->id = arr[i].id;
		current->firstName = arr[i].firstName;
		current->lastName = arr[i].lastName;
		current->DOB_month = arr[i].DOB_month;
		current->DOB_day = arr[i].DOB_day;
		current->DOB_year = arr[i].DOB_year;
		current->yearsWorked = arr[i].yearsWorked;
		current->salary = arr[i].salary;
		current->position = arr[i].position;
		current = current->next;
	}
}

// quicksort, geeksforgeeks
//-------------------------------------------------------------------------------------V
// A utility function to swap two elements 
void swap(node *a, node *b)
{
	node t = *a;
	*a = *b;
	*b = t;
}

// IS GOOD
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(node arr[], int low, int high, string instruction)
{
	//student *cur = head;
	node pivot = arr[high];		// pivot 
	int i = (low - 1);			// Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or equal to pivot 
		if ((instruction == "sort id" && arr[j].id <= pivot.id) || 
			(instruction == "sort first" && arr[j].firstName <= pivot.firstName) ||
			(instruction == "sort last" && arr[j].lastName <= pivot.lastName) || 
			(instruction == "sort DOB" && arr[j].DOB_year <= pivot.DOB_year) ||
			(instruction == "sort years worked" && arr[j].yearsWorked <= pivot.yearsWorked) ||
			(instruction == "sort salary" && arr[j].salary <= pivot.salary) ||
			(instruction == "sort position" && arr[j].position <= pivot.position))
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

// IS GOOD
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low  --> Starting index,
high  --> Ending index */
void quickSort(node arr[], int low, int high, string instruction)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high, instruction);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1, instruction);
		quickSort(arr, pi + 1, high, instruction);
	}
}

// print array test
//-------------------------------------------------------------------------------------V
void printArray(node arr[2000], int indexArrayCounter, ofstream &outputfile) {
	int nodeCheat = 0;
	for (int i = 0; i < indexArrayCounter; i++) {
		std::cout << arr[i].id << " " << arr[i].firstName << " "
			<< arr[i].lastName << " " << arr[i].DOB_month << " " 
			<< arr[i].DOB_day << " " << arr[i].DOB_year << " " 
			<< arr[i].yearsWorked << " " << arr[i].salary << " " 
			<< arr[i].position << endl;

		/*if (i < nodeCounter - 1) {
		outputfile << std::endl;
		}*/
	}
	//outputfile.close();
}

// bubble sort for same position, sort id
//-------------------------------------------------------------------------------------V
void bubbleID(node arr[2000], int indexArrayCounter)
{
	for (int i = 0; i < indexArrayCounter; i++) {
		for (int j = 0; j < indexArrayCounter - i - 1; j++) {
			if (arr[j].position == arr[j + 1].position) {
				//cout << "SAME" << endl;
				if (arr[j].id > arr[j + 1].id) {
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

// bubble sort for same salary, sort id
//-------------------------------------------------------------------------------------V
void bubbleSalary(node arr[2000], int indexArrayCounter)
{
	for (int i = 0; i < indexArrayCounter; i++) {
		for (int j = 0; j < indexArrayCounter - i - 1; j++) {
			if (arr[j].salary == arr[j + 1].salary) {
				//cout << "SAME" << endl;
				if (arr[j].id > arr[j + 1].id) {
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

// bubble sort for same years worked, sort id
//-------------------------------------------------------------------------------------V
void bubbleYearsWorked(node arr[2000], int indexArrayCounter)
{
	for (int i = 0; i < indexArrayCounter; i++) {
		for (int j = 0; j < indexArrayCounter - i - 1; j++) {
			if (arr[j].yearsWorked == arr[j + 1].yearsWorked) {
				//cout << "SAME" << endl;
				if (arr[j].id > arr[j + 1].id) {
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

// bubble sort for same DOB, sort id
//-------------------------------------------------------------------------------------V
void bubbleDOB(node arr[2000], int indexArrayCounter)
{
	for (int i = 0; i < indexArrayCounter; i++) {
		for (int j = 0; j < indexArrayCounter - i - 1; j++) {
			if (arr[j].DOB_year == arr[j + 1].DOB_year) {
				//cout << "SAME" << endl;
				if (arr[j].DOB_month > arr[j + 1].DOB_month) {
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

void bubbleMonth(node arr[2000], int indexArrayCounter)
{
	for (int i = 0; i < indexArrayCounter; i++) {
		for (int j = 0; j < indexArrayCounter - i - 1; j++) {
			if ((arr[j].DOB_year == arr[j + 1].DOB_year) &&
				(arr[j].DOB_month == arr[j + 1].DOB_month)) {
				if (arr[j].DOB_day > arr[j + 1].DOB_day) {
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

// bubble sort for same last name, sort id
//-------------------------------------------------------------------------------------V
void bubbleLastName(node arr[2000], int indexArrayCounter)
{
	for (int i = 0; i < indexArrayCounter; i++) {
		for (int j = 0; j < indexArrayCounter - i - 1; j++) {
			if (arr[j].lastName == arr[j + 1].lastName) {
				//cout << "SAME" << endl;
				if (arr[j].id > arr[j + 1].id) {
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

// bubble sort for same first name, sort id
//-------------------------------------------------------------------------------------V
void bubbleFirstName(node arr[2000], int indexArrayCounter)
{
	for (int i = 0; i < indexArrayCounter; i++) {
		for (int j = 0; j < indexArrayCounter - i - 1; j++) {
			if (arr[j].firstName == arr[j + 1].firstName) {
				//cout << "SAME" << endl;
				if (arr[j].id > arr[j + 1].id) {
					swap(&arr[j], &arr[j + 1]);
				}
			}
		}
	}
}

// MAIN()
//-------------------------------------------------------------------------------------V
int main(int argc, char* argv[])
{
	/*if (argc < 2) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << std::endl;
		return -1;
	}

	ArgumentManager am(argc, argv);
	std::string infilename1 = am.get("sort input");
	std::string infilename2 = am.get("sort");
	std::string outfilename = am.get("output");
	std::cout << "File name for sort input: " << infilename1 << std::endl
		<< "File name for output: " << outfilename << std::endl
		<< "File name for command: " << infilename2 << std::endl;

	ofstream outputfile(outfilename);
	ifstream inputfile1(infilename1);
	ifstream inputfile2(infilename2);*/

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	std::string infilename1 = "input14.txt";		// input file
	std::string infilename2 = "command14.txt";		// command file
	std::string outfilename = "output1.txt";		// output file
	std::ifstream inputfile1(infilename1);
	std::ifstream inputfile2(infilename2);
	std::ofstream outputfile(outfilename);

	std::string dataArray[MAX];				// array to store inputfile1 strings after stringstream
	std::string commandArray[MAX] = {""};	// array to store command strings after stringstream
	std::string str1;						// to store each line from inputfile
	std::string str2;						// for stringstream of inputfile
	std::string str3;						// to store each line from command file
	std::string str4;						// for stringstream of command file
	std::string deleteID;					// ID to be deleted
	std::string strCopy;					// string copy for add toggle
	std::string strCopy2;					// string copy for add toggle stringstream
	std::string instruction;				// sort command
	int deleteIndex1;						// delete from this index
	int deleteIndex2;						// to this index
	int addIndex;							// add before or after this index
	node arr[2000];							// array to sort
	node *head = nullptr;					// head pointer
	node *headCopy = nullptr;				// head pointer for copy of original list
	node *fakehead = nullptr;				// for use in adding nodes and to prevent changing head
	node *trailing = nullptr;				// trailing pointer
	node *current = nullptr;				// current pointer
	node *currentCopy = nullptr;			// current pointer for copy of original list
	int inputfile1lineCounter = 0;			// line counter for inputfile1
	int inputfile2lineCounter = 0;			// line counter for inputfile2 (command file)
	int k = 0;								// index for dataArray
	int l = 0;								// index for commandArray
	int commandIndex = 0;					// for forloop of commandArray
	bool addbeforeIndexZero = false;		// bool for "add before 0"
	bool addbeforeIndex = false;			// bool for "add before index ' '
	bool addafterIndex = false;				// bool for "add after index"
	bool addatBeginning = false;			// bool for "add at beginning"
	bool addatEnd = false;					// bool for "add at end"
	bool isNumber = false;					// bool to find if first string are numbers
	int toggleCounter = 0;					// counter for add toggle
	int toggleCounterCopy = 0;				// counter for copy function
	int indexArrayCounter = 0;				// for bubble sorts and arrays
	int commandCounter = 0;					// for printing LL
	int printCounter = 1;					// for printing LL
	int cheat = 1;							// for printing LL

	// inputfile code here
	if (inputfile1.is_open()) 
	{
		//std::cout << "inputfile1 opened" << endl;
		nodeCounter = -1;						// intialize nodeCounter to -1

		while (getline(inputfile1, str1))
		{
			inputfile1lineCounter++;			// increment inputfile1 line counter
			node *temp = new node;				// create new temp node

			if (str1.length() != 0)				// only run if not a blank line
			{
				std::stringstream ss(str1);
				while (ss >> str2)
				{
					dataArray[k] = str2;		// input str2 into dataArray
					k++;
				}
				k = 0;

				assignData(dataArray, temp);	// assign all data to temp node
				//printTest(temp);

				// reset dataArray
				for (int i = 0; i < 9; i++)
				{
					dataArray[i] = "";
				}
			}

			nodeCounter++;

			if (str1.length() != 0)				// only run if not a blank line
			{ 
				if (nodeCounter == 0)			// only run if empty list
				{
					//cout << "inside head node code" << endl;
					nodeCounter++;
					temp->next = nullptr;
					head = temp;
					current = head;
				}
				else
				{
					temp->next = nullptr;
					current->next = temp;
					current = current->next;
				
					if (inputfile1.eof())
					{
						current = head;
					}
				}
			}
		}
	}

	removeDuplicates(head);		// remove duplicates from input file linked list
	//cout << "copy of original list after removing dups" << endl;
	copyLL(head, headCopy, toggleCounterCopy);
	//std::cout << "print test after copy" << endl;
	//printLL(current, head);
	//std::cout << endl;

	// only to get number of command lines
	if (inputfile2.is_open())
	{
		while (getline(inputfile2, str3))
		{
			inputfile2lineCounter++;
			strCopy = str3;

			if (str3.length() != 0)
			{
				std::stringstream ss(str3);
				while (ss >> str4)
				{
					commandArray[l] = str4;
					l++;
				}
				l = 0;

				//-------------------------------------------------------------------------------------V
				// finds command "output original"
				if (commandArray[0] == "output" && commandArray[1] == "original")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort id"
				if (commandArray[0] == "sort" && commandArray[1] == "id")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort first name"
				if (commandArray[0] == "sort" && commandArray[1] == "first") // && commandArray[2] == "name")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort last name"
				if (commandArray[0] == "sort" && commandArray[1] == "last") // && commandArray[2] == "name")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort DOB"
				if (commandArray[0] == "sort" && commandArray[1] == "DOB")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort years worked"
				if (commandArray[0] == "sort" && commandArray[1] == "years" && commandArray[2] == "worked")
				{
					commandCounter++;
					//cheat++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort salary"
				if (commandArray[0] == "sort" && commandArray[1] == "salary")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort position"
				if (commandArray[0] == "sort" && commandArray[1] == "position")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add at beginning"
				if (commandArray[0] == "add" && commandArray[1] == "at" && commandArray[2] == "beginning")
				{
					commandCounter++;
					cheat++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add before index"
				if (commandArray[0] == "add" && commandArray[1] == "before")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add after index"
				if (commandArray[0] == "add" && commandArray[1] == "after")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add at end"
				if (commandArray[0] == "add" && commandArray[1] == "at" && commandArray[2] == "end")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete ID"
				if (commandArray[0] == "delete" && commandArray[2] != "to" && commandArray[2] != "beginning"
					&& commandArray[2] != "end")
				{
					commandCounter++;
					cheat++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete index to index"
				if (commandArray[0] == "delete" && commandArray[2] == "to")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete at beginning"
				if (commandArray[0] == "delete" && commandArray[1] == "at" && commandArray[2] == "beginning")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete at end"
				if (commandArray[0] == "delete" && commandArray[1] == "at" && commandArray[2] == "end")
				{
					commandCounter++;
				}

				//-------------------------------------------------------------------------------------V
				// reset commandArray to empty
				for (int i = 0; i < MAX; i++)
				{
					commandArray[i] = "";
				}
			}
		}
	}
	inputfile2.close();

	// command file code here
	inputfile2.open(infilename2);
	if (inputfile2.is_open())
	{
		//std::cout << "inputfile2 opened" << endl;

		while (getline(inputfile2, str3))
		{
			inputfile2lineCounter++;
			strCopy = str3;

			if (str3.length() != 0)
			{
				std::stringstream ss(str3);
				while (ss >> str4)
				{
					commandArray[l] = str4;
					l++;
				}
				l = 0;

				//-------------------------------------------------------------------------------------V
				// finds first word is numbers
				if (commandArray[0] != "sort" && commandArray[0] != "add" &&
					commandArray[0] != "delete" && commandArray[0] != "output")
				{
					isNumber = true;
					//cout << "numbers true here: " << strCopy << endl;
				}
				if (commandArray[0] == "sort" || commandArray[0] == "add" ||
					commandArray[0] == "delete" || commandArray[0] == "output")
				{
					isNumber = false;
					//cout << "numbers false here: " << strCopy << endl;
				}

				//-------------------------------------------------------------------------------------V
				// in case add before 0
				if (addbeforeIndexZero == true && isNumber == false)
				{
					//printCounter++;
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// in case add at beginning
				if (addatBeginning == true && isNumber == false)
				{
					//printCounter++;
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// in case add at end
				if (addatEnd == true && isNumber == false)
				{
					//printCounter++;
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// in case add before index
				if (addbeforeIndex == true && isNumber == false)
				{
					//printCounter++;
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// in case add after index 
				if (addafterIndex == true && isNumber == false)
				{
					//printCounter++;
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
					//cout << "hi" << endl;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "output original"
				if (commandArray[0] == "output" && commandArray[1] == "original")
				{
					//std::cout << "found output original" << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					//printCounter++;
					printLLcopy(headCopy, outputfile);
				}
			
				//-------------------------------------------------------------------------------------V
				// finds command "sort id"
				if (commandArray[0] == "sort" && commandArray[1] == "id")
				{
					// sort id here
					//std::cout << "found sort id" << endl;
					
					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;
					
					//printCounter++;
					convertLLtoArray(head, arr, indexArrayCounter);
					quickSort(arr, 0, indexArrayCounter-1, "sort id");
					convertArraytoLL(head, arr, indexArrayCounter);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort first name"
				if (commandArray[0] == "sort" && commandArray[1] == "first") // && commandArray[2] == "name")
				{
					// sort first name here
					//std::cout << "found first name" << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					//printCounter++;
					convertLLtoArray(head, arr, indexArrayCounter);
					quickSort(arr, 0, indexArrayCounter - 1, "sort first");
					//bubbleFirstName(arr, indexArrayCounter);
					convertArraytoLL(head, arr, indexArrayCounter);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort last name"
				if (commandArray[0] == "sort" && commandArray[1] == "last") // && commandArray[2] == "name")
				{
					// sort last name here
					//std::cout << "found last name" << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					//printCounter++;
					convertLLtoArray(head, arr, indexArrayCounter);
					quickSort(arr, 0, indexArrayCounter - 1, "sort last");
					//bubbleLastName(arr, indexArrayCounter);
					convertArraytoLL(head, arr, indexArrayCounter);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort DOB"
				if (commandArray[0] == "sort" && commandArray[1] == "DOB")
				{
					// sort DOB here
					//std::cout << "found sort DOB" << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					//printCounter++;
					convertLLtoArray(head, arr, indexArrayCounter);
					quickSort(arr, 0, indexArrayCounter - 1, "sort DOB");
					bubbleDOB(arr, indexArrayCounter);
					bubbleMonth(arr, indexArrayCounter);
					convertArraytoLL(head, arr, indexArrayCounter);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort years worked"
				if (commandArray[0] == "sort" && commandArray[1] == "years" && commandArray[2] == "worked")
				{
					// sort years worked here
					//std::cout << "found sort years worked" << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					//printCounter++;
					convertLLtoArray(head, arr, indexArrayCounter);
					quickSort(arr, 0, indexArrayCounter - 1, "sort years worked");
					//bubbleYearsWorked(arr, indexArrayCounter);
					convertArraytoLL(head, arr, indexArrayCounter);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort salary"
				if (commandArray[0] == "sort" && commandArray[1] == "salary")
				{
					// sort salary here
					//std::cout << "found sort salary" << endl;
					
					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					//printCounter++;
					convertLLtoArray(head, arr, indexArrayCounter);
					quickSort(arr, 0, indexArrayCounter - 1, "sort salary");
					//bubbleSalary(arr, indexArrayCounter);
					convertArraytoLL(head, arr, indexArrayCounter);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "sort position"
				if (commandArray[0] == "sort" && commandArray[1] == "position")
				{
					// sort position here
					//std::cout << "found sort position" << endl;
					
					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					//printCounter++;
					convertLLtoArray(head, arr, indexArrayCounter);
					quickSort(arr, 0, indexArrayCounter - 1, "sort position");
					//bubbleID(arr, indexArrayCounter);
					convertArraytoLL(head, arr, indexArrayCounter);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add at beginning"
				if (commandArray[0] == "add" && commandArray[1] == "at" && commandArray[2] == "beginning")
				{
					// add at beginning here
					//std::cout << "found add at beginning" << endl;
					
					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = true;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add before index"
				if (commandArray[0] == "add" && commandArray[1] == "before") 
				{
					// add before index here
					addIndex = stoi(commandArray[2]);
					//std::cout << "found add before index - add before " << addIndex << endl;
					if (addIndex == 0)
					{
						addbeforeIndexZero = true;
						addbeforeIndex = false;
					}
					else
					{
						addbeforeIndexZero = false;
						addbeforeIndex = true;
					}

					isNumber = false;
					addatBeginning = false;
					addafterIndex = false;
					addatEnd = false;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add after index"
				if (commandArray[0] == "add" && commandArray[1] == "after")
				{
					addIndex = stoi(commandArray[2]);
					//std::cout << "found add after index - add after " << addIndex << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = true;
					addatEnd = false;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "add at end"
				if (commandArray[0] == "add" && commandArray[1] == "at" && commandArray[2] == "end")
				{
					// add at end here
					//std::cout << "found add at end" << endl;
					
					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = true;
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete ID"
				if (commandArray[0] == "delete" && commandArray[2] != "to" && commandArray[2] != "beginning"
					&& commandArray[2] != "end")
				{
					// delete ID here
					deleteID = commandArray[1];
					//std::cout << "deleteID found, delete " << deleteID << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					// delete ID function here
					//printCounter++;
					deleteIDNode(head, deleteID);
					updateIndexes(head);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete index to index"
				if (commandArray[0] == "delete" && commandArray[2] == "to") 
				{
					// delete index to index here
					deleteIndex1 = stoi(commandArray[1]);
					deleteIndex2 = stoi(commandArray[3]);
					//std::cout << "found delete index to index, delete " << deleteIndex1 << " to " 
						//<< deleteIndex2 << endl;
					
					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					// delete index to index function here
					//printCounter++;
					deleteIndextoIndex(deleteIndex1, deleteIndex2, head);
					updateIndexes(head);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete at beginning"
				if (commandArray[0] == "delete" && commandArray[1] == "at" && commandArray[2] == "beginning")
				{
					// delete at beginning here
					//std::cout << "found delete at beginning" << endl;

					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					// delete at beginning function here
					//printCounter++;
					deleteAtBeginning(head);
					updateIndexes(head);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// finds command "delete at end"
				if (commandArray[0] == "delete" && commandArray[1] == "at" && commandArray[2] == "end")
				{
					// delete at end here
					//std::cout << "found delete at end" << endl;
					
					isNumber = false;
					addbeforeIndexZero = false;
					addatBeginning = false;
					addbeforeIndex = false;
					addafterIndex = false;
					addatEnd = false;

					// delete at end function here
					//printCounter++;
					deleteAtEnd(head);
					updateIndexes(head);
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}

				//-------------------------------------------------------------------------------------V
				// if add at beginning and is number is true
				//cout << "HELLO" << endl;
				//cout << strCopy << endl;
				if (addatBeginning == true && isNumber == true)
				{
					std::stringstream ss(strCopy);
					while (ss >> strCopy2)
					{
						dataArray[l] = strCopy2;
						l++;
					}
					l = 0;

					// add at beginning function here
					current = head;
					node *temp = new node;
					assignData(dataArray, temp);
					addNodes(toggleCounter, head, temp, fakehead, current);
					removeDuplicates(head);
					updateIndexes(head);
					//toggleCounter = 0;			// reset to zero for next functions
					//printLL(current, head, outputfile);
				}
				
				//-------------------------------------------------------------------------------------V
				// if add before index 0 and is number is true
				if (addbeforeIndexZero == true && isNumber == true)
				{
					//std::cout << "ADD-BEFORE AND IS-NUMBER IS TRUE" << endl;
					//cout << strCopy << endl;

					// do something with strCopy
					std::stringstream ss(strCopy);
					while (ss >> strCopy2)
					{
						dataArray[l] = strCopy2;
						l++;
					}
					l = 0;

					// add before index 0 function here
					current = head;
					node *temp = new node;
					assignData(dataArray, temp);
					addNodes(toggleCounter, head, temp, fakehead, current);
					removeDuplicates(head);
					updateIndexes(head);
					//printLL(current, head, outputfile);
				}

				//-------------------------------------------------------------------------------------V
				// if add at before certain index and is number is true
				if (addbeforeIndex == true && isNumber == true)
				{
					// uses addIndex
					//std::cout << "hey girl hey" << endl;
					std::stringstream ss(strCopy);
					while (ss >> strCopy2)
					{
						dataArray[l] = strCopy2;
						l++;
					}
					l = 0;

					// add before index function here
					current = head;
					node *temp = new node;
					assignData(dataArray, temp);
					addnodebeforeIndex(head, temp, addIndex);
					removeDuplicates(head);
					updateIndexes(head);
					//printLL(current, head, outputfile);
				}

				//-------------------------------------------------------------------------------------V
				// if add at after certain index and is number is true
				if (addafterIndex == true && isNumber == true)
				{
					// uses addIndex
					//std::cout << "hey girl heyyyyyy" << endl;
					std::stringstream ss(strCopy);
					while (ss >> strCopy2)
					{
						dataArray[l] = strCopy2;
						l++;
					}
					l = 0;

					// add after index function here
					current = head;
					node *temp = new node;
					assignData(dataArray, temp);
					addnodeafterIndex(head, temp, addIndex);
					removeDuplicates(head);
					updateIndexes(head);
					//cout << "hi" << endl;
					//printLL(current, head, outputfile);
				}

				//-------------------------------------------------------------------------------------V
				// if add at end and is number is true
				if (addatEnd == true && isNumber == true)
				{
					//cout << "god man" << endl;
					//cout << strCopy << endl;

					std::stringstream ss(strCopy);
					while (ss >> strCopy2)
					{
						dataArray[l] = strCopy2;
						l++;
					}
					l = 0;

					// add at end function here
					current = head;
					node *temp = new node;
					assignData(dataArray, temp);
					addEnd(head, temp, current);	
					removeDuplicates(head);
					updateIndexes(head);
					//printLL(current, head);
				}

				//-------------------------------------------------------------------------------------V
				// bool test
				/*if (addbeforeIndexZero == true)
				{
					std::cout << "ADD-BEFORE INDEX BOOL IS TRUE" << endl;
				}
				if (addatBeginning == true)
				{
					std::cout << "ADD-AT-BEGINNING BOOL IS TRUE" << endl;
				}
				if (addatEnd == true)
				{
					std::cout << "ADD-AT-END BOOL IS TRUE" << endl;
				}
				if (addbeforeIndex == true)
				{
					std::cout << "ADD-BEFORE-INDEX "  << addIndex << endl;
				}
				if (addafterIndex == true)
				{
					std::cout << "ADD-AFTER-INDEX " << addIndex << endl;
				}*/

				//-------------------------------------------------------------------------------------V
				// reset commandArray to empty
				for (int i = 0; i < MAX; i++)
				{
					commandArray[i] = "";
				}

				//-------------------------------------------------------------------------------------V
				// print command
				if (inputfile2.eof() && isNumber == true)
				{
					//printCounter++;
					printLL(current, head, outputfile, printCounter, commandCounter, cheat);
				}
			}
		}
	}

	//printArray(arr, indexArrayCounter, outputfile);
	//std::cout << endl;
	//std::cout << "final linked list" << endl;
	//printLL(current, head);
	//std::cout << endl;

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
		<< " milliseconds" << std::endl;

    return 0;
}


