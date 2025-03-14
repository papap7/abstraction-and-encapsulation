#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Product {
public:
    int productId;
    string productName;
    float unitPrice;
    Product(int id, string name, float price) : productId(id), productName(name), unitPrice(price) {}
};

class ShoppingCart {
public:
    vector<pair<Product, int>> cartItems; // Pair of Product and Quantity
    void addCartItem(Product product) {
        for (auto &item : cartItems) {
            if (item.first.productId == product.productId) {
                item.second++; // Increase quantity if product already in cart
                return;
            }
        }
        cartItems.push_back(make_pair(product, 1));
    }
    void viewCart() {
        if (cartItems.empty()) {
            cout << "\nShopping Cart is empty.\n";
            return;
        }
        cout << "\nShopping Cart:\n";
        cout << left << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (auto &item : cartItems) {
            cout << left << setw(10) << item.first.productId << setw(20) << item.first.productName << setw(10) << item.first.unitPrice << item.second << endl;
        }
    }
    float calculateTotal() {
        float total = 0;
        for (auto &item : cartItems) {
            total += item.first.unitPrice * item.second;
        }
        return total;
    }
};

class Payment {
public:
    static bool processPayment(float amount) {
        cout << "\nProcessing payment of PHP " << amount << "...";
        cout << "\nPayment successful!\n";
        return true;
    }
};

class Shipment {
public:
    static void dispatchShipment() {
        cout << "\nOrder has been dispatched for shipment.\n";
    }
};

class Order {
public:
    vector<pair<Product, int>> orderedItems;
    float totalAmount;
    Order(vector<pair<Product, int>> items, float total) : orderedItems(items), totalAmount(total) {}
    void viewOrderDetails() {
        cout << "\nOrder Summary:\n";
        cout << left << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (auto &item : orderedItems) {
            cout << left << setw(10) << item.first.productId << setw(20) << item.first.productName << setw(10) << item.first.unitPrice << item.second << endl;
        }
        cout << "Total Amount: " << totalAmount << "\n";
    }
};

vector<Product> products = {
    Product(1, "Laptop", 50000.0),
    Product(2, "Mouse", 800.0),
    Product(3, "Keyboard", 1500.0),
    Product(4, "Monitor", 7000.0)
};

void viewProducts() {
    cout << "\nAvailable Products:\n";
    cout << left << setw(10) << "Product ID" << setw(20) << "Name" << "Price" << endl;
    for (auto &product : products) {
        cout << left << setw(10) << product.productId << setw(20) << product.productName << product.unitPrice << endl;
    }
}

int main() {
    ShoppingCart cart;
    vector<Order> orders;
    int choice;
    do {
        cout << "\nMenu:\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            viewProducts();
            int id;
            char cont;
            do {
                cout << "Enter the ID of the product you want to add to the shopping cart: ";
                cin >> id;
                bool found = false;
                for (auto &product : products) {
                    if (product.productId == id) {
                        cart.addCartItem(product);
                        cout << "Product added successfully!\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid Product ID!\n";
                cout << "Do you want to add another product? (Y/N): ";
                cin >> cont;
            } while (cont == 'Y' || cont == 'y');
            break;
        }
        case 2: {
            cart.viewCart();
            if (!cart.cartItems.empty()) {
                char checkout;
                cout << "Do you want to check out all the products? (Y/N): ";
                cin >> checkout;
                if (checkout == 'Y' || checkout == 'y') {
                    float total = cart.calculateTotal();
                    if (Payment::processPayment(total)) {
                        orders.push_back(Order(cart.cartItems, total));
                        cart.cartItems.clear();
                        Shipment::dispatchShipment();
                        cout << "You have successfully checked out the products!\n";
                    }
                }
            }
            break;
        }
        case 3: {
            if (orders.empty()) {
                cout << "\nNo orders available.\n";
            } else {
                for (auto &order : orders) {
                    order.viewOrderDetails();
                }
            }
            break;
        }
        case 4:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    return 0;
}