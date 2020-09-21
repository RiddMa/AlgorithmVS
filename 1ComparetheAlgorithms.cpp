#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<Windows.h>
using namespace std;


int RamdomListGen(int* A, int num, int range)
{
	srand(time(NULL));
	for (int i = 0; i < num; i++)
	{
		A[i] = (rand() % range - range / 2);
	}
	return num;
}


int MaxSubsequenceSumN3(int A[], int N)
{
	int ThisSum, MaxSum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			ThisSum = 0;
			for (int k = i; k <= j; k++)
				ThisSum += A[k];
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}


int MaxSubsequenceSumN2(int A[], int N)
{
	int ThisSum, MaxSum = 0;
	for (int i = 0; i < N; i++)
	{
		ThisSum = 0;
		for (int j = i; j < N; j++)
		{
			ThisSum += A[j];
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}


int MaxSubsequenceSumNlogN(int A[], int left, int right)
{
	int ThisSum, MaxSum = 0, mid = (left + right) / 2-1;
	int LeftMax = MaxSubsequenceSumNlogN(A, left, mid);
	int RightMax = MaxSubsequenceSumNlogN(A, mid + 1, right);
	int Mid2LeftMax = 0, Mid2RightMax = 0;

	for (int i = mid, ThisSum = 0; i >= left; i--)
	{
		ThisSum += A[i];
		if (ThisSum >= Mid2LeftMax)
			Mid2LeftMax = ThisSum;
	}
	for (int i = mid, ThisSum = 0; i <= right; i++)
	{
		ThisSum += A[i];
		if (ThisSum >= Mid2LeftMax)
			Mid2RightMax = ThisSum;
	}
	int MidMax = Mid2LeftMax + Mid2RightMax;

	if (LeftMax > RightMax)
	{
		if (LeftMax > MidMax)
			MaxSum = LeftMax;
		else
			MaxSum = MidMax;
	}
	else
	{
		if (RightMax > MidMax)
			MaxSum = RightMax;
		else
			MaxSum = MidMax;
	}
	return MaxSum;
}


int MaxSubsequenceSumN(int A[], int N)
{
	int ThisSum = 0, MaxSum = 0;
	for (int i = 0; i < N; i++)
	{
		ThisSum += A[i];
		if (ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if (ThisSum < 0)
			ThisSum < 0;
	}
	return MaxSum;
}

void CountTime(int (*function)(int*, int),  char* str, int* array, int n)
{
	LARGE_INTEGER num;
	long long start = 0, end = 0, freq;
	QueryPerformanceFrequency(&num);
	freq = num.QuadPart;
	QueryPerformanceCounter(&num);
	start = num.QuadPart;
	function(array, n);
	QueryPerformanceCounter(&num);
	end = num.QuadPart;

	std::cout << (end - start) * 1000000 / freq << std::endl;
}


int main()
{
	int size;
	std::cin >> size;
	int* A = new int[size];
	RamdomListGen(A, size,100);

	clock_t begin = clock();
	MaxSubsequenceSumN(A,size);
	clock_t end = clock();
	double duration = ((double)end - (double)begin) / CLOCKS_PER_SEC;
	std::cout << duration;

	begin = clock();
	MaxSubsequenceSumNlogN(A, 0, size-1);
	end = clock();
	duration = ((double)end - (double)begin) / CLOCKS_PER_SEC;
	std::cout << duration;

	begin = clock();
	MaxSubsequenceSumN2(A, size);
	end = clock();
	duration = ((double)end - (double)begin) / CLOCKS_PER_SEC;
	std::cout << duration;

	begin = clock();
	MaxSubsequenceSumN3(A, size);
	end = clock();
	duration = ((double)end - (double)begin) / CLOCKS_PER_SEC;
	std::cout << duration;
}