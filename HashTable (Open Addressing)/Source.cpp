#include "HashTable.h"
#include "HashTable.cpp"
#include <unordered_map>

long long generateRandLong()
{
	int digit = rand() % 7 + 9;
	long long res = 0;
	int number;

	for (int i = 0; i < digit - 1; i++)
	{
		number = rand() % 10;
		res += (long long)(number * pow(10, i));
	}

	number = rand() % 9 + 1;
	res += (long long)(number * pow(10, digit - 1));

	return res;
}

struct Zombie
{
	char name;
	char color;
	int	num_of_bitten;

	Zombie(int for_name = 0, int for_color = 0, int for_bitten = 0)
		: name((char)(for_name % 26 + 65)), color((char)(for_color % 26 + 97)), num_of_bitten(for_bitten % 1001)
	{
	}
};

bool testHashTable()
{
	const int iters = 500000;
	const int keysAmount = iters * 1;

	// generate random keys:
	long long* keys = new long long[keysAmount];

	long long* keysToInsert = new long long[iters];
	long long* keysToErase = new long long[iters];
	long long* keysToFind = new long long[iters];

	for (int i = 0; i < keysAmount; i++)
	{
		keys[i] = generateRandLong();
	}
	for (int i = 0; i < iters; i++)
	{
		keysToInsert[i] = keys[generateRandLong() % keysAmount];
		keysToErase[i] = keys[generateRandLong() % keysAmount];
		keysToFind[i] = keys[generateRandLong() % keysAmount];
	}

	// test my HashTable:
	HashTable<Zombie> hashTable;

	clock_t myStart = clock();
	for (int i = 0; i < iters; i++)
	{
		hashTable.insert(keysToInsert[i], Zombie(rand(), rand(), rand()));
	}
	int myInsertSize = hashTable.size();
	for (int i = 0; i < iters; i++)
	{
		hashTable.erase(keysToErase[i]);
	}
	int myEraseSize = hashTable.size();
	int myFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (hashTable.find(keysToFind[i]) != NULL)
		{
			myFoundAmount++;
		}
	}
	clock_t myEnd = clock();
	float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

	// test STL hash table:
	unordered_map<long long, Zombie> unorderedMap;

	clock_t stlStart = clock();
	for (int i = 0; i < iters; i++)
	{
		unorderedMap.insert({ keysToInsert[i], Zombie(rand(), rand(), rand()) });
	}
	int stlInsertSize = unorderedMap.size();
	for (int i = 0; i < iters; i++)
	{
		unorderedMap.erase(keysToErase[i]);
	}
	int stlEraseSize = unorderedMap.size();
	int stlFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
		{
			stlFoundAmount++;
		}
	}
	clock_t stlEnd = clock();
	float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

	cout << "My HashTable:" << endl;
	cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << endl;
	cout << "STL unordered_map:" << endl;
	cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl << endl;

	delete[] keys;
	delete[] keysToInsert;
	delete[] keysToErase;
	delete[] keysToFind;

	if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount)
	{
		cout << "The check is completed" << endl;
		return true;
	}

	cerr << ":(" << endl;
	return false;
}

int main()
{
	srand(time(0));
	testHashTable();

	//const int iters = 100000;
	//const int keysAmount = iters * 1;

	//// generate random keys:
	//long long* keys = new long long[keysAmount];

	//long long* keysToInsert = new long long[iters];
	//long long* keysToErase = new long long[iters];
	//long long* keysToFind = new long long[iters];

	//float time_tmp = 100.0f;
	//float res = 0.0f;
	//for (float i = 0.01f; i < 1.0f; i += 0.01f)
	//{
	//	for (int i = 0; i < keysAmount; i++)
	//	{
	//		keys[i] = generateRandLong();
	//	}
	//	for (int i = 0; i < iters; i++)
	//	{
	//		keysToInsert[i] = keys[generateRandLong() % keysAmount];
	//		keysToErase[i] = keys[generateRandLong() % keysAmount];
	//		keysToFind[i] = keys[generateRandLong() % keysAmount];
	//	}

	//	// test my HashTable:
	//	HashTable<Zombie> hashTable;
	//	hashTable.change_load_factor(i);

	//	clock_t myStart = clock();
	//	for (int i = 0; i < iters; i++)
	//	{
	//		hashTable.insert(keysToInsert[i], Zombie(rand(), rand(), rand()));
	//	}
	//	int myInsertSize = hashTable.size();
	//	for (int i = 0; i < iters; i++)
	//	{
	//		hashTable.erase(keysToErase[i]);
	//	}
	//	int myEraseSize = hashTable.size();
	//	int myFoundAmount = 0;
	//	for (int i = 0; i < iters; i++)
	//	{
	//		if (hashTable.find(keysToFind[i]) != NULL)
	//		{
	//			myFoundAmount++;
	//		}
	//	}
	//	clock_t myEnd = clock();
	//	float myTime = ((float)(myEnd - myStart)) / CLOCKS_PER_SEC;
	//	if (myTime < time_tmp)
	//	{
	//		time_tmp = myTime;
	//		res = i;
	//	}
	//}

	//delete[] keys;
	//delete[] keysToInsert;
	//delete[] keysToErase;
	//delete[] keysToFind;

	//cout << res;

	return 0;
}