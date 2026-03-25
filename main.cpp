#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Expense {        //grouping related variables under "Expense"
    string date;
    string category;
    string description;
    double amount;
};

void saveExpenses(const vector<Expense>& expenses) {
    ofstream f("expenses.csv");     //opens file for writing
    for (const auto& a : expenses) {
        f << a.date << ',' 
          << a.category << ','
          << a.description << ','
          << a.amount << endl;
    }
}

vector<Expense> loadExpenses() {
    vector<Expense> expenses;
    ifstream f("expenses.csv");     //opens file for reading

    if (!f.is_open()) {
        return expenses;
    }

    string line;
    
    while (getline(f, line)) {
        istringstream ss(line);     //turns one line of csv into a stream 
        Expense a;                  //and be able to split it apart to read
        string amount;

        getline(ss, a.date, ',');
        getline(ss, a.category, ',');
        getline(ss, a.description, ',');
        getline(ss, amount, ',');

        try {
            a.amount = stod(amount);
        } catch (...) {     //catch any error (like forcing "abc" with "stod" into a number would crash)
            continue;       //skip current expense, move on to next line
        }

        expenses.push_back(a);
    }

    return expenses;
}

void addExpense(vector<Expense>& expenses) {
    Expense a;

    cout << "\nDate (YYYY-MM-DD): ";
    getline(cin, a.date);

    cout << "Category (Food/Transport/Bills/Shopping/Groceries/Other): ";
    getline(cin, a.category);

    cout << "Description: ";
    getline(cin, a.description);

    cout << "Amount ($): ";
    string amount;
    getline(cin, amount);
    a.amount = stod(amount);        //convert type string -> double
    
    expenses.push_back(a);          //creates the whole list
    saveExpenses(expenses);
    cout << "Expense Saved." << endl;
}

vector<Expense> printExpenses(const vector<Expense>& expenses) {
    vector<Expense> sorted = expenses;
    sort(sorted.begin(), sorted.end(), [](const Expense& a, const Expense& b) {
        return a.date < b.date;
    });

    cout << "\n";
    cout << left
         << setw(5) << "#"
         << setw(13) << "Date"
         << setw(14) << "Category"
         << setw(22) << "Description"
         << right
         << setw(9) << "Amount" << endl;

    cout << string(70, '-') << endl;

    double total = 0.0;

    for (int i = 0; i < (int)sorted.size(); i++) {
        const auto& a = sorted[i];
        cout << left
             << setw(5) << i + 1
             << setw(13) << a.date
             << setw(14) << a.category
             << setw(22) << a.description
             << right 
             << fixed
             << setprecision(2)
             << setw(4) << '$' << a.amount << endl;
        
        total += a.amount;
    }

    cout << string(70, '-') << endl;
    cout << right << setw(58) << "Total: $"
         << fixed << setprecision(2) << total << endl;

    return sorted;
}

void listExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo Expenses Yet." << endl;
        return;
    }

    auto sorted = printExpenses(expenses);

    //filtering menu 
    cout << "\nFilter? " << endl;
    cout << "1. Month" << endl;
    cout << "2. Date After..." << endl;
    cout << "3. Date Before..." << endl;
    cout << "4. Date Between..." << endl;
    cout << "5. Exit" << endl;
    cout << "Selection: ";

    string selection;
    getline(cin, selection);

    if (selection == "1") {
        cout << "Filter by month: (YYYY-MM or press Enter to skip): ";
        string month;
        getline(cin, month);

        if(!month.empty()) {
            vector<Expense> filtered;
            for (const auto& a : expenses) {
                if (a.date.substr(0, 7) == month) {
                    filtered.push_back(a);
                }
            }
            
            if (filtered.empty()) {
                cout << "No Expenses Found for " << month << "." << endl;
                return;
            }

            cout << "\n--- Filtered: " << month << "---\n";
            printExpenses(filtered);
        }
             
    } else if (selection == "2") {
        return;
    } else if (selection == "3") {
        return;
    } else if (selection == "4") {
        return;
    } else if (selection == "5") {
        return;
    }
}

void summaryByCategory(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No Expenses Yet." << endl;
        return;
    }

    vector<string> lists;

    for (const auto& a : expenses) {
        if (find(lists.begin(), lists.end(), a.category) == lists.end()) {      //category matching
            lists.push_back(a.category);
        }
    }

    cout << "\n";
    cout << string(35, '-') << '\n';
    double grand = 0.0;

    for (const auto& list : lists) {
        double sum = 0.0;
        for (const auto& a : expenses) {
            if (a.category == list) {
                sum += a.amount;
            }
        }
        cout << left << setw(20) << list
             << right << "$" << fixed << setprecision(2) << sum << endl;
        grand += sum;
    }

    cout << string(35, '-') << endl;
    cout << left << setw(20) << "Total: "
         << right << "$" << fixed << setprecision(2) << grand << endl;
}

void deleteExpense(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\n";
        cout << "No Expenses to Delete." << endl;
        return;
    }

    vector<Expense> sorted = printExpenses(expenses);

    cout << "\n";
    cout << "Row Number to Delete (1 to " << sorted.size() << "): ";
    string input;
    getline(cin, input);

    try {
        int i = stoi(input) - 1;
        if (i < 0 || i >= (int)sorted.size()) {
            cout << "Invalid Number" << endl;
            return;
        }

        Expense toDelete = sorted[i];
        for (int j = 0; j < (int)expenses.size(); j++ ){
            if (expenses[j].date == toDelete.date &&
                expenses[j].category == toDelete.category &&
                expenses[j].description == toDelete.description &&
                expenses[j].amount == toDelete.amount) {
                    expenses.erase(expenses.begin() + j);
                    break;
                }
        }

        saveExpenses(expenses);
        cout << "Expense Deleted" << endl;
    } catch (...) {
        cout << "Invalid Input." << endl;
    }
}

void searchExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\n";
        cout << "No Expenses yet." << endl;
        return;
    }

    cout << "\n";
    cout << "Enter Keyword: ";
    string keyword;
    getline(cin, keyword);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    vector<Expense> results;
    for (const auto& a : expenses) {
        string desc = a.description;
        transform(desc.begin(), desc.end(), desc.begin(), ::tolower);

        string cate = a.category;
        transform(cate.begin(), cate.end(), cate.begin(), ::tolower);

        if (desc.find(keyword) != string::npos || cate.find(keyword) != string::npos) {
            results.push_back(a);
        }
    }

    if (results.empty()) {
        cout << "No Matches." << endl;
    } else {
        printExpenses(results);
    }
}

int main() {
    vector<Expense> expenses = loadExpenses();

    while (true) {
        cout << "\n1. Add Expense" << endl;
        cout << "2. List Expenses" << endl;
        cout << "3. Summary By Category" << endl;
        cout << "4. Search Expense" << endl;
        cout << "5. Delete Expense" << endl;
        cout << "6. Quit" << endl;
        cout << "Selection: ";

        string selection;
        getline(cin, selection);

        if (selection == "1") {
            addExpense(expenses);
        } else if (selection == "2") {
            listExpenses(expenses);
        } else if (selection == "3") {
            summaryByCategory(expenses);
        } else if (selection == "4") {
            searchExpenses(expenses);
        } else if (selection == "5") {
            deleteExpense(expenses);
        } else if (selection == "6") {
            cout << "\n";
            cout << "Goodbye!\n" << endl;
            break;
        } else {
            cout << "coming soon." << endl;
        }
    }

    return 0;
}