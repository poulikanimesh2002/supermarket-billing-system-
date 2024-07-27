#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Item {
public:
    string name;
    double price;
    int quantity;

    Item(string itemName, double itemPrice, int itemQuantity) {
        name = itemName;
        price = itemPrice;
        quantity = itemQuantity;
    }
};

class Supermarket {
private:
    vector<Item> inventory;
    vector<Item> cart;

public:
    // Function to insert items into inventory
    void insertItem(const string& name, double price, int quantity) {
        inventory.emplace_back(name, price, quantity);
        cout << "Item inserted successfully.\n";
    }

    // Function to buy items and add them to cart
    void buyItem(const string& name, int quantity) {
        for (auto& item : inventory) {
            if (item.name == name) {
                if (item.quantity >= quantity) {
                    cart.emplace_back(name, item.price, quantity);
                    item.quantity -= quantity;
                    cout << "Item added to cart.\n";
                } else {
                    cout << "Insufficient stock.\n";
                }
                return;
            }
        }
        cout << "Item not found.\n";
    }

    // Function to show items in the cart
    void showCart() const {
        if (cart.empty()) {
            cout << "Cart is empty.\n";
        } else {
            cout << "Items in the cart:\n";
            for (const auto& item : cart) {
                cout << "Name: " << item.name << ", Price: " << item.price << ", Quantity: " << item.quantity << endl;
            }
        }
    }

    // Function to generate bill
    void generateBill() const {
        if (cart.empty()) {
            cout << "Cart is empty. No bill to generate.\n";
            return;
        }

        double totalAmount = 0;
        cout << "\nBill:\n";
        cout << left << setw(15) << "Item" << setw(10) << "Price" << setw(10) << "Quantity" << setw(10) << "Total" << endl;
        for (const auto& item : cart) {
            double itemTotal = item.price * item.quantity;
            cout << left << setw(15) << item.name << setw(10) << item.price << setw(10) << item.quantity << setw(10) << itemTotal << endl;
            totalAmount += itemTotal;
        }

        double discount = 0;
        const double discountThreshold = 100.0; // Discount threshold
        const double discountRate = 0.1; // 10% discount
        if (totalAmount > discountThreshold) {
            discount = totalAmount * discountRate;
            totalAmount -= discount;
        }

        cout << "Discount: " << discount << endl;
        cout << "Total Amount: " << totalAmount << endl;
    }
};

int main() {
    Supermarket supermarket;
    int choice;

    do {
        cout << "\nSupermarket Billing System Menu:\n";
        cout << "1. Insert Items\n";
        cout << "2. Buy Items\n";
        cout << "3. Show Items in the Cart\n";
        cout << "4. Generate Bill\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double price;
                int quantity;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item price: ";
                cin >> price;
                cout << "Enter item quantity: ";
                cin >> quantity;
                supermarket.insertItem(name, price, quantity);
                break;
            }
            case 2: {
                string name;
                int quantity;
                cout << "Enter item name to buy: ";
                cin >> name;
                cout << "Enter quantity to buy: ";
                cin >> quantity;
                supermarket.buyItem(name, quantity);
                break;
            }
            case 3: {
                supermarket.showCart();
                break;
            }
            case 4: {
                supermarket.generateBill();
                break;
            }
            case 5: {
                cout << "Exiting the program.\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 5);

    return 0;
}
