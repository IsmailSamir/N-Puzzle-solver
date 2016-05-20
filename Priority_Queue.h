#pragma once
#include"NPuzzle.h"

class Priority_Queue
{
private:
	int HeapSize;
public:
	 map<string, int> Hash; //Hash For Searching in OpenList.
	 N_Puzzle* List; //Pointer To Puzzle.
	
	//Default Constructor.
	Priority_Queue() {
		List = new N_Puzzle[9999]; //Decleration and Initialize List With MaxSize.
		HeapSize = -1; //Set HeapSize
	}

	//Check if the Heap empty or Not.
	bool isEmpty() {
		return HeapSize < 0;
	}

	//Return Heap_Size (OpenList_Size).
	int GetListSize() {
		return HeapSize;
	}

	//Return State with Minimum F(n) in Heap (OpenList).
	N_Puzzle Heap_Minimum() {
		return List[0];
	}

	//Return State with Minimum F(n) in Heap (OpenList) and Remove it from the Heap(OpenList).
	N_Puzzle Heap_Extract_Min() {

		N_Puzzle Min = List[0];
		Hash.erase(List[0].HashValue); //Remove state from hash.
		if (HeapSize != 0) {
			List[0] = List[HeapSize];
			Hash[List[HeapSize].HashValue] = 0; //ReSet Index.
		}
		HeapSize--; //Decrement HeapSize.
		Min_Heapify(0); //Make Minimum_Heapify to Set State with Minimum F(n) at the top of Priority_Queue.
		return Min;

	}

	//Insert new Key in the Heap (OpenList).
	void Heap_Insert(N_Puzzle& Key) {
		HeapSize++; //Increment HeapSize.
		Decrease_Key(HeapSize, Key); //Insert Key.
	}

	// Remove puzzle from OpenList.
	void Remove(N_Puzzle& Key,int i) {
		Hash.erase(Key.HashValue); //Remove state from hash.
		List[i] = List[HeapSize];
		Hash[List[HeapSize].HashValue] = i; //Rest Index
		List[HeapSize] = N_Puzzle(); //Reset Last Index with Default.
		HeapSize--; //Decrement HeapSize.
		Min_Heapify(i); //Make Minimum_Heapify to Set State with Minimum F(n) at the top of Priority_Queue.
	}

private:
	// Return index of Parent.
	int Parent(int i) {
		return floor((i / 2));
	}
	
	// Return index of Left.
	int Left(int i) {
		return i * 2;
	}
	
	// Return index of Right.
	int Right(int i) {
		return (i * 2) + 1;
	}
	
	// Let Heap in Min_Heapify Properety.
	void Min_Heapify(int i) {
		int L = Left(i);
		int R = Right(i);
		int Smallest = i;
		//Get Index Of State with Minimum F(n).
		if ((L <= HeapSize) && (List[L] < List[i]))
			Smallest = L;
		if ((R <= HeapSize) && (List[R] < List[Smallest]))
			Smallest = R;

		//Swap elements Until each element reaches to his Exact Position.
		if (Smallest != i) {
			swap(List[i], List[Smallest]);
			Hash[List[i].HashValue] = i; //ReSet Index.
			Hash[List[Smallest].HashValue] = Smallest; //ReSet Index.
			Min_Heapify(Smallest);
		}
	}

	// Used in Insert Function to Let Heap in Min_Heapify Properety.
	void Decrease_Key(int i, N_Puzzle& Key) {
		List[i] = Key; //Insert Key.
		Hash.emplace(Key.HashValue, i); //Insert Key at Hash.
		//Swap elements Until each element reaches to his Exact Position. 
		while ((i > 0) && (List[Parent(i)] > List[i]))
		{
			swap(List[i], List[Parent(i)]);
			Hash[List[i].HashValue] = i; //ReSet Index.
			Hash[List[Parent(i)].HashValue] = Parent(i); //ReSet Index.
			i = Parent(i);
		}
	}
	
};