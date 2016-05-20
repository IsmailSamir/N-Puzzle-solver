#pragma once
#include"Priority_Queue.h"


class Tree {
private:
	deque<N_Puzzle> Queue; //Queue For BFS Algorithm.		
	Priority_Queue OpenList; //The set of tentative nodes to be evaluated, initially containing the start node.
	map<string, N_Puzzle> ClosedList;  	//The set of nodes already evaluated.
	multimap<string, pair<N_Puzzle, N_Puzzle>>Came_From; // The map of navigated nodes.
	vector<N_Puzzle> total_path; //path from start state to goal state.
	clock_t start, stop, Time; //To Calculate Time.
public:

	//Check if Puzzle Solvable or Not.
	void CheckSolvability(N_Puzzle& Intial_State) {
		start = clock(); //Start StopWatch.
		//Check if Given Puzzle Solvable.
		if (Intial_State.isSolvable() == false) {
			stop = clock(); //Stop StopWatch.
			cout << "\nIt's Unsolvable!!!!!" << endl;
			printf("Time : %.2f sec.\n", float((stop - start) / CLOCKS_PER_SEC)); //Calculate Duration_Time.
		}
		else
			A_Star(Intial_State); //Call A* Function.

	}

	//A* Algorithm.
	void A_Star(N_Puzzle& Intial_State) {

		OpenList.Heap_Insert(Intial_State); //Insert Initial_State at OpenList.
		
		//While OpenList not empty.
		while (!OpenList.isEmpty())
		{
			N_Puzzle Current = OpenList.Heap_Extract_Min(); //Get state with minimum F(n) from OpenList.

			//Is this Goal state.
			if (Current.isGoal()) {
				cout << "\n\t\t     (Using A* Algorithm.)\nSolvable..!" << endl;
				cout << "Number Of Steps : " << Current.gVal << endl;
				stop = clock();
				printf("Time : %.2f sec.\n", (float)((float)(stop - start) / CLOCKS_PER_SEC)); //Calculate Duration_Time.
				if (Intial_State.theSize == 3 && Current.gVal != 0)
					Display_Path(reconstruct_path(Came_From, Current)); //To Display Path For 3X3 Puzzle.
				break;
			}

			//Generate all possible Next states of the puzzle.
			for (int i = 0; i < 4; ++i)
			{
				N_Puzzle NextState = Current;
				if (Current.isValid((N_Puzzle::direction)i)) //Check if the move is valid.
				{
					//Make move and get Next_State.
					NextState.move((N_Puzzle::direction)i);
					NextState.gVal = Current.gVal + abs(Current.gVal - NextState.gVal);	// length of this path.
					NextState.hVal = NextState.HammingDistance(); //Calculate heuristice_value.
					NextState.fVal = NextState.gVal + NextState.hVal; //Calculate F(n)=F(h)+F(g).
			
					//Check if NextState is in OpenList.
					if (OpenList.Hash.find(NextState.HashValue) != OpenList.Hash.end()) {
						//We already have same state in the openList.
						map<string, int>::iterator itOpen = OpenList.Hash.find(NextState.HashValue);
						if (OpenList.List[itOpen->second].fVal > NextState.fVal) {
							//We have found a better way to reach at this state. Discard the costlier one.
							OpenList.Remove(OpenList.List[itOpen->second], itOpen->second); //Remove it from OpenList.
							OpenList.Heap_Insert(NextState); //Insert state with lower F(n).
						}
					}
					
					//Check if NextState is in ClosedList.
					if (ClosedList.find(NextState.HashValue) != ClosedList.end()) {
						//We have found a better way to reach at this state. Discard the costlier one.
						map<string, N_Puzzle>::iterator itClosed = ClosedList.find(NextState.HashValue);
						if (itClosed->second.fVal > NextState.fVal) {
							ClosedList.erase(itClosed); //Remove it from ClosedList.
							OpenList.Heap_Insert(NextState); //Insert state with lower F(n).
						}
					}
					
					// Either this is a new state, or better than previous one.
					if (ClosedList.find(NextState.HashValue) == ClosedList.end() && OpenList.Hash.find(NextState.HashValue) == OpenList.Hash.end()) {
						OpenList.Heap_Insert(NextState); //Insert new state
						// This path is the best until now. Record it!
						Came_From.emplace(NextState.HashValue, make_pair(NextState, Current));
					}					
				}
			}
			ClosedList.emplace(Current.HashValue, Current); //Insert Current at ClosedList.
		}
	}

