#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    const int num_students = 5;
    string filename = "scores.txt";

    // Write scores to file
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    for (int i = 0; i < num_students; ++i) {
        double score;
        cout << "Enter score for student " << i + 1 << ": ";
        cin >> score;
        outfile << score << endl;
    }
    outfile.close();

    // Read scores and calculate average
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }

    double total_score = 0.0;
    int count = 0;
    double score;
    while (infile >> score) {
        total_score += score;
        count++;
    }
    infile.close();

    if (count > 0) {
        double average_score = total_score / count;
        cout << fixed << setprecision(2);
        cout << "Average score: " << average_score << endl;
    } else {
        cout << "File is empty. No average to calculate." << endl;
    }

    return 0;
}
