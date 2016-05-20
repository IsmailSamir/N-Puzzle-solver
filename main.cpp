#pragma once
#include "AStar.h"
int main()
{
	//freopen("out.txt", "w", stdout); //Open File For Writing.
	//freopen("in.txt", "r", stdin); //Open File For Reading.



	int TheSize;
	cin >> TheSize;
	vector < vector<int> > State;
	vector<int> temp;
	for (int i = 0; i < TheSize; i++)
	{
		int var;
		for (int j = 0; j < TheSize; j++)
		{
			cin >> var;
			temp.push_back(var);
		}
		State.push_back(temp);
		temp.clear();
	}

	N_Puzzle Test(State);
	Tree TestTree;
	TestTree.CheckSolvability(Test);



	return 0;
}