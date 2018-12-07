// author(s): Finnian Allen and CS122 class Gonzaga 2018
// analizes insertion selection and bubble sort algorythms
// CPSC 122

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <fstream> 
using namespace std;

const int MAXSIZE = 6000;

// searches a list, sequentially, for a certain value
// pre: list[0..listSize - 1] has been assigned values
//      target has also been assigned a value
// post: if target is found in list, then returns where
//       else returns -1
// usage: where = doLinearSearch(list, listSize, target);
int doLinearSearch(int list[], int listSize, int target, int& countOfWork);

// looks for the largest number in a list
// pre: list[0..listSize - 1] has been assigned values
// post: returns the index of the largest number in list
// usage: whereLargest = findIndexOfLargest(list, size);
int findIndexOfLargest(int list[], int listSize, int& countOfWork);

// uses the selection sort algorithm to sort a list
// pre: list[0..listSize - 1] has been assigned values
// post: list[0..listSize - 1] has values in increasing order
// usage: doSelectionSort(list, size);
void doSelectionSort(int list[], int listSize, int& countOfWork);

// swaps two values
// pre: first and second are assigned values
// post: first now has second's value and vice versa
// usage: swap(list[k], list[j]);
void swap(int& first, int& second, int& countOfWork);

// fills a list with random integers from 0 to 1045 inclusive
// pre: listSize has been assigned a value less than maximum size of list
// post: list[0..listSize - 1] have random integers from 0 to 1045 inclusive
// usage: createList(list, size);
void createList(int list[], int listSize);

// prints a list on the screen
// pre: list[0..listSize - 1] has been assigned values
// post: the values in list[0..listSize - 1] are displayed on the screen
//       right-justified in a field width of 10 after index in field width of 5
void printList(int list[], int listSize);

// prints the result of a search on a list
// pre: whereTarget and target have been assigned a value
// post: prints a message depending on whereTarget
// usage: printSearchResults(whereTarget);
void printSearchResults(int whereTarget, int target);

// prints a number of newlines
// pre: desiredNumber is assigned a nonnegative value
// post: desiredNumber of newlines are displayed on the screen
// usage: printNewLines(4);
void printNewLines(int desiredNumber);

// prints a message
// pre: theMessage is assigned
// post: theMessage is displayed on the screen and then a newline
// usage: printMessage("Hi");
void printMessage(string theMessage);

void bubbleSort(int list[], int listSize, int& countOfWork);

void insertionSort(int* list, int listSize, int& countOfWork);

int main()
{
   int list[MAXSIZE];
   int seed = time(0);
   int whereFound;
   int randomIndex;
   int countOfWork = 0;
   ofstream outfile;
   
   outfile.open("out.dat");
   
	srand(seed);
   
   printNewLines(3);
   outfile << "------------------------" << endl;
   outfile << "Selection Sort" << endl;
   for(int size = 100; size <= 6000; size += 100) {
	   
	createList(list, size);
   //printMessage("The Unsorted List of Random Numbers");
   //printNewLines(1);
   //printList(list, 10);
   
		//whereFound = doLinearSearch(list, size, 2000, countOfWork); // worst case
		//printNewLines(2);
		doSelectionSort(list, size, countOfWork);
		outfile << size << " " << countOfWork << endl;
		countOfWork = 0;
   }
   
   outfile << endl;
   outfile << "------------------------" << endl;
   outfile << "Bubble Sort" << endl;
   for(int size = 100; size <= 6000; size += 100) {
	   
   createList(list, size);
   //printMessage("The Unsorted List of Random Numbers");
   //printNewLines(1);
   //printList(list, 10);
   
		//whereFound = doLinearSearch(list, size, 2000, countOfWork); // worst case
		//printNewLines(2);
		bubbleSort(list, size, countOfWork);
		outfile << size << " " << countOfWork << endl;
		countOfWork = 0;
   }
   
   outfile << endl;
   outfile << "------------------------" << endl;
   outfile << "Insertion Sort" << endl;
   for(int size = 100; size <= 6000; size += 100) {
	   
   createList(list, size);
   //printMessage("The Unsorted List of Random Numbers");
   //printNewLines(1);
   //printList(list, 10);
   
		//whereFound = doLinearSearch(list, size, 2000, countOfWork); // worst case
		//printNewLines(2);
		insertionSort(list, size, countOfWork);
		outfile << size << " " << countOfWork << endl;
   }
   
   /*
   printNewLines(3);
   printMessage("Showing that Linear Search works");
   printNewLines(2);
   randomIndex = rand() % 10;
   whereFound = doLinearSearch(list, 10, list[randomIndex]);
   printSearchResults(whereFound, list[randomIndex]);
   printNewLines(2);
   whereFound = doLinearSearch(list, 10, 2000);
   printSearchResults(whereFound, 2000);
   
   printNewLines(3);
   printMessage("After Selection Sort, the sorted List");
   printNewLines(2);
   doSelectionSort(list, 10);
   printList(list,10);
   */
   
   printNewLines(3);

   return 0;
}

