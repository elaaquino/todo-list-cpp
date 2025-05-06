#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void addItem(vector<string>& list);
void removeItem(vector<string>& list);
void replaceItem(vector<string>& list);
void deleteList(map<string, vector<string>>& todoLists);
void displayList(const vector<string>& list, const string& title = "");

bool showFirstMenu(map<string, vector<string>>& todoLists) {
  char userInput;
  string listName;
  
  cout << "Welcome to your To-Do Lists!" << endl;
  cout << "Currently, you have " << todoLists.size() << " lists." << endl;
  cout << "Create your first list? (y/n)" << endl;
  cin >> userInput;
  cin.ignore();
  
  if (userInput == 'y' || userInput == 'Y') {
    cout << "Please enter a name for this list: ";
    getline(cin, listName);
    todoLists[listName] = vector<string>();
    cout << "List '" << listName << "' created!" << endl;
    return true;
  }
  else {
    cout << "Goodbye!" << endl;
    return false;
  }
}

int showMainMenu(map<string, vector<string>>& todoLists) {
  int userInput;
  cout << "------ Main Menu ------" << endl;
  cout << "1. Modify list" << endl;
  cout << "2. View list" << endl;
  cout << "3. Create new list" << endl;
  cout << "4. Delete existing list" << endl;
  cout << "5. Quit" << endl;
  cout << "Please enter a number 1-5: "; 
  cin >> userInput;
  return userInput;
}

vector<string>* chooseList(map<string, vector<string>>& todoLists) {
  if (todoLists.empty()) {
    cout << "You have no lists to modify." << endl;
    return nullptr;
  }

  int userInput;
  cout << "Here are your current lists: " << endl;
  int index = 1;
  for (const auto& pair : todoLists)
    cout << index++ << ". " << pair.first << endl;

  cout << "\nWhch number list would you like to modify? ";
  cin >> userInput;
  cin.ignore();

  if (userInput < 1 || userInput > todoLists.size()) {
    cout << "Invalid list number." << endl;
    return nullptr;
  }

  auto it = todoLists.begin();
  advance(it, userInput - 1);

  return &it->second;
}

void showModifyMenu(map<string, vector<string>>& todoLists) {
  vector<string>* list = chooseList(todoLists);

  if (!list) return;
  
  int userInput;
  do {
    cout << "\n ------ Modify Menu ------" << endl;
    cout << "1. Add item\n2. Remove item\n3. Replace item\n4. Return to main menu\n";
    cout << "Please enter a number 1-4: ";
    cin >> userInput;
    cin.ignore();

    switch(userInput) {
      case 1: addItem(*list); break;
      case 2: removeItem(*list); break;
      case 3: replaceItem(*list); break;
      case 4: cout << "Returning to main menu..." << endl; break;
      default: cout << "Invalid input. Please try again." << endl; break;
    }
  } while (userInput != 4);
}

void addItem(vector<string>& list) {
  string item;
  cout << "Enter item to add: ";
  getline(cin, item);
  list.push_back(item);
  cout << "Item added!" << endl;
}

void removeItem(vector<string>& list) {
  if(list.empty()) {
    cout << "This list is empty, nothing to remove!" << endl;
    return;
  }

  cout << "Here is the list:" << endl;
  displayList(list);

  int indexToRemove;
  cout << "Enter the number of the item to remove: ";
  cin >> indexToRemove;
  cin.ignore();

  if (indexToRemove < 1 || indexToRemove > list.size()) {
    cout << "Invalid item number." << endl;
    return;
  }

  string removedItem = list[indexToRemove - 1];
  list.erase(list.begin() + indexToRemove - 1);
  cout << "Item '" << removedItem << "' removed!" << endl;
}

void replaceItem(vector<string>& list) {
  int oldIndex;
  int index = 1;
  string newItem;
  cout << "Here is your list:" << endl;
  displayList(list);
  cout << "Enter the number of the item to replace: ";
  cin >> oldIndex;
  cin.ignore();

  if (oldIndex < 1 || oldIndex > list.size()) {
    cout << "Invalid item. Returning to modify menu..." << endl;
    return;
  }
  
  cout << "Enter the new item: ";
  getline(cin, newItem);
  list[oldIndex - 1] = newItem;
  cout << "Item replaced! Here's your new list: " << endl;
  index = 1;
  for (const auto& item : list)
    cout << index++ << ". " << item << endl;
  cout << endl;
}

void deleteList(map<string, vector<string>>& todoLists) {
  int listNum;
  cout << "Here are your current lists: " << endl; int index = 1;
  for (const auto& pair : todoLists)
    cout << index++ << ". " << pair.first << endl;
  cout << "Enter the number of the list to delete: ";
  cin >> listNum;

  if (listNum < 1 || listNum > todoLists.size()) {
    cout << "Invalid list number." << endl;
    return;
  }
  
  auto it = todoLists.begin();
  advance(it, listNum - 1);
  todoLists.erase(it);
  cout << "List deleted!" << endl;
  cout << "Returning to main menu..." << endl;
}

bool showViewMenu(map<string, vector<string>>& todoLists) {
  char userInput;
  cout << endl << "------ View Menu ------" << endl;

  for(const auto&pair : todoLists) {
    displayList(pair.second, pair.first);
  }

  cout << "Return to main menu? (y/n): ";
  cin >> userInput;

  return (userInput == 'y' || userInput == 'Y');
}

void displayList(const vector<string>& list, const string& title) {
    if (!title.empty()) {
        cout << "\n--- " << title << " ---" << endl;
    }

    if (list.empty()) {
        cout << "This list is empty." << endl;
        return;
    }

    for (size_t i = 0; i < list.size(); ++i) {
        cout << i + 1 << ". " << list[i] << endl;
    }
    cout << endl;
}

int main() {
  map<string, vector<string>> todoLists;

  if (!showFirstMenu(todoLists)) return 0;

  int userInput;
  do {
    userInput = showMainMenu(todoLists);
    switch (userInput) {
      case 1: showModifyMenu(todoLists); break;
      case 2: while(!showViewMenu(todoLists)); break; // loop until user wants to return to main menu)
      case 3: {
        string newListName;
        cin.ignore();
        cout << "Enter a name for the new list: ";
        getline(cin, newListName);
        if(todoLists.count(newListName)) {
          cout << "A list with this name already exists." << endl;
        } else {
            todoLists[newListName] = vector<string>();
            cout << "List '" << newListName << "' created!" << endl;
            break;
        }
      }
      case 4: deleteList(todoLists); break;
      case 5: cout << "Goodbye!" << endl; break;
      default: cout << "Invalid input. Please try again." << endl; break;
    }
  } while (userInput != 5);

  return 0;
}
