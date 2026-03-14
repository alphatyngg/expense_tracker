#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Expense {        //grouping related variables under "Expense"
    string date;
    string category;
    string description;
    double amount;
};

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
    cout << "Expense Saved." << endl;
}

void listExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo Expenses Yet." << endl;
        return;
    }

    cout << "\n";
    cout << left
         << setw(13) << "Date"
         << setw(14) << "Category"
         << setw(22) << "Description"
         << right
         << setw(9) << "Amount" << endl;

    cout << string(60, '-') << endl;

    double total = 0;

    for (const auto& a : expenses) {
        cout << left
             << setw(13) << a.date
             << setw(14) << a.category
             << setw(22) << a.description
             << right 
             << fixed
             << setprecision(2)
             << setw(4) << '$' << a.amount << endl;
        
        total += a.amount;
    }
    cout << string(60, '-') << endl;
    cout << right << setw(53) << "Total: $"
         << fixed << setprecision(2) << total << endl;
}

int main() {
    vector<Expense> expenses;

    while (true) {
        cout << "\n1. Add Expense" << endl;
        cout << "2. List Expenses" << endl;
        cout << "3. Quit" << endl;
        cout << "Selection: ";

        string selection;
        getline(cin, selection);

        if (selection == "1") {
            addExpense(expenses);
        } else if (selection == "2") {
            listExpenses(expenses);
        } else if (selection == "3") {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "work in progress..." << endl;
        }
    }

    return 0;
}