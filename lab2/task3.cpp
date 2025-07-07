#include <iostream>
#include <string>
using namespace std;

// ---------- Base Class ----------
class Account {
protected:
    int accountNumber;
    double balance;
    string ownerName;

public:
    Account(int accNo, double bal, string name)
        : accountNumber(accNo), balance(bal), ownerName(name) {}

    string getOwnerName() const { return ownerName; }

    virtual void deposit(double amount) = 0;      // Pure virtual
    virtual void withdraw(double amount) = 0;     // Pure virtual

    virtual void displayInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Owner Name: " << ownerName << endl;
        cout << "Balance: $" << balance << endl;
    }

    // Overloaded operators
    bool operator>(const Account& other) const {
        return this->balance > other.balance;
    }

    bool operator<(const Account& other) const {
        return this->balance < other.balance;
    }

    bool operator==(const Account& other) const {
        return this->balance == other.balance;
    }

    virtual ~Account() {
        // virtual destructor for safe polymorphic deletion
    }
};

// ---------- SavingsAccount ----------
class SavingsAccount : public Account {
    double interestRate;
    const double minBalance = 100.0;

public:
    SavingsAccount(int accNo, double bal, string name, double rate)
        : Account(accNo, bal, name), interestRate(rate) {}

    void deposit(double amount) override {
        double interest = amount * interestRate;
        balance += amount + interest;
        cout << "Deposited with interest: $" << amount + interest << endl;
    }

    void withdraw(double amount) override {
        if (balance - amount < minBalance) {
            cout << "Withdrawal denied. Balance would fall below minimum required ($100)." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        }
    }

    void displayInfo() const override {
        cout << "[Savings Account]" << endl;
        Account::displayInfo();
        cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
    }
};

// ---------- CheckingAccount ----------
class CheckingAccount : public Account {
    double overdraftLimit;

public:
    CheckingAccount(int accNo, double bal, string name, double limit)
        : Account(accNo, bal, name), overdraftLimit(limit) {}

    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }

    void withdraw(double amount) override {
        if (amount > balance + overdraftLimit) {
            cout << "Withdrawal denied. Overdraft limit exceeded." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        }
    }

    void displayInfo() const override {
        cout << "[Checking Account]" << endl;
        Account::displayInfo();
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
    }
};

// ---------- InvestmentAccount ----------
class InvestmentAccount : public Account {
    int investmentDuration;  // in months
    double riskFactor;       // e.g., 0.1 = 10%

public:
    InvestmentAccount(int accNo, double bal, string name, int duration, double risk)
        : Account(accNo, bal, name), investmentDuration(duration), riskFactor(risk) {}

    void deposit(double amount) override {
        double change = amount * riskFactor;
        balance += amount + change;
        cout << "Deposited with investment gain: $" << amount + change << endl;
    }

    void withdraw(double amount) override {
        double change = amount * riskFactor;
        double actualAmount = amount - change;
        if (actualAmount > balance) {
            cout << "Withdrawal denied. Not enough balance after accounting for risk." << endl;
        } else {
            balance -= actualAmount;
            cout << "Withdrawn (after risk loss): $" << actualAmount << endl;
        }
    }

    void displayInfo() const override {
        cout << "[Investment Account]" << endl;
        Account::displayInfo();
        cout << "Investment Duration: " << investmentDuration << " months" << endl;
        cout << "Risk Factor: " << riskFactor * 100 << "%" << endl;
    }
};

int main() {
    // Base class pointers for polymorphism
    Account* acc1 = new SavingsAccount(1001, 500, "Alice", 0.05);
    Account* acc2 = new CheckingAccount(1002, 300, "Bob", 200);
    Account* acc3 = new InvestmentAccount(1003, 1000, "Charlie", 12, 0.10);

    // Display info
    acc1->displayInfo(); cout << endl;
    acc2->displayInfo(); cout << endl;
    acc3->displayInfo(); cout << endl;

    // Operations
    acc1->deposit(200); acc1->withdraw(150); cout << endl;
    acc2->deposit(100); acc2->withdraw(500); cout << endl;
    acc3->deposit(500); acc3->withdraw(800); cout << endl;

        cout << acc1->getOwnerName() << "'s account has more balance than " << acc2->getOwnerName() << "'s account.\n";
    if (*acc1 > *acc2) {
        cout << acc1->getOwnerName() << "'s account has more balance than " << acc2->getOwnerName() << "'s account.\n";
    }

    if (*acc3 == *acc3) {
        cout << "acc3 compared with itself using == operator works!\n";
    }

    // Free memory
    delete acc1;
    delete acc2;
    delete acc3;

    return 0;
}
