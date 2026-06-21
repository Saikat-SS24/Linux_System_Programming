/* LRU Cache Implementation
Use doubly linked list + hash map to implement LRU Cache:
- Capacity-based eviction
- O(1) operations */

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
    int capacity;
    // The list stores the keys. Head is Most Recent, Tail is Least Recent.
    list<int> lruList; 
    // Map stores the key and a pair: {Value, Iterator pointing to the key in the list}
    unordered_map<int, pair<int, list<int>::iterator>> cache;

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        // 1. If key doesn't exist
        if (cache.find(key) == cache.end()) {
            return -1;
        }

        // 2. If it exists, move it to the front (Most Recently Used)
        // splice moves the element at cache[key].second to the front of lruList
        lruList.splice(lruList.begin(), lruList, cache[key].second);
        
        return cache[key].first;
    }

    void put(int key, int value) {
        // Case A: Key already exists
        if (cache.find(key) != cache.end()) {
            lruList.splice(lruList.begin(), lruList, cache[key].second);
            cache[key].first = value; // Update value
            return;
        }

        // Case B: New key - Check capacity
        if (cache.size() == capacity) {
            // Remove the Least Recently Used (back of the list)
            int lastKey = lruList.back();
            lruList.pop_back();
            cache.erase(lastKey);
        }

        // Add new key to the front
        lruList.push_front(key);
        cache[key] = {value, lruList.begin()};
    }
};

int main() {
    LRUCache cache(3);

    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);

    cout << "Value of 1: " << cache.get(1) << endl; // Moves 1 to front

    cache.put(4, 400); // Evicts key 2 (because it was the least recently used)

    if (cache.get(2) == -1) cout << "Key 2 was evicted!" << endl;

    return 0;
}



