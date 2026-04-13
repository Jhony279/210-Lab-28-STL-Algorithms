#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Goat.h"
#include <vector>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_OPTIONS = 9;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void sort_trip(list<Goat> &trip);
void reverse_trip(list<Goat> &trip);
void clear_trip(list<Goat> &trip);
void display_trip(list<Goat> trip);
void find_goat(list<Goat> trip);
void count_goats(list<Goat> trip, int age);
void shuffle_trip(list<Goat> &trip);
int main_menu();

int main() {
    srand(time(0));
    bool again = true;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    while (again) {
        int sel = main_menu();
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;

            case 4:
                cout << "Sorting goat by name.\n";
                sort_trip(trip);
                break;

            case 5:
                cout << "Reversing goat order.\n";
                reverse_trip(trip);
                break;

            case 6:
                cout << "Clear goat data.\n";
                clear_trip(trip);
                break;

            case 7:
                cout << "Finding a goat.\n";
                find_goat(trip);
                break;

            case 8:
                cout << "Counting goats older than n age.\n";
                int age;
                cout << "Enter age n: ";
                cin >> age;
                count_goats(trip, age);
                break;

            case 9:
                cout << "Shuffling goat order.\n";
                shuffle_trip(trip);
                break;

            case MAX_OPTIONS + 1:
                cout << "Quitting.\n";
                again = false;
                break;

            default:
                cout << "Invalid selection.\n";
                break;
        }
    }
    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by name\n";
    cout << "[5] Reverse goat order\n";
    cout << "[6] Clear goat data\n";
    cout << "[7] Find a goat\n";
    cout << "[8] Goats older than n age\n";
    cout << "[9] Shuffle list\n";
    cout << "[10] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > MAX_OPTIONS) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

// @brief sort the list by name
void sort_trip(list<Goat> &trip) {
    trip.sort();
}

// @brief reverse the list
void reverse_trip(list<Goat>& trip){
    reverse(trip.begin(), trip.end());
}

// @brief clear the list of all goats
void clear_trip(list<Goat> &trip) {
    trip.clear();
}

// @brief find a goat by name and display its data if found
void find_goat(list<Goat> trip) {
    string name;
    cout << "Enter goat name to find: ";
    cin >> name;

    // use find_if and a lambda to search for the goat by name
    auto it = find_if(trip.begin(), trip.end(), [name](const Goat& g) {
        return g.get_name() == name;
    });
    if (it != trip.end()) { // found
        cout << "Goat found: " << it->get_name() 
            << " (" << it->get_age() 
            << ", " << it->get_color() << ")\n";
    } else { // Outside of the trip (no goat found)
        cout << "Goat not found.\n";
    }
}

// @brief count goats older than a certain age and display the count
void count_goats(list<Goat> trip, int age) {
    int count = count_if(trip.begin(), trip.end(), [age](const Goat& g){
        return g.get_age() > age;
    });
    cout << "Number of goats older than " << age << ": " << count << endl;
}

void shuffle_trip(list<Goat> &trip) {
    vector<Goat> temp(trip.begin(), trip.end());

    random_device rd;
    mt19937 g(rd());

    shuffle(temp.begin(), temp.end(), g);
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
            << "[" << i++ << "] "
            << gt.get_name() 
            << " (" << gt.get_age() 
            << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}