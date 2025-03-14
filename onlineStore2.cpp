#include <iostream>
#include <unordered_map>
#include <regex>
#include <limits>
#include <memory>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

class ShoppingCart;

class Customer {
    private:
    int customerId;
    string customerName, address, email, password, phoneNumber;
    shared_ptr<ShoppingCart> cart;

    // Static members
    static unordered_map<int, shared_ptr<Customer>> customerMap;
    static unordered_map<string, int> emailToCustomerId;
    static int nextCustomerId;

    // Function to check input validity using regex
    static bool isValidInput(const string& input, const string& pattern) {
        if(input.empty()) {
            cout << "Input cannot be empty! Please enter a valid value. \n";
            return false;
        }
        return regex_match(input, regex(pattern));
    }

    // Get and validate input in one function
    static string getValidatedInput(const string& prompt, const string& pattern, const string& errorMessage) {
        string input;
        bool valid;
        do {
            cout << prompt;
            getline(cin, input);
            valid = isValidInput(input, pattern);
            if (!valid) {
                cout << errorMessage << endl;
            }
        } while (!valid);
        return input;
    }

    public:
    Customer(int customerId, string customerName, string address, string email, string password, string phoneNumber)
    : customerId(customerId), customerName(customerName), address(address), email(email), password(password), phoneNumber(phoneNumber) {
        cart = make_shared<ShoppingCart>(); // Create cart
;    }
     
    // Getters
    int getCustomerId() const { return customerId; }
    string getPassword() const { return password; }
    string getEmail() const { return email; }
    shared_ptr<ShoppingCart> getCart() const { return cart; }

    // Display customer info
    void displayCustomerInfo() const {
        cout << "Customer ID: " << customerId << "\nName: " << customerName << "Email: " << email << endl;
    }

    // Register a new customer
    static void registerCustomer() {
        cout << " - - - - - - - - - - - - - - Register - - - - - - - - - - - - - -\n" << endl;
        string name = getValidatedInput("Enter Name: ", "^(?=.*[A-Za-z])[A-Za-z\\s'’.-]+$", "Invalid name! Only letters are allowed.");
        string email = getValidatedInput("Enter Email: ", "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$", "Invalid email format! Must be xxxxxxx@gmail.com.");

        if (emailToCustomerId.count(email)) {
            cout << "Email already registered! Please use a different email.\n";
            return;
        }

        string password = getValidatedInput("Enter Password: ", "^.+$", "Password cannot be empty! Please enter a valid password.");
        string phone = getValidatedInput("Enter Phone Number(09XXXXXXXXX): ", "^09\\d{9}", "Invalid phone number! Must be a valid Phillipine mobile (09XXXXXXXXX).");

        cout << "Enter Address: ";
        string address;
        getline(cin, address);

        auto newCustomer = make_shared<Customer>(nextCustomerId, name, address, email, password, phone);
        customerMap[nextCustomerId] = newCustomer;
        emailToCustomerId[email] = nextCustomerId;

        cout << "Registration successful! Your customer ID is " << nextCustomerId++ << ".\n";
    }

    // Login system 
    static shared_ptr<Customer> loginCustomer() {
        cout << " - - - - - - - - - - - - - - Login - - - - - - - - - - - - - -\n" << endl;
        string email, password;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Password: ";
        cin >> password;

        auto it = emailToCustomerId.find(email);
        if (it != emailToCustomerId.end() && customerMap[it->second]->getPassword() == password) {
            cout << "Login successful!, Welcome, " << customerMap[it->second]->customerName << "!\n";
            return customerMap[it->second];
        }
        cout << "Invalid email or password!\n";
        return nullptr;
    }

    // Enum for menu options (readability)
    enum MenuOption { REGISTER = 1, LOGIN, EXIT };

