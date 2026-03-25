# expense_tracker
mini expense tracker project because apparently im an adult now and i need to learn how to manage my money better

features:
- add expenses with date, category, description, and amount
- list expenses in a formatted table, auto-sorted by date
- filter expense by month
- summarize expenses by category
- search expenses by keyword
- delete expenses by row number
- autosaved data to .csv file

how to run:
- macOS with clang (xcode-select --install)

compile:
- clang++ -std=c++17 -o expense_tracker main.cpp

run: 
- ./expense_tracker


work in progress features:
- filter expenses before/after specific date
- filter expenses in a time period