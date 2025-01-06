#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MCARS = 10;
const int MCustomer = 10;

struct Car {
    string name;
    string type;
    float price_per_hour;
    bool avaible;
};

struct Customer {
    string username;
    string password;
    string name;
};

void registerCustomer(Customer customers[], int& customerCount);
bool loginCustomer(const Customer customers[], int customerCount);
void showAvailableCars(const Car cars[], int carCount);
float calculateFare(float price_per_hour, float hours, float distance);
void saveCustomersToFile(const Customer customers[], int customerCount);
void saveCarsToFile(const Car cars[], int carCount);
void loadCustomersFromFile(Customer customers[], int& customerCount);
void loadCarsFromFile(Car cars[], int& carCount);

int main() {
    Customer customers[MCustomer];
    Car cars[MCARS];
    int customerCount = 0;
    int carCount = 0;

    loadCustomersFromFile(customers, customerCount);
    loadCarsFromFile(cars, carCount);

    int choice;
    bool login = false;

    while (true) {
        cout << "Welcome to the Car Rental System!" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            registerCustomer(customers, customerCount);
            saveCustomersToFile(customers, customerCount);
        } else if (choice == 2) {
            login = loginCustomer(customers, customerCount);

            if (login) {
                cout << "Login successful!" << endl;

                while (true) {
                    int carChoice;
                    cout << "\nMenu:" << endl;
                    cout << "1. View Available Cars" << endl;
                    cout << "2. Calculate Fare" << endl;
                    cout << "3. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> carChoice;

                    if (carChoice == 1) {
                        showAvailableCars(cars, carCount);
                    } else if (carChoice == 2) {
                        float hours, distance;
                        cout << "Enter rental duration in hours: ";
                        cin >> hours;
                        cout << "Enter distance traveled in km: ";
                        cin >> distance;

                        cout << "Select car from the list: ";
                        int carIndex;
                        cin >> carIndex;
                        if (carIndex >= 0 && carIndex < carCount && cars[carIndex].avaible) {
                            float fare = calculateFare(cars[carIndex].price_per_hour, hours, distance);
                            cout << "Total fare: $" << fixed << setprecision(2) << fare << endl;
                        } else {
                            cout << "Invalid selection or car is not available." << endl;
                        }
                    } else if (carChoice == 3) {
                        cout << "Logging out..." << endl;
                        break;
                    } else {
                        cout << "Invalid choice!" << endl;
                    }
                }
            } else {
                cout << "Invalid username or password!" << endl;
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}

void registerCustomer(Customer customers[], int& cusCount) {
    string username, password, name;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter full name: ";
    cin.ignore();  
    getline(cin, name);

    customers[cusCount].username = username;
    customers[cusCount].password = password;
    customers[cusCount].name = name;

    cusCount++;
    cout << "Customer registered successfully!" << endl;
}

bool loginCustomer(const Customer customers[], int customerCount) {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < customerCount; i++) {
        if (customers[i].username == username && customers[i].password == password) {
            return true;
        }
    }

    return false;
}

void showAvailableCars(const Car cars[], int carCount) {
    cout << "\nAvailable Cars:" << endl;
    for (int i = 0; i < carCount; i++) {
        if (cars[i].avaible) {
            cout << i << ". " << cars[i].name << " (" << cars[i].type << ") - $"
                 << cars[i].price_per_hour << " per hour" << endl;
        }
    }
}

float calculateFare(float price_per_hour, float hours, float distance) {
    return (price_per_hour * hours) + (0.50 * distance);
}

void saveCustomersToFile(const Customer customers[], int customerCount) {
    ofstream file("customers.txt");

    for (int i = 0; i < customerCount; i++) {
        file << customers[i].username << "\n" << customers[i].password << "\n"
             << customers[i].name << endl;
    }

    file.close();
}

void saveCarsToFile(const Car cars[], int carCount) {
    ofstream file("cars.txt");

    for (int i = 0; i < carCount; i++) {
        file << cars[i].name << "\n" << cars[i].type << "\n" << cars[i].price_per_hour << "\n"
             << cars[i].avaible << endl;
    }

    file.close();
}

void loadCustomersFromFile(Customer customers[], int& cusCount) {
    ifstream file("customers.txt");

    string username, password, name;
    while (getline(file, username)) {
        getline(file, password);
        getline(file, name);

        customers[cusCount].username = username;
        customers[cusCount].password = password;
        customers[cusCount].name = name;

        cusCount++;
    }

    file.close();
}

void loadCarsFromFile(Car cars[], int& carCount) {
    ifstream file("cars.txt");

    string name, type;
    float price_per_hour;
    bool avaible;
    while (getline(file, name)) {
        getline(file, type);
        file >> price_per_hour >> avaible;
        file.ignore();  

        cars[carCount].name = name;
        cars[carCount].type = type;
        cars[carCount].price_per_hour = price_per_hour;
        cars[carCount].avaible = avaible;

        carCount++;
    }

    file.close();
}
