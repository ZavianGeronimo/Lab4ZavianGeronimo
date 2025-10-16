
/**
 * Temperature Bar Chart Program
 * Displays hourly temperatures as a horizontal bar chart with zero-centered scale
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

const int MIN_TEMP = -30;
const int MAX_TEMP = 120;
const int DEGREES_PER_STAR = 3;

bool readTemperatures(const string& filename, vector<int>& temperatures);
bool isValidTemperature(int temp);
void displayChart(const vector<int>& temperatures);
void displayHeader();
void displayBar(int temp);

int main() {
    vector<int> temperatures;
    string filename;
    
    cout << "=================================================\n";
    cout << "        HOURLY TEMPERATURE BAR CHART\n";
    cout << "=================================================\n\n";
    
    cout << "Enter the name of the temperature data file: ";
    getline(cin, filename);
    
    if (!readTemperatures(filename, temperatures)) {
        cerr << "Error: Unable to process temperature data.\n";
        return 1;
    }
    
    if (temperatures.empty()) {
        cerr << "Error: No valid temperature data found in file.\n";
        return 1;
    }
    
    cout << "\n";
    displayChart(temperatures);
    
    cout << "\n=================================================\n";
    cout << "Total hours recorded: " << temperatures.size() << "\n";
    cout << "=================================================\n";
    
    return 0;
}

bool readTemperatures(const string& filename, vector<int>& temperatures) {
    ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'\n";
        return false;
    }
    
    int temp;
    int lineNumber = 0;
    
    while (inputFile >> temp) {
        lineNumber++;
        if (isValidTemperature(temp)) {
            temperatures.push_back(temp);
        } else {
            cerr << "Warning: Invalid temperature " << temp 
                 << " on line " << lineNumber << " (ignored)\n";
        }
    }
    
    inputFile.close();
    return true;
}

bool isValidTemperature(int temp) {
    return (temp >= MIN_TEMP && temp <= MAX_TEMP);
}

void displayChart(const vector<int>& temperatures) {
    displayHeader();
    
    for (size_t i = 0; i < temperatures.size(); i++) {
        cout << "Hour " << setw(2) << (i + 1) << " | ";
        displayBar(temperatures[i]);
    }
}

void displayHeader() {
    cout << "Temperature Bar Chart\n";
    cout << "Scale: Each * represents " << DEGREES_PER_STAR << " degrees Fahrenheit\n";
    cout << "Range: " << MIN_TEMP << "°F to " << MAX_TEMP << "°F\n";
    cout << "------------------------------------------------------------------------\n";
    
    // Display scale markers
    cout << "        ||";
    for (int temp = MIN_TEMP; temp <= MAX_TEMP; temp += 15) {
        if (temp == MIN_TEMP) {
            cout << setw(4) << temp;
        } else {
            cout << setw(5) << temp;
        }
    }
    cout << "\n------------------------------------------------------------------------\n";
}

void displayBar(int temp) {
    // Calculate stars needed from zero point
    int starsFromZero = abs(temp) / DEGREES_PER_STAR;
    
    // Calculate position of zero line (how far from -30)
    int zeroPosition = abs(MIN_TEMP) / DEGREES_PER_STAR;
    
    cout << setw(4) << temp << "°F |";
    
    if (temp < 0) {
        // Negative: spaces, then stars ending at zero
        int spaces = zeroPosition - starsFromZero;
        for (int i = 0; i < spaces; i++) {
            cout << " ";
        }
        for (int i = 0; i < starsFromZero; i++) {
            cout << "*";
        }
        cout << "|";
    } else if (temp == 0) {
        // Zero: just the line
        for (int i = 0; i < zeroPosition; i++) {
            cout << " ";
        }
        cout << "|";
    } else {
        // Positive: spaces to zero, line, then stars
        for (int i = 0; i < zeroPosition; i++) {
            cout << " ";
        }
        cout << "|";
        for (int i = 0; i < starsFromZero; i++) {
            cout << "*";
        }
    }
    
    cout << "\n";
}