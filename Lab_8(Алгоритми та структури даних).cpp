#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

vector<int> Intersect_bruteforce(const vector<int>& A, const vector<int>& B, long long& comparisons) {
    vector<int> C;
    comparisons = 0;

    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            comparisons++;
            if (A[i] == B[j]) {
                bool exists = false;
                for (size_t k = 0; k < C.size(); ++k) {
                    comparisons++;
                    if (C[k] == A[i]) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    C.push_back(A[i]);
                }
                break;
            }
        }
    }
    return C;
}

vector<int> Intersect_conversion(vector<int> A, vector<int> B, long long& comparisons) {
    vector<int> C;
    comparisons = 0;

    auto comp = [&comparisons](int a, int b) {
        comparisons++;
        return a < b;
        };

    sort(A.begin(), A.end(), comp);
    sort(B.begin(), B.end(), comp);

    size_t i = 0;
    size_t j = 0;

    while (i < A.size() && j < B.size()) {
        comparisons++;
        if (A[i] == B[j]) {
            if (C.empty() || C.back() != A[i]) {
                C.push_back(A[i]);
            }
            i++;
            j++;
        }
        else {
            comparisons++;
            if (A[i] < B[j]) {
                i++;
            }
            else {
                j++;
            }
        }
    }
    return C;
}

vector<int> inputVector(const string& name, int size) {
    vector<int> vec(size);
    cout << "Enter " << size << " elements for set " << name << ": ";
    for (int i = 0; i < size; ++i) {
        cin >> vec[i];
    }
    return vec;
}

vector<int> generateRandomVector(int size, int maxValue) {
    vector<int> vec(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, maxValue);

    for (int i = 0; i < size; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}

void printVector(const string& name, const vector<int>& vec) {
    cout << name << " (" << vec.size() << " elements): [ ";
    size_t limit = min(vec.size(), (size_t)25);
    for (size_t i = 0; i < limit; ++i) {
        cout << vec[i] << " ";
    }
    if (vec.size() > limit) {
        cout << "...";
    }
    cout << "]\n";
}

void runBruteforceTest(const vector<int>& A, const vector<int>& B) {
    long long comparisons = 0;
    auto start = chrono::high_resolution_clock::now();
    vector<int> C = Intersect_bruteforce(A, B, comparisons);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "\n--- Intersect_bruteforce Results ---\n";
    printVector("Set C (Intersection)", C);
    cout << "Comparisons count: " << comparisons << "\n";
    cout << "Execution time:    " << duration.count() << " ms\n";
}

void runConversionTest(const vector<int>& A, const vector<int>& B) {
    long long comparisons = 0;
    auto start = chrono::high_resolution_clock::now();
    vector<int> C = Intersect_conversion(A, B, comparisons);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "\n--- Intersect_conversion Results ---\n";
    printVector("Set C (Intersection)", C);
    cout << "Comparisons count: " << comparisons << "\n";
    cout << "Execution time:    " << duration.count() << " ms\n";
}

int main() {
    int choice = 0;
    cout << "Select input mode:\n";
    cout << "1 - Manual input\n";
    cout << "2 - Random generation\n";
    cout << "Choice: ";
    cin >> choice;

    vector<int> A;
    vector<int> B;

    if (choice == 1) {
        int n = 0;
        int m = 0;
        cout << "Enter size of set A: ";
        cin >> n;
        A = inputVector("A", n);

        cout << "Enter size of set B: ";
        cin >> m;
        B = inputVector("B", m);
    }
    else {
        int n = 0;
        cout << "Enter size for both sets A and B: ";
        cin >> n;
        A = generateRandomVector(n, n * 2);
        B = generateRandomVector(n, n * 2);
        cout << "Sets successfully generated.\n";
    }

    if (A.size() <= 30 && B.size() <= 30) {
        printVector("Set A", A);
        printVector("Set B", B);
    }

    runBruteforceTest(A, B);
    runConversionTest(A, B);

    return 0;
}