// searches a list, sequentially, for a certain value
// pre: list[0..listSize - 1] has been assigned values
//      target has also been assigned a value
// post: if target is found in list, then returns where
//       else returns -1
// usage: where = doLinearSearch(list, listSize, target);
int doLinearSearch(int list[], int listSize, int target, int& countOfWork)
{
	//worst case: target is not found in list
   int whereTarget;
   bool isFound = false; countOfWork++;
   int index = 0; countOfWork++;
   
   countOfWork++; // last < in while condition
   while (index < listSize and not isFound)
   {
	  countOfWork += 3; // <, not, and
	  countOfWork += 3; // ==, [], (D,M)
	  
      if (target == list[index])
         isFound = true;
      index++; countOfWork += 2; // A,D
   }
   countOfWork++; //if condition 
   if (isFound)
   {
      whereTarget = index - 1;
   } else {
      whereTarget = -1; countOfWork++; // worst case not found 
   }
   return whereTarget; countOfWork++; // return 
   
}

// looks for the largest number in a list
// pre: list[0..listSize - 1] has been assigned values
// post: returns the index of the largest number in list
// usage: whereLargest = findIndexOfLargest(list, size);
int findIndexOfLargest(int list[], int listSize, int& countOfWork)
{
	int indexSoFar = 0; countOfWork ++; // 1A
	countOfWork ++; // 1C last loop condition
	for (int currentIndex = 1; currentIndex < listSize; currentIndex++)
	{
		countOfWork += 3; // 1C, 1A, 1D
		if (list[currentIndex] > list[indexSoFar])
		{
			countOfWork += 5; // 2D, 2M, 1 C
			indexSoFar = currentIndex; countOfWork ++; // 1A
		}
   }
   return indexSoFar; countOfWork ++; // 1A return
}

// uses the selection sort algorithm to sort a list
// pre: list[0..listSize - 1] has been assigned values
// post: list[0..listSize - 1] has values in increasing order
// usage: doSelectionSort(list, size);
void doSelectionSort(int list[], int listSize, int& countOfWork)
{
	//
	// also 1D for list size - 1?
	//
	countOfWork += 2; // 1A, 1D
	countOfWork ++; // 1C last time loop condition
	for (int last = listSize - 1; last >= 1; last--)
	{
	  countOfWork += 4; // 1D 1B, 1A, 1C
      int largest = findIndexOfLargest(list, last + 1, countOfWork); countOfWork ++; // 1A
      swap(list[largest], list[last]); countOfWork += 4;// 2D, 2M
	}
}

// swaps two values
// pre: first and second are assigned values
// post: first now has second's value and vice versa
// usage: swap(list[k], list[j]);
void swap(int& first, int& second, int& countOfWork)
{
   int temp;

   temp = first; countOfWork ++; // 1A
   first = second; countOfWork ++; // 1A
   second = temp; countOfWork ++; // 1A
   
}

// fills a list with random integers from 0 to 1045 inclusive
// pre: listSize has been assigned a value less than maximum size of list
// post: list[0..listSize - 1] have random integers from 0 to 1045 inclusive
// usage: createList(list, size);
void createList(int list[], int listSize)
{
   for(int k = 0; k < listSize; k++)
   {
      list[k] = rand() % 4321;
   }
}


