#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// TODO: Do file processing manually
int main() {
    ifstream in("day2.txt");
    int pos = 0, depth = 0, aim = 0;
    string dir;
    int val;
    while (in >> dir >> val) {
        if (dir == "forward") {
            pos += val;
            depth += aim * val;
        } else if (dir == "up") {
            aim -= val;
        } else if (dir == "down") {
            aim += val;
        }
    }

    cout << pos * depth << "\n";

    return 0;
}