#include<iostream>
using  namespace std{


Main()
{

	int thread_number = 1;
	startThreads();
}

Thread1()
{
	do {

		// entry section
		// wait until threadnumber is 1
		while (threadnumber == 2)
			;

		// critical section

		// exit section
		// give access to the other thread
		threadnumber = 2;

		// remainder section

	} while (completed == false)
}

Thread2()
{

	do {

		// entry section
		// wait until threadnumber is 2
		while (threadnumber == 1)
			;

		// critical section

		// exit section
		// give access to the other thread
		threadnumber = 1;

		// remainder section

	} while (completed == false)
}
}