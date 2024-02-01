#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>

using namespace std;

// Define a simple structure for a clothing item
struct ClothingItem {
    string name;
    string type;
    double price;
};

// Function to display the menu
void displayMenu() {
    cout << "===== Clothing Shop Menu =====" << endl;
    cout << "1. View Items" << endl;
    cout << "2. Add Item" << endl;
    cout << "3. Remove Item" << endl;
    cout << "4. Exit" << endl;
    cout << "==============================" << endl;
}

// Function to display all items in the shop
void viewItems(const vector<ClothingItem>& items) {
    cout << "===== Clothing Items =====" << endl;
    cout << setw(20) << left << "Item Name" << setw(15) << "Item Type" << setw(10) << right << "Price" << endl;
    cout << "--------------------------------------" << endl;

    for (const ClothingItem& item : items) {
        cout << setw(20) << left << item.name << setw(15) << item.type << fixed << setprecision(2) << setw(10) << right << item.price << endl;
    }

    cout << "======================================" << endl;
}

// Function to add a new item to the shop with a random price
void addItem(vector<ClothingItem>& items) {
    ClothingItem newItem;

    cout << "Enter the name of the item: ";
    getline(cin, newItem.name);

    cout << "Enter the type of the item (e.g., T-shirt, trousers, shoes, costume): ";
    getline(cin, newItem.type);

    // Generate a random price between 10.00 and 100.00
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(10.0, 100.0);
    newItem.price = dis(gen);

    items.push_back(newItem);

    cout << "Item added successfully!" << endl;
}

// Function to remove an item from the shop
void removeItem(vector<ClothingItem>& items) {
    string itemName;

    cout << "Enter the name of the item to remove: ";
    getline(cin, itemName);

    // Search for the item in the vector
    auto it = find_if(items.begin(), items.end(), [itemName](const ClothingItem& item) {
        return item.name == itemName;
    });

    if (it != items.end()) {
        items.erase(it);
        cout << "Item removed successfully!" << endl;
    } else {
        cout << "Item not found in the shop." << endl;
    }
}

// Function to load items from a file
void loadItemsFromFile(vector<ClothingItem>& items) {
    ifstream inputFile("menu.txt");

    if (!inputFile) {
        cerr << "Error opening menu.txt. Creating a new file." << endl;
        return;
    }

    items.clear();  // Clear existing items

    ClothingItem newItem;
    while (inputFile >> newItem.name >> newItem.type >> newItem.price) {
        items.push_back(newItem);
    }

    inputFile.close();
}

// Function to save items to a file
void saveItemsToFile(const vector<ClothingItem>& items) {
    ofstream outputFile("menu.txt");

    if (!outputFile) {
        cerr << "Error opening menu.txt for writing." << endl;
        return;
    }

    for (const ClothingItem& item : items) {
        outputFile << item.name << " " << item.type << " " << fixed << setprecision(2) << item.price << endl;
    }

    outputFile.close();
}

int main() {
    vector<ClothingItem> clothingShop;

    // Load items from the file at the beginning
    loadItemsFromFile(clothingShop);

    int choice;

    do {
        displayMenu();

        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore();  // Clear the input buffer

        switch (choice) {
            case 1:
                viewItems(clothingShop);
                break;
            case 2:
                addItem(clothingShop);
                break;
            case 3:
                removeItem(clothingShop);
                break;
            case 4:
                cout << "Exiting the program. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }

    } while (choice != 4);

    // Save items to the file before exiting
    saveItemsToFile(clothingShop);

    return 0;
}