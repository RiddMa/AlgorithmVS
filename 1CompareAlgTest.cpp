#include"1CompareAlgTest.h"
#include"1ComparetheAlgorithms.h"

int RamdomListGen(int* A, int num, int range)
{
	srand(time(NULL));
	for (int i = 0; i < num; i++)
	{
		A[i] = (rand() % range - range / 2);
	}
	return num;
}

/*
#define RAND 0
#define ZERO 1
#define MAX 2
#define MIN 3
#define RANDSAME 4
#define NEGRAND 5
*/
void ListGen(int* List, int arg, int num, int range)
{
	switch (arg)
	{
	case 0:
	{
		srand(time(NULL));
		for (int i = 0; i < num; i++)
		{
			List[i] = (rand() % range - range / 2);
		}
		break;
	}
	case 1:
	{
		for (int i = 0; i < num; i++)
		{
			List[i] = 0;
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < num; i++)
		{
			List[i] = INT_MAX;
		}
		break;
	}
	case 3:
	{
		for (int i = 0; i < num; i++)
		{
			List[i] = INT_MIN;
		}
		break;
	}
	case 4:
	{
		srand(time(NULL));
		int value = rand() % range - range / 2;
		for (int i = 0; i < num; i++)
		{
			List[i] = value;
		}
		break;
	}
	case 5:
	{
		srand(time(NULL));
		int value = rand() % range - range;
		for (int i = 0; i < num; i++)
		{
			List[i] = value;
		}
		break;
	}
	}
}

long long CountTime(testFunc func, int* array, int N)
{
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	// Activity to be timed
	func(array, N);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	return ElapsedMicroseconds.QuadPart;
}

void perfTest()
{
	int size;
	cout << "\nRunning performance test:" << endl;
	cout << "Input sequence size:" << endl;
	cin >> size;
	int* A = new int[size];

	//test rand
	for (int i = 0; i < 6; i++)
	{
		ListGen(A, i, size, 1000);
		switch (i)
		{
		case 0:cout << "Testing RANDOM sequence\n"; break;
		case 1:cout << "Testing ZERO sequence\n"; break;
		case 2:cout << "Testing INT_MAX sequence\n"; break;
		case 3:cout << "Testing INT_MIN sequence\n"; break;
		case 4:cout << "Testing RANDOMSAME sequence\n"; break;
		case 5:cout << "Testing NEGRAND sequence\n"; break;
		}
		try {
			cout << "Time used for O(N): " << CountTime(MaxSubsequenceSumN, A, size) << " us" << endl;
			cout << "Time used for O(NlogN): " << CountTime(MaxSubsequenceSumNlogN, A, size) << " us" << endl;
			cout << "Time used for O(N2): " << CountTime(MaxSubsequenceSumN2, A, size) << " us" << endl;
			cout << "Time used for O(N3): " << CountTime(MaxSubsequenceSumN3, A, size) << " us" << endl;
		}
		catch (const char* msg) {
			cerr << msg << endl;
		}
		cout << endl;
	}
}

void correctnessTest()
{
	cout << "Running correctness test:" << endl;
	int size = 10;
	try {
		int* A = new int[size];
		ListGen(A, 0, size, 300);
		cout << "{ ";
		for (int i = 0; i < size; i++)
			cout << A[i] << ", ";
		cout << "}" << endl;

		cout << MaxSubsequenceSumN(A, size) << endl;
		cout << MaxSubsequenceSumNlogN(A, size) << endl;
		cout << MaxSubsequenceSumN2(A, size) << endl;
		cout << MaxSubsequenceSumN3(A, size) << endl;
		cout << endl;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	int* B = new int[size];

	try {
		cout << "All zero" << endl;
		ListGen(B, 1, size, 100);
		cout << MaxSubsequenceSumN(B, size) << endl;
		cout << MaxSubsequenceSumNlogN(B, size) << endl;
		cout << MaxSubsequenceSumN2(B, size) << endl;
		cout << MaxSubsequenceSumN3(B, size) << endl;
		cout << endl;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	try {
		cout << "All INT_MAX" << endl;
		ListGen(B, 2, size, 100);
		cout << MaxSubsequenceSumN(B, size) << endl;
		cout << MaxSubsequenceSumNlogN(B, size) << endl;
		cout << MaxSubsequenceSumN2(B, size) << endl;
		cout << MaxSubsequenceSumN3(B, size) << endl;
		cout << endl;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	try {
		cout << "All INT_MIN" << endl;
		ListGen(B, 3, size, 100);
		cout << MaxSubsequenceSumN(B, size) << endl;
		cout << MaxSubsequenceSumNlogN(B, size) << endl;
		cout << MaxSubsequenceSumN2(B, size) << endl;
		cout << MaxSubsequenceSumN3(B, size) << endl;
		cout << endl;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	try {
		cout << "All negative" << endl;
		ListGen(B, 5, size, 100);
		//B[0] = 1; B[1] = -1; B[2] = 2; B[3] = -1; B[4] = 2;
		cout << MaxSubsequenceSumN(B, size) << endl;
		cout << MaxSubsequenceSumNlogN(B, size) << endl;
		cout << MaxSubsequenceSumN2(B, size) << endl;
		cout << MaxSubsequenceSumN3(B, size) << endl;
		cout << endl;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}


	try {
		cout << "{ INT_MIN, INT_MIN, INT_MAX }" << endl;
		int C[] = { INT_MIN, INT_MIN, INT_MAX };
		cout << MaxSubsequenceSumN(C, 3) << endl;
		cout << MaxSubsequenceSumNlogN(C, 3) << endl;
		cout << MaxSubsequenceSumN2(C, 3) << endl;
		cout << MaxSubsequenceSumN3(C, 3) << endl;
		cout << endl;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

int main()
{
	correctnessTest();
	perfTest();
	return 0;
}