    // Main Login page
    static shared_ptr<Customer> loginPage() {
        int choice;
        shared_ptr<Customer> loggedInCustomer = nullptr;
    
        do {
            cout << "- - - - - - - - - - - - - - Hot Wheels: Garage - - - - - - - - - - - - - -\n";
            cout << "\n1. Register\n2. Login\n3. Exit\n\nEnter number of choice: ";
            
            if(!(cin >> choice)) { // Fix input validation
                cout << "Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
    
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
            switch (static_cast<MenuOption>(choice)) {
            case REGISTER: 
                registerCustomer();
                break;
            case LOGIN:
                loggedInCustomer = loginCustomer();
                if (loggedInCustomer) return loggedInCustomer;
                break;
            case EXIT: 
                cout << "Exiting...\n";
                return nullptr;
            default: 
                cout << "Invalid choice! Enter only 1, 2, or 3.\n";
            }
        } while (!loggedInCustomer && choice != EXIT);
        return loggedInCustomer;
    }
};

    // Initialize the static unordered_map
    unordered_map<int, shared_ptr<Customer>> Customer::customerMap;
    unordered_map<string, int> Customer::emailToCustomerId;
    int Customer::nextCustomerId = 1000;
    
class Product {
    private:
    int productId;
    string productName;
    float unitPrice;
    
    // Static unordered map to store predefined products using shared_ptr
    static unordered_map<int, shared_ptr<Product>> productMap;
    public:
    // Constructor
    Product(int productId, string productName, float unitPrice)
    : productId(productId), productName(productName), unitPrice(unitPrice) {}

    static unordered_map<int, shared_ptr<Product>>& getProductMap() { // Public getter
        return productMap;
    }

    // Static methos to initialize predefined products
    static void initializeProducts() {
        productMap = {
            {101, make_shared<Product>(101, "Audi R8", 499.99)},
            {102, make_shared<Product>(102, "Porsche GT3 RS", 599.99)},
            {103, make_shared<Product>(103, "Ferrari 360", 399.99)},
            {104, make_shared<Product>(104, "Rolls Royce Phantom", 799.99)},
            {105, make_shared<Product>(105, "Bugatti Chiron", 899.99)}
        };
    }

    // Getters
    int getProductId() const { return productId; }
    float getUnitPrice() const { return unitPrice; }
    string getName() const { return productName; }

    // Find a product by ID
    static shared_ptr<Product> getProductbyId(int productId) {
        if (productMap.count(productId)) {
            return productMap[productId];
        } 
        return nullptr;
    }

    // Dispkay all products
    static void displayAllProducts() {
        if (productMap.empty()) {
            cout << "No products available.\n";
            return;
        }
        cout << "\n- - - - - - - - - - - - - - Products - - - - - - - - - - - - - -\n";
        for (const auto& pair : productMap) {
            pair.second->display();
            cout << "- - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - -\n";
        }
    }

    // Display function
    void display() const {
        cout << "Product ID: " << productId << endl << "Name: " << productName << endl << "Price: P" << unitPrice << endl;
    }  
};

unordered_map<int, shared_ptr<Product>> Product::productMap;

class ShoppingCart {
    private:
    unordered_map<int, int> cartItems; // productId -> quantity
     // The customer who owns this cart

    public:
    shared_ptr<Customer> owner;
    ShoppingCart() {}
    ShoppingCart(shared_ptr<Customer> owner) : owner(owner) {}

    // Add a product to the cart
    void addToCart(int productId, int quantity) {
        cartItems[productId] += quantity;
        cout << "Added " << quantity << "x Product ID " << productId << " to cart.\n";
    }

    // Remove a product from the cart
    void removeFromCart(int productId, int quantity) {
        if (cartItems.count(productId)) {
            if (cartItems[productId] > quantity) {
                cartItems[productId] -= quantity;
                cout << "Removed " << quantity << "x from cart.\n";
            } else {
                cartItems.erase(productId);
                cout << "Item removed from cart.\n";
            }
        } else {
            cout << "Item not in cart!\n";
        }
    }

