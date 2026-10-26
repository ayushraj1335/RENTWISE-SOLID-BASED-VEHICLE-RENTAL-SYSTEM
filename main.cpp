#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <limits>

using namespace std;

class Vehicle {
protected:
    int id;
    string brand;
    double dailyRate;
    bool available;

public:
    Vehicle(int vehicleId, string vehicleBrand, double rate)
        : id(vehicleId), brand(vehicleBrand), dailyRate(rate), available(true) {}

    virtual ~Vehicle() {}

    int getId() const {
        return id;
    }

    string getBrand() const {
        return brand;
    }

    double getDailyRate() const {
        return dailyRate;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool status) {
        available = status;
    }

    virtual string getType() const = 0;

    virtual void display() const {
        cout << left << setw(8) << id
             << setw(20) << getType()
             << setw(18) << brand
             << "Rs. " << fixed << setprecision(2) << dailyRate
             << (available ? "  Available" : "  Rented") << '\n';
    }
};

class Car : public Vehicle {
public:
    Car(int id, string brand, double rate)
        : Vehicle(id, brand, rate) {}

    string getType() const override {
        return "Car";
    }
};

class Bike : public Vehicle {
public:
    Bike(int id, string brand, double rate)
        : Vehicle(id, brand, rate) {}

    string getType() const override {
        return "Bike";
    }
};

class Scooter : public Vehicle {
public:
    Scooter(int id, string brand, double rate)
        : Vehicle(id, brand, rate) {}

    string getType() const override {
        return "Scooter";
    }
};

class PricingStrategy {
public:
    virtual ~PricingStrategy() {}
    virtual double calculate(double dailyRate, int days) const = 0;
};

class StandardPricing : public PricingStrategy {
public:
    double calculate(double dailyRate, int days) const override {
        return dailyRate * days;
    }
};

class WeekendPricing : public PricingStrategy {
public:
    double calculate(double dailyRate, int days) const override {
        return dailyRate * days * 1.10;
    }
};

class DiscountPolicy {
public:
    virtual ~DiscountPolicy() {}
    virtual double calculateDiscount(double amount, int days) const = 0;
};

class NoDiscount : public DiscountPolicy {
public:
    double calculateDiscount(double amount, int days) const override {
        return 0.0;
    }
};

class StudentDiscount : public DiscountPolicy {
public:
    double calculateDiscount(double amount, int days) const override {
        return amount * 0.10;
    }
};

class LongRentalDiscount : public DiscountPolicy {
public:
    double calculateDiscount(double amount, int days) const override {
        if (days >= 7) {
            return amount * 0.15;
        }
        return 0.0;
    }
};

class PaymentMethod {
public:
    virtual ~PaymentMethod() {}
    virtual bool pay(double amount) = 0;
    virtual string getName() const = 0;
};

class UPIPayment : public PaymentMethod {
public:
    bool pay(double amount) override {
        cout << "Processing UPI payment of Rs. "
             << fixed << setprecision(2) << amount << '\n';
        cout << "UPI payment successful.\n";
        return true;
    }

    string getName() const override {
        return "UPI";
    }
};

class CardPayment : public PaymentMethod {
public:
    bool pay(double amount) override {
        cout << "Processing card payment of Rs. "
             << fixed << setprecision(2) << amount << '\n';
        cout << "Card payment successful.\n";
        return true;
    }

    string getName() const override {
        return "Card";
    }
};

class CashPayment : public PaymentMethod {
public:
    bool pay(double amount) override {
        cout << "Cash payment received: Rs. "
             << fixed << setprecision(2) << amount << '\n';
        return true;
    }

    string getName() const override {
        return "Cash";
    }
};

class Notifier {
public:
    virtual ~Notifier() {}
    virtual void notify(const string& message) const = 0;
};

class ConsoleNotifier : public Notifier {
public:
    void notify(const string& message) const override {
        cout << "\nNotification: " << message << '\n';
    }
};

class RentalRecord {
public:
    int vehicleId;
    string vehicleType;
    string brand;
    int days;
    double baseAmount;
    double discount;
    double finalAmount;
    string paymentMethod;
    bool returned;

    RentalRecord(int id, string type, string vehicleBrand, int rentalDays,
                 double base, double discountAmount, double total,
                 string payment)
        : vehicleId(id),
          vehicleType(type),
          brand(vehicleBrand),
          days(rentalDays),
          baseAmount(base),
          discount(discountAmount),
          finalAmount(total),
          paymentMethod(payment),
          returned(false) {}
};

