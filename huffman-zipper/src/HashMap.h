#pragma once
#include <vector>

#include "HashCode.h"
#include "Constants.h"

/**
 * This class implements an association between keys and values.
 *
 * It stores a set of key-value pairs and uses a hash table as its
 * underlying representation.
 */
template <typename KeyType, typename ValueType>
class HashMap {
private:

	/** Type definition for each cells in the bucket chain */
	struct Entry {
		KeyType key;
		ValueType value;
		Entry* next;
	};

	std::vector<Entry*> buckets;	/**< Vector of pointer to Entry */
	int nBuckets;					/**< Total number of buckets */
	int numEntries;					/**< Total number of entries */

private:

	/** Creates vector of buckets to have nBuckets entries, each NULL.  */
	void createBuckets(int nBuckets);

	/** Deletes all the cells in the linked lists contained in vector. */
	void deleteBuckets(std::vector<Entry*>& buckets);

	/**
	 * Increases the buckets in the map and then rehashes all existing entries.
	 *
	 * This operation is used when the load factor (i.e. the number of cells per
	 * bucket) has increased enough such that the get() and put() operation
	 * are no longer of complexity of O(1).
	 */
	void expandAndRehash();

	/**
	 * Finds a cell in the chain for the specified bucket that matches key.
	 * @return pointer to the cell containing the matching key or NULL.
	 */
	Entry* findEntry(int bucket, const KeyType& key) const;

	/**
	 * @param parent cell preceding the matching cell.
	 * @see remove()
	 */
	Entry* findEntry(int bucket, const KeyType& key, Entry*& parent) const;

	/** Creates deep copy of src HashMap*/
	void deepCopy(const HashMap& src);

public:
	HashMap();
	virtual ~HashMap();

	/** This copy constructor is to make a deep copy of HashMap */
	HashMap(const HashMap& src);

	/** This operator= are defined assign from one map to another. */
	HashMap& operator=(const HashMap& src);

	/** Removes all entries from this map. */
	void clear();

	/** @returns the number of entries in this map. */
	int size() const;

	/** @returns <code>true</code> if this map contains no entries. */
	bool isEmpty() const;

	/** Associates <code>key</code> with <code>value</code> in this map. */
	void put(const KeyType& key, const ValueType& value);

	/**
	* @returns the value associated with <code>key</code> in this map.
	* @returns the default value for ValueType, if <code>key</code> is not found
	*/
	ValueType get(const KeyType& key) const;

	/**
	 * @returns <code>true</code> if there is an entry for <code>key</code>
	 * in this map.
	 */
	bool containsKey(const KeyType& key) const;

	/**
	 * removes any entry for <code>key</code> from this map.
	 * If the given key is not found, has no effect.
	 */
	void remove(const KeyType& key);

	/**
	 * Selects the value associated with <code>key</code>.
	 * @returns a reference to its associated value.
	 *
	 * If key is not present in the map, a new entry is created
	 * whose value is set to the default for the value type.
	 */
	ValueType& operator[](const KeyType& key);
	ValueType operator[](const KeyType& key) const;


	/**
	 * Iterator support for class HashMap
	 */
	class iterator {
	private:
		const HashMap* map;          /**< Pointer to the map           */
		int bucket;                  /**< Index of current bucket      */
		Entry* current;              /**< Current cell in bucket chain */

	public:
		iterator() {}

		iterator(const HashMap* map, bool end) {
			this->map = map;
			if (end) {
				bucket = map->nBuckets;
				current = nullptr;
			}
			else {
				bucket = 0;
				current = map->buckets.at(bucket);
				while (current == nullptr && ++bucket < map->nBuckets) {
					current = map->buckets.at(bucket);
				}
			}
		}

		iterator(const iterator& it) {
			map = it.map;
			bucket = it.bucket;
			current = it.current;
		}

		iterator& operator++() {
			current = current->next;
			while (current == nullptr && ++bucket < map->nBuckets) {
				current = map->buckets.at(bucket);
			}
			return *this;
		}

		iterator operator++(int) {
			iterator copy(*this);
			operator++();
			return copy;
		}

		bool operator==(const iterator& rhs) {
			return map == rhs.map && bucket == rhs.bucket && current == rhs.current;
		}

		bool operator!=(const iterator& rhs) {
			return !(*this == rhs);
		}

