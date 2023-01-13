#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream in("day1.txt");
    vector<int> values;
    int val;
    while (in >> val) {
        values.push_back(val);
    }

    // Part 1
    int last = 0;
    int count = -1; // First value parsed will make count 0
    for (vector<int>::iterator it = values.begin(); it != values.end(); it++) {
        if (*it > last) {
            count += 1;
        }
        last = *it;
    }

    // Part 2
    int last2 = 0;
    int count2 = -1;
    for (int index = 0; index < values.size(); index++) {
        if (index + 2 >= values.size()) {
            break;
        }

        int sum = values[index] + values[index+1] + values[index+2];
        if (sum > last2) {
            count2 += 1;            
        }

        last2 = sum;
    }

    cout << count << "\n";
    cout << count2 << "\n";

    return 0;
}