    // View cart contents
    void displayCart() {
        if (cartItems.empty()) {
            cout << "Your cart is empty!\n";
            return;
        }
    
        cout << "\n- - - - - - - - - - - - - - Shopping Cart - - - - - - - - - - - - - -\n";
        float total = 0.0;
    
        auto productMap = Product::getProductMap(); // Access product map safely
    
        for (const auto& [productid, quantity] : cartItems) {
            if (productMap.find(productid) == productMap.end()) {
                cout << "Product ID " << productid << " not found!\n";
                continue;
            }
    
            auto product = productMap[productid];
            float itemTotal = product->getUnitPrice() * quantity;
            total += itemTotal;
    
            cout << product->getName() << " (x" << quantity << ") - P" << itemTotal << "\n";
        }
        cout << "Total: P" << total << "\n";
    }
    
    void checkout(bool allItems) {
        if (cartItems.empty()) {
            cout << "Your cart is empty! Nothing to checkout.\n";
            return;
        }
    
        auto productMap = Product::getProductMap(); // Access product map safely
    
        cout << "\n=========================================\n";
        cout << "              ORDER DETAILS              \n";
        cout << "=========================================\n";
        cout << left << setw(15) << "Product ID" 
             << setw(20) << "Name" 
             << setw(15) << "Price" 
             << setw(10) << "Quantity" << endl;
        cout << "----------------------------------------------------------\n";
    
        double totalPrice = 0.0;
    
        if (allItems) {
            for (const auto& [productId, quantity] : cartItems) {
                if (productMap.find(productId) != productMap.end()) {
                    auto product = productMap[productId];
                    double itemTotal = product->getUnitPrice() * quantity;
                    totalPrice += itemTotal;
                    cout << left << setw(15) << productId 
                         << setw(20) << product->getName() 
                         << setw(15) << product->getUnitPrice() 
                         << setw(10) << quantity << endl;
                }
            }
            cartItems.clear(); // Empty cart
        } else {
            int productId;
            cout << "Enter product ID to checkout: ";
            cin >> productId;
    
            if (cartItems.count(productId)) {
                if (productMap.find(productId) != productMap.end()) {
                    auto product = productMap[productId];
                    double itemTotal = product->getUnitPrice() * cartItems[productId];
                    totalPrice += itemTotal;
                    cout << left << setw(15) << productId 
                         << setw(20) << product->getName() 
                         << setw(15) << product->getUnitPrice() 
                         << setw(10) << cartItems[productId] << endl;
                } else {
                    cout << "Error: Product not found in system!\n";
                }
                cartItems.erase(productId); // Remove item from cart
            } else {
                cout << "Item not in cart!\n";
                return;
            }
        }
    
        cout << "----------------------------------------------------------\n";
        cout << right << setw(35) << "TOTAL PRICE: " << totalPrice << endl;
        cout << "=========================================\n";
    }   
    
};

class Order {
private:
    int orderId;
    int customerId;
    unordered_map<int, int> products; // productId -> quantity
    float totalPrice;
    time_t timestamp;

    static int nextOrderId;
    static unordered_map<int, vector<shared_ptr<Order>>> orderHistory; // customerId -> orders

public:
    Order(int customerId, const unordered_map<int, int>& products, float totalPrice)
        : orderId(nextOrderId++), customerId(customerId), products(products), totalPrice(totalPrice), timestamp(time(nullptr)) {}

    // Store order in order history
    static void addOrder(int customerId, const unordered_map<int, int>& products, float totalPrice) {
        auto order = make_shared<Order>(customerId, products, totalPrice);
        orderHistory[customerId].push_back(order);
        cout << "Order placed successfully! Order ID: " << order->orderId << "\n";
        cout << "Current order history size for the Customer " << customerId << ": " << orderHistory[customerId].size() << endl;
    }

