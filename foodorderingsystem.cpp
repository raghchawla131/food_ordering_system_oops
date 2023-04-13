#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;

class item
{
    public:
    string name;
    int price; 
    static pair<string, int> menuPair;

    item(string n, int p)
    {
        name = n;
        price = p;
        menuPair = make_pair(n, p);
    }
};
pair<string,int> item::menuPair; //agar class mai koi function static ho then aise bhi likhana hota hai "codearchery - yt"

class menu : public item //inheritance
{
    public:
    
    static void ShowMenu()
    {
        fstream menuFile;
        menuFile.open("menu.txt", ios::in);
        if(menuFile.is_open())
        {
            string itemName, tempStr;
            int itemPrice;
            string line;
            while(getline(menuFile, line))
            {
                stringstream ss(line); //aache se seekhna hai
                getline(ss, itemName, ',');
                getline(ss, tempStr, ',');
                itemPrice = stoi(tempStr);
                cout << itemName << " = $" << itemPrice << "\n";
            }
            menuFile.close();
        }
    }

    static void AddToMenu()
    {
        fstream menuFile;
        menuFile.open("menu.txt", ios::app);
        if(menuFile.is_open())
        {
            menuFile << menuPair.first << "," << menuPair.second << "\n";
            menuFile.close();
        }
    }
};

class order
{
    public:
    unordered_map<string, int> mp_NameAndPrice;
    vector<string> userOrder;
    unordered_map<string, int> mp_foodQuantity;
    int totalOrderPrice;

    void SelectItemsFromMenu()
    {
        fstream menuFile;
        menuFile.open("menu.txt", ios::in);
        if(menuFile.is_open())
        {
            string tempStr, itemName;
            int itemPrice;
            string line;
            while(getline(menuFile, line))
            {
                stringstream ss(line);
                getline(ss, itemName, ',');
                getline(ss, tempStr, ',');
                itemPrice = stoi(tempStr);
                mp_NameAndPrice[itemName] = itemPrice; // mapping food items to their prices
            }
            menuFile.close();
        }
    }

    void OrderedFoodItems()
    {
        string a;
        while(cin >> a) //ctrl + z se exit hoga loop i.e. end of line(eof) 
        {
            userOrder.push_back(a);
        } 
    }

    void bill()
    {
        totalOrderPrice=0;
        for(auto it : userOrder)
        {
            mp_foodQuantity[it]++;
            if(mp_NameAndPrice.find(it)!=mp_NameAndPrice.end())
            {
                totalOrderPrice += mp_NameAndPrice[it];
            }
        }
        cout << "Your order is: \n"; 
        for(auto it : mp_foodQuantity)
        {
            cout << it.second << "   " << it.first << "\n";
        }
        cout << "Cash to pay: $" << totalOrderPrice << "\n";
        cout << "\n\nTHANKYOU FOR VISITING US :)";
    }

    void updateOrderHistory()
    {
        fstream orderHistoryFile;
        orderHistoryFile.open("orderHistory.txt", ios::app);
        if(orderHistoryFile.good())
        {
            for(int i=0; i<userOrder.size(); i++)
            {
                orderHistoryFile << userOrder[i] << ", ";
            }
            orderHistoryFile << totalOrderPrice << "\n";
        }
    }
};  

void showRecords()
{
    fstream orderHistoryFile;
    orderHistoryFile.open("orderHistory.txt", ios::in);
    if(orderHistoryFile.good())
    {
        string line;
        while(getline(orderHistoryFile, line))
        {
            cout << line << "\n";
        }

    }
}

auto UserWindow()
{
    menu::ShowMenu();
    int choice;
    cout << "Press 1 to order you food & ctrl+z when you finished ordering : ";
    cin >> choice;
    if(choice==1)
    {
        order obj;
        obj.SelectItemsFromMenu();
        obj.OrderedFoodItems();
        obj.bill();
        obj.updateOrderHistory();
    }
}

auto OwnerWindow()
{
    string m_food;
    int ownerChoice, m_price;
    cout << "Press 1 to update the menu. \n";
    cout << "Press 2 to show order history. \n";
    cin >> ownerChoice;
    if(ownerChoice==1)
    {
        cout << "Enter the food name : ";
        cin.ignore();
        getline(cin, m_food);
        cout << "Enter it's price : ";
        cin >> m_price;
        item obj(m_food, m_price);
        menu::AddToMenu();
    }
    if(ownerChoice==2)
    {
        system("cls");
        showRecords();
    }
}

int main()
{
    int choice, ownerChoice;
    cout << "Press 1 to show the menu.\n";
    cout << "Press 2 if you are the owner.\n";
    cin >> choice;
    system("cls");
    if(choice==1)
    {
        UserWindow(); //abstraction
    }
    if(choice==2)
    {
        OwnerWindow(); //abstraction
        return main();
    }
}
