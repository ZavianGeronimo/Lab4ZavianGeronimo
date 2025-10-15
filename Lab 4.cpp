
#include <iostream> //Input/Output Stream - for cout and cin
#include <fstream> //File Stream - for reading files 
#include <iomanip> //Input/Output Manipulators  - for formating
#include <string> // For working with text 
#include <vector> // For creating resisable lines

using namespace std;

// Constants
const int MIN_TEMP = -30;
const int MAX_TEMP = 120;
const int DEGREES_PER_STAR = 3;
const int MAX_STARS = 50;

// Function prototypes
bool readTemperatures(const string& filename, vector<int>& temperatures);
bool isValidTemperature(int temp);
void displayChart(const vector<int>& temperatures);
void displayHeader();
void displayBar(int temp);
int calculateStars(int temp);

/**
 * Main function
 * Precondition: None
 * Postcondition: Temperature bar chart is displayed on screen
 */
int main() {
    vector<int> temperatures;
    string filename;
    
    cout << "=================================================\n";
    cout << "        HOURLY TEMPERATURE BAR CHART\n";
    cout << "=================================================\n\n";
    
    // Get filename from user
    cout << "Enter the name of the temperature data file: ";
    getline(cin, filename);
    
    // Read temperatures from file
    if (!readTemperatures(filename, temperatures)) {
        cerr << "Error: Unable to process temperature data.\n";
        cerr << "Please check that the file exists and contains valid data.\n";
        return 1;
    }
    
    // Check if any temperatures were read
    if (temperatures.empty()) {
        cerr << "Error: No valid temperature data found in file.\n";
        return 1;
    }
    
    // Display the bar chart
    cout << "\n";
    displayChart(temperatures);
    
    cout << "\n=================================================\n";
    cout << "Total hours recorded: " << temperatures.size() << "\n";
    cout << "=================================================\n";
    
    return 0;
}

/**
 * Reads temperature values from a file
 * Precondition: filename is a valid string
 */
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
            cerr << "         Valid range is " << MIN_TEMP 
                 << " to " << MAX_TEMP << " degrees.\n";
        }
    }
    
    inputFile.close();
    return true;
}

/**
 * Validates if a temperature is within acceptable range
 */
bool isValidTemperature(int temp) {
    return (temp >= MIN_TEMP && temp <= MAX_TEMP);
}

/**
 * Displays the complete temperature bar chart with header

 */
void displayChart(const vector<int>& temperatures) {
    displayHeader();
    
    for (size_t i = 0; i < temperatures.size(); i++) {
        cout << "Hour " << setw(2) << (i + 1) << " | ";
        displayBar(temperatures[i]);
    }
}

/**
 * Displays the chart header with scale information
 */
void displayHeader() {
    cout << "Temperature Bar Chart\n";
    cout << "Scale: Each * represents " << DEGREES_PER_STAR << " degrees Fahrenheit\n";
    cout << "Range: " << MIN_TEMP << "°F to " << MAX_TEMP << "°F\n";
    cout << "-------------------------------------------------\n";
    cout << "        |";
    
    // Display scale markers
    for (int i = 0; i <= MAX_STARS; i += 10) {
        if (i == 0) {
            cout << "|";
        } else {
            cout << setw(10) << "|";
        }
    }
    cout << "\n";
    
    cout << "        |";
    for (int i = 0; i <= MAX_STARS; i += 10) {
        int temp = MIN_TEMP + (i * DEGREES_PER_STAR);
        if (i == 0) {
            cout << setw(1) << temp;
        } else {
            cout << setw(10) << temp;
        }
    }
    cout << "\n-------------------------------------------------\n";
}

 // Displays a single bar for a given temperature
 
void displayBar(int temp) {
    int stars = calculateStars(temp);
    
    // Display temperature value
    cout << setw(4) << temp << "°F |";
    
    // Display the bar of stars
    for (int i = 0; i < stars; i++) {
        cout << "*";
    }
    
    cout << "\n";
}


 // Calculates the number of stars to display for a temperature
 
int calculateStars(int temp) {
    // Adjust temperature to start from 0
    int adjustedTemp = temp - MIN_TEMP;
    
    // Calculate number of stars (round to nearest integer)
    int stars = (adjustedTemp + DEGREES_PER_STAR / 2) / DEGREES_PER_STAR;
    
    // Ensure stars is within valid range
    if (stars < 0) stars = 0;
    if (stars > MAX_STARS) stars = MAX_STARS;
    
    return stars;
}