    // Display order history of a customer
    static void displayOrderHistory(int customerId) {
        cout << "Checking order history for Customer ID: " << customerId << endl;
        if (orderHistory.find(customerId) == orderHistory.end() || orderHistory[customerId].empty()) {
            cout << "No past orders found for this customer.\n";
            return;
        }

        cout << "\n- - - - - - - - - - Order History - - - - - - - - - -\n";
        cout << "Total orders found: " << orderHistory[customerId].size() << "\n";
        for (const auto& order : orderHistory[customerId]) {
            cout << "Order ID: " << order->orderId << " | Total Price: P" << order->totalPrice << "\n";
            cout << "Products: \n";
            for (const auto& [productId, quantity] : order->products) {
                cout << " - Product ID " << productId << " x" << quantity << "\n";
            }
            cout << "Timestamp: " << ctime(&order->timestamp);
            cout << "----------------------\n";
        }
    }

    // Automatically create an order when checking out
    static void checkout(int customerId, const unordered_map<int, int>& cartItems) {
        if (cartItems.empty()) {
            cout << "Your cart is empty! Nothing to checkout.\n";
            return;
        }

        float totalPrice = 0.0;
        for (const auto& [productId, quantity] : cartItems) {
            totalPrice += quantity * 100; // Placeholder price calculation
        }

        addOrder(customerId, cartItems, totalPrice);
    }
};

// Initialize static members
unordered_map<int, vector<shared_ptr<Order>>> Order::orderHistory;
int Order::nextOrderId = 1;

void displayMenu() {
    cout << "\n- - - - - - - - - - - - - - Online Store Menu - - - - - - - - - - - - - -\n";
    cout << "1. View Products\n";
    cout << "2. Add to Cart\n";
    cout << "3. View Cart\n";
    cout << "4. Remove from Cart\n";
    cout << "5. Checkout\n";
    cout << "6. View Order History\n";
    cout << "7. Logout\n";
    cout << "Enter your choice: ";
}

int main() {
    Product::initializeProducts(); // Ensure products are available
    shared_ptr<Customer> currentCustomer = Customer::loginPage(); // Use loginPage to get customer

    if (!currentCustomer) return 0; // Exit if login fails

    int choice;

    do {
        displayMenu();

        // Validate input for choice
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue;
        }

        switch (choice) {
        case 1:
            Product::displayAllProducts();
            break;
        case 2: {
            int productId, quantity;
            cout << "Enter Product ID: ";
            
            // Validate Product ID input
            if (!(cin >> productId)) {
                cout << "Invalid Product ID! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "Enter Quantity: ";
            if (!(cin >> quantity) || quantity <= 0) {
                cout << "Invalid quantity! Please enter a positive number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            currentCustomer->getCart()->addToCart(productId, quantity);
            break;
        }
        case 3:
            currentCustomer->getCart()->displayCart();
            break;
        case 4: {
            int productId, quantity;
            cout << "Enter Product ID to remove: ";

            // Validate Product ID input
            if (!(cin >> productId)) {
                cout << "Invalid Product ID! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "Enter Quantity to remove: ";
            if (!(cin >> quantity) || quantity <= 0) {
                cout << "Invalid quantity! Please enter a positive number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            currentCustomer->getCart()->removeFromCart(productId, quantity);
            break;
        }
        case 5: { // Checkout
            int checkoutChoice;
            cout << "Checkout Options:\n";
            currentCustomer->getCart()->displayCart();
            cout << "1. Checkout All Items\n";
            cout << "2. Checkout Specific Product\n";
            cout << "Enter choice: ";
        
            if (!(cin >> checkoutChoice)) {
                cout << "Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        
            switch (checkoutChoice) {
            case 1:
                currentCustomer->getCart()->checkout(true);
                break;
            case 2:
                currentCustomer->getCart()->checkout(false);
                break;
            default:
                cout << "Invalid choice! Please enter 1 or 2.\n";
            }
            break;
        }        
        case 6: // View Order History
            if (currentCustomer) {
            int customerId = currentCustomer->getCustomerId();
            
            Order::displayOrderHistory(customerId);
            } else {
                cout << "No customer is logged in.\n";
            }
            break;
        case 7:
            cout << "Logging out...\n";
            return 0;
        default:
            cout << "Invalid choice! Enter only 1-7.\n";
        }

    } while (choice != 7); // Keep looping until user chooses logout

    return 0;
}
