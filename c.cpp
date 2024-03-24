#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <set>

using namespace std;
using namespace std::chrono;

struct Teacher {
    string name = "Surname_Name_MiddleName";
    string faculty = "Faculty";
    string academic_title = "Title";
    string degree = "Degree";

    bool operator==(const Teacher& teacher) const {
        return this->faculty == teacher.faculty && this->name == teacher.name && this->degree == teacher.degree &&
               this->academic_title == teacher.academic_title;
    }

    bool operator<(const Teacher& teacher) const {
        if (this->faculty == teacher.faculty)
            if (this->name == teacher.name)
                if (this->degree == teacher.degree)
                    return this->academic_title < teacher.academic_title;
                else return this->degree < teacher.degree;
            else return this->name < teacher.name;
        else return this->faculty < teacher.faculty;
    }

    bool operator<=(const Teacher& teacher) const {
        return *this < teacher || *this == teacher;
    }

    bool operator>(const Teacher& teacher) const {
        return !(*this <= teacher);
    }

    bool operator>=(const Teacher& teacher) const {
        return !(*this < teacher);
    }

    friend ostream& operator<<(ostream& os, const Teacher& teacher);
};

ostream& operator<<(ostream& os, const Teacher& teacher) {
    os << teacher.faculty << ' ' << teacher.name << ' ' << teacher.degree << ' ' << teacher.academic_title;
    return os;
}

namespace std {
    template<>
    struct hash<Teacher> {
        size_t operator()(const Teacher& teacher) const {
            size_t hashValue = 0;
            hashValue ^= hash<string>{}(teacher.name) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            hashValue ^= hash<string>{}(teacher.faculty) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            hashValue ^= hash<string>{}(teacher.degree) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            hashValue ^= hash<string>{}(teacher.academic_title) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            return hashValue;
        }
    };
}

vector<Teacher> readFile(const string& file, int size) {
    ifstream inputFile(file);
    vector<Teacher> result(size);
    for (int i = 0; i < size; i++) {
        inputFile >> result[i].name;
        inputFile >> result[i].faculty;
        inputFile >> result[i].degree;
        inputFile >> result[i].academic_title;
    }
    inputFile.close();
    return result;
}

void searchBST(const vector<Teacher>& teachers, const Teacher& key) {
    clock_t start = clock();
    map<Teacher, int> bst;
    for (int i = 0; i < teachers.size(); ++i) {
        bst[teachers[i]] = i;
    }

    auto it = bst.find(key);
    clock_t stop = clock();

    if (it != bst.end()) {
        cout << "Element found at index " << it->second << " in BST." << endl;
    } else {
        cout << "Element not found in BST." << endl;
    }

    double duration = double(stop - start) / CLOCKS_PER_SEC;
    cout << "BST Search Time: " << duration * 1000 << " milliseconds" << endl;
}

void searchHashTable(const vector<Teacher>& teachers, const Teacher& key) {
    clock_t start = clock();
    unordered_map<Teacher, int> hashTable;
    for (int i = 0; i < teachers.size(); ++i) {
        hashTable[teachers[i]] = i;
    }

    auto it = hashTable.find(key);
    clock_t stop = clock();

    if (it != hashTable.end()) {
        cout << "Element found at index " << it->second << " in Hash Table." << endl;
    } else {
        cout << "Element not found in Hash Table." << endl;
    }

    double duration = double(stop - start) / CLOCKS_PER_SEC;
    cout << "Hash Table Search Time: " << duration * 1000 << " milliseconds" << endl;
}

void searchMultimap(const vector<Teacher>& teachers, const Teacher& key) {
    clock_t start = clock();
    multimap<Teacher, int> multimap;
    for (int i = 0; i < teachers.size(); ++i) {
        multimap.insert({teachers[i], i});
    }

    auto range = multimap.equal_range(key);
    clock_t stop = clock();

    bool found = false;
    for (auto it = range.first; it != range.second; ++it) {
        cout << "Element found at index " << it->second << " in Multimap." << endl;
        found = true;
    }
    if (!found) {
        cout << "Element not found in Multimap." << endl;
    }

    double duration = double(stop - start) / CLOCKS_PER_SEC;
    cout << "Multimap Search Time: " << duration * 1000 << " milliseconds" << endl;
}

void searchRedBlackTree(const vector<Teacher>& teachers, const Teacher& key) {
    clock_t start = clock();
    set<Teacher> redBlackTree;
    for (const auto& teacher : teachers) {
        redBlackTree.insert(teacher);
    }

    auto it = redBlackTree.find(key);
    clock_t stop = clock();

    if (it != redBlackTree.end()) {
        cout << "Element found in Red-Black Tree." << endl;
    } else {
        cout << "Element not found in Red-Black Tree." << endl;
    }

    double duration = double(stop - start) / CLOCKS_PER_SEC;
    cout << "Red-Black Tree Search Time: " << duration * 1000 << " milliseconds" << endl;
}


int main() {
    int sizes[9] = {500, 1000, 3000, 5000, 10000, 50000, 100000, 500000, 1000000};
    for (int size : sizes) {
        char buffer[50];
        sprintf(buffer, "random_string_%d.txt", size);
        vector<Teacher> teachers = readFile(buffer, size);
        Teacher key = teachers[rand() % size];

        cout << "Search for key: " << key << " in array of size " << size << endl;
        cout << "-------------------------------------------" << endl;

        searchBST(teachers, key);
        searchHashTable(teachers, key);
        searchRedBlackTree(teachers, key);
        searchMultimap(teachers, key);

        cout << endl;
    }
    return 0;
}