	//Return Path From Initial State To Goal State.
	vector<N_Puzzle> reconstruct_path(multimap<string, pair<N_Puzzle, N_Puzzle>> Came_From, N_Puzzle& current) {
		total_path.push_back(current); //Push Goal State.
		//Check IF State is Found Or Not.
		while (Came_From.find(current.HashValue) != Came_From.end()) {
			current = Came_From.find(current.HashValue)->second.second; //Get Parent Of Current State.
			total_path.push_back(current); //Push Parent State.
		}
		return total_path; //Return Path From Initial State To Goal State.
	}

	//Display The Path.
	void Display_Path(vector<N_Puzzle> Path) {
		for (int i = Path.size() - 1; i >= 0; --i) {
			Path[i].print();
			cout << endl << endl;
		}
	}

	//BFS Algorithm.
	void Breadth_First_Search(N_Puzzle Intial_State) {
		bool Flage = false;
		map<string, N_Puzzle> TempForSearch; //For Search In OpenList.
		int Steps = 0; //Number of steps.
		Queue.push_back(Intial_State); //Push Initial_State in Queue.
		TempForSearch.emplace(Intial_State.HashValue, Intial_State); 
		//While Queue not empty.
		while (!Queue.empty()){
			N_Puzzle Parent = Queue.front(); //Get Top of Queue.
			Queue.pop_front();

			ClosedList.emplace(Parent.HashValue, Parent); //Insert Parent at ClosedList.

			//Is this Goal state.
			if (Parent.isGoal()) {
				cout << "\n\t\t     (Using Breadth_First_Search)\nSolvable..!" << endl;
				cout << "Number Of Steps : " << Steps << endl;
				stop = clock();
				printf("Time : %.2f sec.\n", (float)((float)(stop - start) / CLOCKS_PER_SEC)); //Calculate Duration_Time.
				if (Intial_State.theSize == 3 && Steps > 1)
					Display_Path(reconstruct_path(Came_From, Parent)); //To Display Path For 3X3 Puzzle.
				break;
			}
			Steps++; //Increment Number of steps.
		    //Generate all possible Next states of the puzzle.
			for (int i = 0; i < 4; ++i) {
				N_Puzzle Child = Parent;
				//Check if the move is valid.
				if (Parent.isValid((N_Puzzle::direction)i)) {
					//Make move and get Next_State.
					Child.move((N_Puzzle::direction)i);
					//Is this Goal state.
					if (Child.isGoal()) {
						cout << "\n\t\t     (Using Breadth_First_Search)\nSolvable..!" << endl;
						cout << "Number Of Steps : " << Steps << endl;
						stop = clock();
						printf("Time : %.2f sec.\n", (float)((float)(stop - start) / CLOCKS_PER_SEC)); //Calculate Duration_Time.
						if (Intial_State.theSize == 3 && Steps > 1)
							Display_Path(reconstruct_path(Came_From, Child)); //To Display Path For 3X3 Puzzle.
						break;
					}
					//Check if Child is not in ClosedList and Queue.
					if (ClosedList.find(Child.HashValue) == ClosedList.end() && TempForSearch.find(Child.HashValue) == TempForSearch.end()) {
						Queue.push_back(Child); //Push Child in Queue.
						TempForSearch.emplace(Child.HashValue, Child);
						// This path is the best until now. Record it!
						Came_From.emplace(Child.HashValue, make_pair(Child, Parent));
					}
				}
			}
		}
	}
};