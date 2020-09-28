#pragma once
#include<iostream>
#include<Windows.h>
#include<profileapi.h>
#include<functional>
#include<stdlib.h>
#include<ctime>
using namespace std;

typedef std::function<int(int*, int)> testFunc;


int RamdomListGen(int* A, int num, int range);