		Entry operator*() {
			return *current;
		}

		Entry* operator->() {
			return current;
		}

		// iterator traits
		using difference_type = Entry;
		using value_type = Entry;
		using pointer = const Entry*;
		using reference = const Entry&;
		using iterator_category = std::forward_iterator_tag;
	};

	iterator begin() const {
		return iterator(this, false);
	}

	iterator end() const {
		return iterator(this, true);
	}
};

/************************************************************************/
/* implementation                                                       */
/************************************************************************/

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::createBuckets(int nBuckets) {
	if (nBuckets == 0) nBuckets = 1;
	buckets = std::vector<Entry*>(nBuckets, nullptr);
	this->nBuckets = nBuckets;
	numEntries = 0;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::deleteBuckets(std::vector<Entry*>& buckets) {
	for (int i = 0; i < buckets.size(); i++) {
		Entry* current = buckets[i];
		while (current != nullptr) {
			Entry* np = current->next;
			delete current;
			current = np;
		}
		buckets[i] = nullptr;
	}
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::expandAndRehash() {
	std::vector<Entry*> oldBuckets = buckets;
	createBuckets(oldBuckets.size() * 2 + 1);
	for (int i = 0; i < oldBuckets.size(); i++) {
		for (Entry* current = oldBuckets[i]; current != nullptr; current = current->next) {
			put(current->key, current->value);
		}
	}
	deleteBuckets(oldBuckets);
}

template <typename KeyType, typename ValueType>
typename HashMap<KeyType, ValueType>::Entry*
HashMap<KeyType, ValueType>::findEntry(int bucket, const KeyType& key) const {
	Entry* parent;
	return findEntry(bucket, key, parent);
}

template <typename KeyType, typename ValueType>
typename HashMap<KeyType, ValueType>::Entry*
HashMap<KeyType, ValueType>::findEntry(int bucket, const KeyType& key, Entry*& parent) const {
	parent = nullptr;
	Entry* current = buckets.at(bucket);
	while (current != nullptr && key != current->key) {
		parent = current;
		current = current->next;
	}
	return current;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::deepCopy(const HashMap& src) {
	createBuckets(src.nBuckets);
	for (int i = 0; i < src.nBuckets; i++) {
		for (Entry* current = src.buckets.at(i); current != nullptr; current = current->next) {
			put(current->key, current->value);
		}
	}
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap() {
	createBuckets(INITIAL_BUCKET_COUNT);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
	deleteBuckets(buckets);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap(const HashMap& src) {
	deepCopy(src);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator=(const HashMap& src) {
	if (this != &src) {
		clear();
		deepCopy(src);
	}
	return *this;
}

template <typename KeyType, typename ValueType>
int HashMap<KeyType, ValueType>::size() const {
	return numEntries;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::isEmpty() const {
	return size() == 0;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) {
	(*this)[key] = value;
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::get(const KeyType& key) const {
	Entry* current = findEntry(hashCode(key) % nBuckets, key);
	if (current == nullptr) return ValueType();
	return current->value;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::containsKey(const KeyType& key) const {
	return findEntry(hashCode(key) % nBuckets, key) != nullptr;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::remove(const KeyType& key) {
	int bucket = hashCode(key) % nBuckets;
	Entry* parent;
	Entry* current = findEntry(bucket, key, parent);
	if (current != nullptr) {
		if (parent == nullptr) {
			buckets[bucket] = current->next;
		}
		else {
			parent->next = current->next;
		}
		delete current;
		numEntries--;
	}
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::clear() {
	deleteBuckets(buckets);
	numEntries = 0;
}

template <typename KeyType, typename ValueType>
ValueType& HashMap<KeyType, ValueType>::operator[](const KeyType& key) {
	int bucket = hashCode(key) % nBuckets;
	Entry* current = findEntry(bucket, key);
	if (current == nullptr) {
		if (numEntries > MAX_LOAD_PERCENTAGE * nBuckets / 100.0) {
			expandAndRehash();
			bucket = hashCode(key) % nBuckets;
		}
		current = new Entry;
		current->key = key;
		current->value = ValueType();
		current->next = buckets[bucket];
		buckets[bucket] = current;
		numEntries++;
	}
	return current->value;
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::operator[](const KeyType& key) const {
	return get(key);
}