class ReceiptGenerator {
public:
    void generate(const RentalRecord& record) const {
        cout << "\n========================================\n";
        cout << "             RENTWISE RECEIPT\n";
        cout << "========================================\n";
        cout << "Vehicle ID       : " << record.vehicleId << '\n';
        cout << "Vehicle Type     : " << record.vehicleType << '\n';
        cout << "Brand            : " << record.brand << '\n';
        cout << "Rental Days      : " << record.days << '\n';

        cout << fixed << setprecision(2);
        cout << "Base Amount      : Rs. " << record.baseAmount << '\n';
        cout << "Discount         : Rs. " << record.discount << '\n';
        cout << "Final Amount     : Rs. " << record.finalAmount << '\n';
        cout << "Payment Method   : " << record.paymentMethod << '\n';
        cout << "Return Status    : "
             << (record.returned ? "Returned" : "Not returned") << '\n';
        cout << "========================================\n";
    }
};

class RentalService {
private:
    vector<unique_ptr<Vehicle>> vehicles;
    vector<RentalRecord> history;

    const PricingStrategy* pricing;
    const DiscountPolicy* discount;
    PaymentMethod* payment;
    const Notifier* notifier;

public:
    RentalService(const PricingStrategy* pricingStrategy,
                  const DiscountPolicy* discountPolicy,
                  PaymentMethod* paymentMethod,
                  const Notifier* notificationService)
        : pricing(pricingStrategy),
          discount(discountPolicy),
          payment(paymentMethod),
          notifier(notificationService) {

        vehicles.push_back(make_unique<Car>(101, "Toyota", 2500));
        vehicles.push_back(make_unique<Car>(102, "Honda", 2200));
        vehicles.push_back(make_unique<Bike>(201, "Yamaha", 800));
        vehicles.push_back(make_unique<Bike>(202, "Royal Enfield", 1000));
        vehicles.push_back(make_unique<Scooter>(301, "Honda Activa", 500));
        vehicles.push_back(make_unique<Scooter>(302, "TVS Jupiter", 450));
    }

    void setPricing(const PricingStrategy* strategy) {
        pricing = strategy;
    }

    void setDiscount(const DiscountPolicy* policy) {
        discount = policy;
    }

    void setPayment(PaymentMethod* method) {
        payment = method;
    }

    void showVehicles() const {
        cout << "\n================ AVAILABLE VEHICLES ================\n";
        cout << left << setw(8) << "ID"
             << setw(20) << "Type"
             << setw(18) << "Brand"
             << "Daily Rate\n";
        cout << "-----------------------------------------------------\n";

        for (const auto& vehicle : vehicles) {
            vehicle->display();
        }

        cout << "=====================================================\n";
    }

    void rentVehicle(int vehicleId, int days) {
        if (days <= 0) {
            cout << "Rental days must be greater than zero.\n";
            return;
        }

        Vehicle* selectedVehicle = nullptr;

        for (const auto& vehicle : vehicles) {
            if (vehicle->getId() == vehicleId) {
                selectedVehicle = vehicle.get();
                break;
            }
        }

        if (selectedVehicle == nullptr) {
            cout << "Vehicle ID not found.\n";
            return;
        }

        if (!selectedVehicle->isAvailable()) {
            cout << "This vehicle is already rented.\n";
            return;
        }

        double baseAmount =
            pricing->calculate(selectedVehicle->getDailyRate(), days);

        double discountAmount =
            discount->calculateDiscount(baseAmount, days);

        double finalAmount = baseAmount - discountAmount;

        cout << "\nRental Details\n";
        cout << "Vehicle: " << selectedVehicle->getBrand() << '\n';
        cout << "Days: " << days << '\n';
        cout << fixed << setprecision(2);
        cout << "Base Amount: Rs. " << baseAmount << '\n';
        cout << "Discount: Rs. " << discountAmount << '\n';
        cout << "Final Amount: Rs. " << finalAmount << '\n';

        if (!payment->pay(finalAmount)) {
            cout << "Payment failed. Rental was not completed.\n";
            return;
        }

        selectedVehicle->setAvailable(false);

        history.emplace_back(
            selectedVehicle->getId(),
            selectedVehicle->getType(),
            selectedVehicle->getBrand(),
            days,
            baseAmount,
            discountAmount,
            finalAmount,
            payment->getName()
        );

        notifier->notify("Vehicle rented successfully.");
    }

    void returnVehicle(int vehicleId) {
        Vehicle* selectedVehicle = nullptr;

        for (const auto& vehicle : vehicles) {
            if (vehicle->getId() == vehicleId) {
                selectedVehicle = vehicle.get();
                break;
            }
        }

        if (selectedVehicle == nullptr) {
            cout << "Vehicle ID not found.\n";
            return;
        }

        if (selectedVehicle->isAvailable()) {
            cout << "This vehicle is not currently rented.\n";
            return;
        }

        selectedVehicle->setAvailable(true);

        for (int i = static_cast<int>(history.size()) - 1; i >= 0; i--) {
            if (history[i].vehicleId == vehicleId &&
                !history[i].returned) {
                history[i].returned = true;
                break;
            }
        }

        notifier->notify("Vehicle returned successfully.");
    }

