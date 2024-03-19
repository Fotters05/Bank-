#include <iostream>
#include <string>
#include <Windows.h>



using namespace std;

class BankAccount {
private:
    int accountNumber;   
    double balance;     
    double interestRate; 
public:
    BankAccount(int accNum, double initialBalance) {
        this->accountNumber = accNum;
        if (initialBalance < 0) {
            throw invalid_argument("Начальный баланс не может быть отрицательным.");
        }
        this->balance = initialBalance;
        this->interestRate = 0;
    }




    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма внесения.");
        }
        balance += amount;
        cout << "Средства успешно внесены. Остаток на счете: " << balance << endl;
    }




    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма снятия.");
        }
        if (amount > balance) {
            throw invalid_argument("Недостаточно средств для снятия.");
        }
        balance -= amount;
        cout << "Средства успешно сняты. Остаток на счете: " << balance << endl;
    }

 



    double getBalance() {
        return balance;
    }



    double getInterest() {
        return balance * interestRate / 100.0 * (1.0 / 12.0);
    }




    void setInterestRate(double rate) {
        interestRate = rate;
    }




    double getInterestRate() {
        return interestRate;
    }




    int getAccountNumber() {
        return accountNumber;
    }
    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};




bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount <= 0) {
        throw invalid_argument("Некоректная сумма перевода");
    }
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        cout << "Операция успешно воспроизведена!" << endl;
        return true;
    }
    else {
        cout << "Не достаточно средств!" << endl;
        return false;
    }
}




int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    try {
        BankAccount Google(1, 0);
        BankAccount Aplee(2, 0);

        int choice;
        double amount;
        bool success;


        while (true) {
            cout << "Выберите действие:\n"
                "1. Пополнить счет\n"
                "2. Снять деньги\n"
                "3. Изменить процентную ставку\n"
                "4. Перевод\n"
                "5. Узнать текущую процентную ставку\n"
                "6. Выйти из программы\n";

            cout << "Ваш выбор: ";
            cin >> choice;



            
            if (!(cin >> choice)) {
                cout << "Ошибка, нужно выбрать число." << endl;
                continue; 
            }


            
            switch (choice) {
            case 1:
                cout << "Введите сумму для пополнения: ";
                cin >> amount;
                Google.deposit(amount);
                break;
            case 2:
                cout << "Введите сумму для снятия: ";
                cin >> amount;
                Google.withdraw(amount);
                break;
            case 3:
                cout << "Введите новую процентную ставку: ";
                cin >> amount;
                Google.setInterestRate(amount);
                break;
            case 4:
                cout << "Введите сумму для перевода: ";
                cin >> amount;
                success = transfer(Google, Aplee, amount);
                if (success) {
                    cout << "Баланс счета 1: " << Google.getBalance() << endl;
                    cout << "Баланс счета 2: " << Aplee.getBalance() << endl;
                }
                break;
            case 5:
                cout << "Текущая процентная ставка: " << Google.getInterestRate() << "%" << endl;
                break;
            case 6:
                cout << "Выход из программы." << endl;
                return 0;
            default:
                cout << "Ошибка: Неверный выбор. Пожалуйста, выберите действие из списка." << endl;
            }
        }

    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}