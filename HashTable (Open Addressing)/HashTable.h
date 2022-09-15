#pragma once
#include "Header.h"

template <class T>
class HashTable
{
private:
	enum class Type
	{
		Empty,
		Removed,
		Occupied
	};
	template <class T>
	struct HashNode
	{
		HashNode()
			: type(Type::Empty), key(0), value(NULL)
		{
		}

		Type type;
		long long key;
		T value;
	};

	float load_border_ = 0.55f;

	const int kA1;
	const int kB1;
	const long long kP1 = 748117663422179;
	const int kA2;
	const int kB2;
	const long long kP2 = 296983563352733;

	const int kArrExt = 2;

	float load_factor_;
	int buckets_count_;
	int buckets_filled_;

	HashNode<T>* buckets_array_ = new HashNode<T>[buckets_count_];

	int hash1(long long key);
	int hash2(long long key);
	bool is_prime(int number);
	void relocate_memory();
public:
	HashTable();
	~HashTable();

	int size();
	void insert(long long key, T value);
	void erase(long long key);
	HashNode<T>* find(long long key);
	void change_load_factor(float a)
	{
		load_border_ = a;
	}
};