    void showHistory() const {
        if (history.empty()) {
            cout << "\nNo rental history available.\n";
            return;
        }

        cout << "\n================ RENTAL HISTORY ================\n";
        cout << fixed << setprecision(2);

        for (size_t i = 0; i < history.size(); i++) {
            cout << "\nRental " << i + 1 << '\n';
            cout << "Vehicle ID: " << history[i].vehicleId << '\n';
            cout << "Type: " << history[i].vehicleType << '\n';
            cout << "Brand: " << history[i].brand << '\n';
            cout << "Days: " << history[i].days << '\n';
            cout << "Amount: Rs. " << history[i].finalAmount << '\n';
            cout << "Payment: " << history[i].paymentMethod << '\n';
            cout << "Status: "
                 << (history[i].returned ? "Returned" : "Not returned")
                 << '\n';
        }

        cout << "================================================\n";
    }

    void showLatestReceipt(const ReceiptGenerator& generator) const {
        if (history.empty()) {
            cout << "\nNo receipt available. Rent a vehicle first.\n";
            return;
        }

        generator.generate(history.back());
    }
};

int readInt(const string& message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value) {
            return value;
        }

        cout << "Invalid input. Please enter an integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    StandardPricing standardPricing;
    WeekendPricing weekendPricing;

    NoDiscount noDiscount;
    StudentDiscount studentDiscount;
    LongRentalDiscount longRentalDiscount;

    UPIPayment upi;
    CardPayment card;
    CashPayment cash;

    ConsoleNotifier notifier;
    ReceiptGenerator receiptGenerator;

    RentalService rentalService(
        &standardPricing,
        &noDiscount,
        &upi,
        &notifier
    );

    int choice;

    do {
        cout << "\n========== RENTWISE VEHICLE RENTAL ==========\n";
        cout << "1. View Vehicles\n";
        cout << "2. Rent a Vehicle\n";
        cout << "3. Return a Vehicle\n";
        cout << "4. View Rental History\n";
        cout << "5. View Latest Receipt\n";
        cout << "6. Select Pricing Strategy\n";
        cout << "7. Select Discount Policy\n";
        cout << "8. Select Payment Method\n";
        cout << "9. Exit\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
        case 1:
            rentalService.showVehicles();
            break;

        case 2: {
            rentalService.showVehicles();

            int id = readInt("Enter vehicle ID: ");
            int days = readInt("Enter rental days: ");

            rentalService.rentVehicle(id, days);
            break;
        }

        case 3: {
            int id = readInt("Enter vehicle ID to return: ");
            rentalService.returnVehicle(id);
            break;
        }

        case 4:
            rentalService.showHistory();
            break;

        case 5:
            rentalService.showLatestReceipt(receiptGenerator);
            break;

        case 6: {
            cout << "1. Standard daily pricing\n";
            cout << "2. Weekend pricing (10% extra)\n";

            int option = readInt("Choose pricing strategy: ");

            if (option == 1) {
                rentalService.setPricing(&standardPricing);
                cout << "Standard pricing selected.\n";
            } else if (option == 2) {
                rentalService.setPricing(&weekendPricing);
                cout << "Weekend pricing selected.\n";
            } else {
                cout << "Invalid pricing option.\n";
            }

            break;
        }

        case 7: {
            cout << "1. No discount\n";
            cout << "2. Student discount (10%)\n";
            cout << "3. Long rental discount (15% for 7 or more days)\n";

            int option = readInt("Choose discount policy: ");

            if (option == 1) {
                rentalService.setDiscount(&noDiscount);
                cout << "No discount selected.\n";
            } else if (option == 2) {
                rentalService.setDiscount(&studentDiscount);
                cout << "Student discount selected.\n";
            } else if (option == 3) {
                rentalService.setDiscount(&longRentalDiscount);
                cout << "Long rental discount selected.\n";
            } else {
                cout << "Invalid discount option.\n";
            }

            break;
        }

        case 8: {
            cout << "1. UPI\n";
            cout << "2. Card\n";
            cout << "3. Cash\n";

            int option = readInt("Choose payment method: ");

            if (option == 1) {
                rentalService.setPayment(&upi);
                cout << "UPI selected.\n";
            } else if (option == 2) {
                rentalService.setPayment(&card);
                cout << "Card selected.\n";
            } else if (option == 3) {
                rentalService.setPayment(&cash);
                cout << "Cash selected.\n";
            } else {
                cout << "Invalid payment option.\n";
            }

            break;
        }

        case 9:
            cout << "Thank you for using RentWise!\n";
            break;

        default:
            cout << "Invalid choice. Please select 1-9.\n";
        }

    } while (choice != 9);

    return 0;
}