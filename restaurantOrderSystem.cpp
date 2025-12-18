#include <bits/stdc++.h>
using namespace std;

class Dish {
public:
    int id;
    string name, cuisine, category;
    double price;
    bool veg, available;

    Dish(int id, string n, string cu, string ca, double p, bool v) {
        this->id = id;
        name = n;
        cuisine = cu;
        category = ca;
        price = p;
        veg = v;
        available = true;
    }
};

class OrderItem {
public:
    Dish* dish;
    int quantity;

    OrderItem(Dish* d, int q) {
        dish = d;
        quantity = q;
    }
};

class Order {
public:
    int id;
    vector<OrderItem> items;
    string status;
    int tableNo;
    bool takeaway;

    Order(int id) {
        this->id = id;
        status = "Placed";
        tableNo = 0;
        takeaway = false;
    }

    double getTotal() {
        double total = 0;
        for (auto &it : items)
            total += it.dish->price * it.quantity;
        return total;
    }
};

class RestaurantSystem {
    vector<Dish> dishes;
    vector<Order> orders;
    int nextDishId = 1;
    int nextOrderId = 1;

public:
    RestaurantSystem() {
        initMenu();
    }

    void initMenu() {
        addDish("Masala Dosa","Indian","Breakfast",80,true);
        addDish("Paneer Butter Masala","Indian","Lunch",180,true);
        addDish("Butter Chicken","Indian","Dinner",220,false);
        addDish("Samosa","Indian","Snacks",20,true);
        addDish("Gulab Jamun","Indian","Dessert",40,true);
    }

    void addDish(string n, string cu, string ca, double p, bool v) {
        dishes.emplace_back(nextDishId++, n, cu, ca, p, v);
    }

    void showMenu() {
        cout << "\n--- MENU ---\n";
        for (auto &d : dishes) {
            if (!d.available) continue;
            cout << d.id << ". " << d.name
                 << (d.veg ? " (Veg)" : " (Non-Veg)")
                 << " - Rs." << d.price << endl;
        }
    }

    Dish* getDishById(int id) {
        for (auto &d : dishes)
            if (d.id == id && d.available)
                return &d;
        return nullptr;
    }

    void placeOrder() {
        Order order(nextOrderId++);
        int choice, qty;

        while (true) {
            showMenu();
            cout << "Enter dish id (0 to finish): ";
            cin >> choice;
            if (choice == 0) break;

            Dish* d = getDishById(choice);
            if (!d) {
                cout << "Invalid dish\n";
                continue;
            }

            cout << "Quantity: ";
            cin >> qty;
            order.items.emplace_back(d, qty);
        }

        if (order.items.empty()) {
            cout << "No items selected\n";
            return;
        }

        cout << "Table No: ";
        cin >> order.tableNo;

        cout << "Takeaway? (1/0): ";
        cin >> order.takeaway;

        orders.push_back(order);
        printReceipt(order);
    }

    void printReceipt(Order &o) {
        cout << "\n--- RECEIPT ---\n";
        cout << "Order ID: " << o.id << endl;
        cout << "Table: " << o.tableNo
             << (o.takeaway ? " (Takeaway)" : "") << endl;

        for (auto &it : o.items) {
            cout << it.dish->name
                 << " x" << it.quantity
                 << " = Rs." << it.dish->price * it.quantity << endl;
        }

        cout << "TOTAL: Rs." << o.getTotal() << endl;
        cout << "Status: " << o.status << endl;
    }

    void viewOrders() {
        if (orders.empty()) {
            cout << "No orders yet\n";
            return;
        }
        for (auto &o : orders) {
            cout << "ID: " << o.id
                 << " | Table: " << o.tableNo
                 << " | Total: Rs." << o.getTotal() << endl;
        }
    }

    void run() {
        int ch;
        while (true) {
            cout << "\n1. Place Order\n2. View Orders\n3. Exit\nChoice: ";
            cin >> ch;
            if (ch == 1) placeOrder();
            else if (ch == 2) viewOrders();
            else break;
        }
    }
};

int main() {
    RestaurantSystem app;
    app.run();
    return 0;
}