// prints a list on the screen
// pre: list[0..listSize - 1] has been assigned values
// post: the values in list[0..listSize - 1] are displayed on the screen
//     right-justified in a field width of 10 after index in field width of 5
void printList(int list[], int listSize)
{
   for (int k = 0; k < listSize; k++)
   {
      cout << right << setw(5) << k << setw(10) << list[k] << endl;
   }
}

// prints the result of a search on a list
// pre: whereTarget and target has been assigned values
// post: prints a message about target depending on whereTarget
// usage: printSearchResults(whereTarget);
void printSearchResults(int whereTarget, int target)
{
   if (whereTarget > -1)
   {
      cout << "the target: " << target << " was found at index " << whereTarget << " in the list" << endl;
   } else {
      cout << "the target: " << target << " was not found in the list" << endl;
   }
}

// prints a number of newlines
// pre: desiredNumber is assigned a nonnegative value
// post: desiredNumber of newlines are displayed on the screen
// usage: printNewLines(4);
void printNewLines(int desiredNumber)
{
   for (int k = 0; k < desiredNumber; k++)
   {
      cout << endl;
   }
}

// prints a message
// pre: theMessage is assigned
// post: theMessage is displayed on the screen and then a newline
// usage: printMessage("Hi");
void printMessage(string theMessage)
{
   cout << theMessage << endl;
}

void insertionSort(int list[], int n, int& countOfWork) { 
	
	countOfWork ++; // 1A in loop
	countOfWork ++; // 1C last time loop condition
	for ( int unsorted = 1; unsorted < n; unsorted++)
	{
		countOfWork += 3; // 1A, 1C, 1D
		// At this point, list[0..unsorted-1] is sorted.
		// Find the right position (loc) in list[0..unsorted]
		// for list[unsorted], which is the first entry in the
		// unsorted region; shift, if necessary, to make room
		int nextItem = list[unsorted]; countOfWork += 3; // 1A, 1D, 1M
		int loc = unsorted; countOfWork ++; // 1A
		/////////
		//
		/////////
		//countOfWork += 2; // 2C last time loop condition
			while ((loc > 0) && (list[loc - 1] > nextItem))
			{
				countOfWork += 6; // 2C, 1B, 2D, 1M,
				list[loc] = list[loc - 1]; countOfWork += 6;// 2M, 3D, 1A
				loc--; countOfWork += 2; // 1D, 1A
			}
	// At this point, list[loc] is where nextItem belongs
	list[loc] = nextItem; countOfWork += 3; // 1D, 1M, 1A // Insert nextItem into sorted region
	}
}

// Sorts the items in an array into ascending order.
// pre None.
// post theArray is sorted into ascending order; n is unchanged.
void bubbleSort(int list[], int n, int& countOfWork)
{
	bool sorted = false; countOfWork ++; // 1A
	int pass = 1; countOfWork ++; // 1A
	countOfWork ++; // 1C last time loop condition
	while (!sorted && (pass < n))
	{
		countOfWork += 3; // 2B, 1C
		// At this point, theArray[n+1-pass..n-1] is sorted
		// and all of its entries are > the entries in theArray[0..n-pass]
		sorted = true; countOfWork ++; // 1A
		countOfWork ++; // 1A
		countOfWork ++; // 1C last time loop condition
			for ( int index = 0; index < n - pass; index++)
			{
			countOfWork += 4; // 1A, 1C, 2D,
			// At this point, all entries in theArray[0..index-1]
			// are <= theArray[index]
			int nextIndex = index + 1; countOfWork += 2; // 1A, 1D
				if (list[index] > list[nextIndex])
				{
				countOfWork += 5; // 1C, 2D, 2M
				// Exchange entries
				swap(list[index], list[nextIndex]); countOfWork += 4; // 2D, 2M
				sorted = false; countOfWork ++; // 1A
				} // end if
			} // end for
			// Assertion: theArray[0..n-pass-1] < theArray[n-pass]
			pass++; countOfWork += 2; // 1A, 1D
	} // end while
} // end bubbleSort 

