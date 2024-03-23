#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

struct Teacher
{
    string name = "Surname_Name_MiddleName";
    string faculty = "Faculty";
    string academic_title = "Title";
    string degree = "Degree";

    bool operator == (const Teacher& teacher)
    {
        return this->faculty == teacher.faculty && this->name == teacher.name && this->degree == teacher.degree &&
        this->academic_title == teacher.academic_title;
    }

    bool operator < (const Teacher& teacher)
    {
        if (this->faculty == teacher.faculty)
            if (this->name == teacher.name)
                if (this->degree == teacher.degree)
                    return this->academic_title < teacher.academic_title;
                else return this->degree < teacher.degree;
            else return this->name < teacher.name;
        else return this->faculty < teacher.faculty;
    }

    bool operator <= (const Teacher& teacher)
    {
        return *this < teacher || *this == teacher;
    }

    bool operator > (const Teacher& teacher)
    {
        return !(*this <= teacher);
    }

    bool operator >= (const Teacher& teacher)
    {
        return !(*this < teacher);
    }
    friend ostream& operator<<(ostream& os, const Teacher& teacher);
};

    ostream& operator<<(ostream& os, const Teacher& teacher)
    {
        os << teacher.faculty << ' ' << teacher.name << ' ' << teacher.degree << ' ' << teacher.academic_title;
    }


void bubbleSort(vector<Teacher>& teachers) // n^2
{
    for (int i = 0; i < teachers.size(); i++)
        for (int j = 0; j < teachers.size() - 1; j++)
            if (teachers[j] > teachers[j + 1])
                swap(teachers[j], teachers[j + 1]);
}

void quickSort(vector<Teacher>& teachers, int start, int end) // n log n
{
    if (teachers.size() < 2)
        return;

    int l = start;
    int r = end;
    Teacher pivot = teachers[(l + r) / 2];

    while (l <= r)
    {
        while (teachers[l] < pivot)
            l++;
        while (teachers[r] > pivot)
            r--;
        if (l <= r)
            swap(teachers[l++], teachers[r--]);
    }
        if (start < r)
            quickSort(teachers, start, r);
        if (end > l)
            quickSort(teachers, l, end);
}

void mergeSort(vector<Teacher>& teachers, int l, int r) // n log n
{
    if (teachers.size() < 2)
        return;

    if (l == r) return;
    int mid = (l + r) / 2;
    mergeSort(teachers, l, mid);
    mergeSort(teachers, mid + 1, r);
    int i = l;
    int j = mid + 1;
    vector<Teacher> tmp;
    for (int step = 0; step < r - l + 1; step++)
    {
        if ((j > r) || ((i <= mid) && (teachers[i] < teachers[j])))
        {
            tmp.push_back(teachers[i]);
            i++;
        }
        else
        {
            tmp.push_back(teachers[j]);
            j++;
        }
    }
    for (int step = 0; step < r - l + 1; step++)
        teachers[l + step] = tmp[step];
}

vector<Teacher> readFile(string file, int size)
{
    ifstream inputFile(file);
    vector<Teacher> result(size);
    for (int i = 0; i < size; i++)
    {
        inputFile >> result[i].name;
        inputFile >> result[i].faculty;
        inputFile >> result[i].degree;
        inputFile >> result[i].academic_title;
    }
    inputFile.close();
    return result;
}

class BinaryTree {
private:
    struct Node {
        Teacher data;
        Node* left;
        Node* right;

        Node(Teacher obj) : data(obj), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Вспомогательный метод для рекурсивного поиска
    Node* searchRecursively(Node* node, const std::string& key) {
        if (node == nullptr || node->data.name == key) {
            return node;
        }

        if (key < node->data.name) {
            return searchRecursively(node->left, key);
        } else {
            return searchRecursively(node->right, key);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const vector<Teacher>& teachers)
    {
        for (auto i : teachers)
            root = insertRecursively(root, i);
    }

    // Метод для добавления элемента в дерево
    void insert(const Teacher& obj) {
        root = insertRecursively(root, obj);
    }

    // Рекурсивный метод для вставки элемента в дерево
    Node* insertRecursively(Node* node, const Teacher& obj) {
        if (node == nullptr) {
            return new Node(obj);
        }

        if (obj.name < node->data.name) {
            node->left = insertRecursively(node->left, obj);
        } else if (obj.name > node->data.name) {
            node->right = insertRecursively(node->right, obj);
        }

        return node;
    }

    // Метод для поиска элемента по ключу
    Node* search(const std::string& key) {
        return searchRecursively(root, key);
    }
};


int main()
{
    int sizes[7] {100, 300, 500, 1000, 3000, 5000, 10000};
    for (auto i: sizes)
    {
        char buffer[50];
        sprintf(buffer, "random_string_%d.txt", i);
        vector<Teacher> teachers1 = readFile(buffer, i);
        vector<Teacher> teachers2 = readFile(buffer, i);
        vector<Teacher> teachers3 = readFile(buffer, i);
//
//        BinaryTree tree;
//        for (int j = 0; j < i; j++)
//        {
//
//        }

        std::clock_t start_time1 = std::clock();
        bubbleSort(teachers1);
        std::clock_t end_time1 = std::clock();
        cout << "Bubble sort " << i << ": "  << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC << endl;

        std::clock_t start_time2 = std::clock();
        quickSort(teachers2, 0, teachers2.size() - 1);
        std::clock_t end_time2 = std::clock();
        cout << "Quick sort " << i << ": "  << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC << endl;

        std::clock_t start_time3 = std::clock();
        mergeSort(teachers3, 0, teachers3.size() - 1);
        std::clock_t end_time3 = std::clock();
        cout << "Merge sort " << i << ": "  << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC << endl;

        cout << endl;
        sprintf(buffer, "random_string_%d_sorted.txt", i);
        ofstream outputFile(buffer);
        for (int j = 0; j < teachers1.size(); ++j)
            outputFile << teachers2[j] << endl;
        outputFile.close();
    }

}