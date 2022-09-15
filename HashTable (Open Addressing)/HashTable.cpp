#include "HashTable.h"

template<class T>
HashTable<T>::HashTable()
	: kA1(rand() % 1000 + 1), kB1(rand() % 1000 + 1), kA2(rand() % 1000 + 1), kB2(rand() % 1000 + 1),
	load_factor_(0), buckets_count_(14657), buckets_filled_(0)
{
}

template<class T>
HashTable<T>::~HashTable()
{
	delete[] buckets_array_;
}

template<class T>
inline int HashTable<T>::size()
{
	return buckets_filled_;
}

template<class T>
inline int HashTable<T>::hash1(long long key)
{
	return ((kA1 * key + kB1) % kP1) % buckets_count_;
}

template<class T>
inline int HashTable<T>::hash2(long long key)
{
	return (buckets_count_ - 1) - (((kA2 * key + kB2) % kP2) % (buckets_count_ - 1));
}

template<class T>
bool HashTable<T>::is_prime(int number)
{
	for (int i = 2; i <= number / 2; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}

template<class T>
void HashTable<T>::relocate_memory()
{
	int old_buckets_count = buckets_count_;
	buckets_count_ *= kArrExt;

	buckets_filled_ = 0;

	while (!is_prime(buckets_count_))
	{
		++buckets_count_;
	}

	HashNode<T>* temp_arr = new HashNode<T>[buckets_count_];

	for (int i = 0; i < old_buckets_count; i++)
	{
		if (buckets_array_[i].type == Type::Occupied)
		{
			int h1 = hash1(buckets_array_[i].key);
			int h2 = hash2(buckets_array_[i].key);
			int index = h1;

			int j = 1;
			while (temp_arr[index].type == Type::Occupied)
			{
				index = (h1 + j * h2) % buckets_count_;
				++j;
			}

			temp_arr[index].type = Type::Occupied;
			temp_arr[index].key = buckets_array_[i].key;
			temp_arr[index].value = buckets_array_[i].value;

			++buckets_filled_;
			load_factor_ = (float)buckets_filled_ / (float)buckets_count_;
		}
	}

	delete[] buckets_array_;
	buckets_array_ = temp_arr;
}

template<class T>
void HashTable<T>::insert(long long key, T value)
{
	int h1 = hash1(key);
	int h2 = hash2(key);
	int index = h1;

	int i = 1;
	while (buckets_array_[index].type == Type::Occupied)
	{
		if (buckets_array_[index].key == key)
		{
			buckets_array_[index].value = value;
			return;
		}
		index = (h1 + i * h2) % buckets_count_;
		++i;
	}

	buckets_array_[index].type = Type::Occupied;
	buckets_array_[index].key = key;
	buckets_array_[index].value = value;

	++buckets_filled_;
	load_factor_ = (float)buckets_filled_ / (float)buckets_count_;

	if (load_factor_ > load_border_)
	{
		relocate_memory();
	}
}

template<class T>
void HashTable<T>::erase(long long key)
{
	int h1 = hash1(key);
	int h2 = hash2(key);
	int index = h1;

	int i = 1;
	while (buckets_array_[index].type != Type::Empty)
	{
		if (buckets_array_[index].key == key && buckets_array_[index].type == Type::Occupied)
		{
			buckets_array_[index].type = Type::Removed;
			--buckets_filled_;

			/*int next = (h1 + i * h2) % buckets_count_;
			while (buckets_array_[next].type != Type::Empty)
			{
				if (buckets_array_[next].type == Type::Occupied)
				{
					buckets_array_[next].type = Type::Removed;
					--buckets_filled_;
					insert(buckets_array_[next].key, buckets_array_[next].value);
				}
				++i;
				next = (h1 + i * h2) % buckets_count_;
			}*/
			return;
		}
		index = (h1 + i * h2) % buckets_count_;
		++i;
	}
}

template<class T>
HashTable<T>::HashNode<T>* HashTable<T>::find(long long key)
{
	int h1 = hash1(key);
	int h2 = hash2(key);
	int index = h1;

	int i = 1;
	while (buckets_array_[index].type != Type::Empty)
	{
		if (buckets_array_[index].key == key && buckets_array_[index].type == Type::Occupied)
		{
			return &buckets_array_[index];
		}
		index = (h1 + i * h2) % buckets_count_;
		++i;
	}
	return nullptr;
}