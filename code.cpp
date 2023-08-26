//Isabelle Viraldo
//08/01/2023
//Mini Project 7

#include <iostream>
#include <iomanip>
using namespace std;

int vol(int, int, int);
double addBox(int);
double shipping(double);
void printReciept();
double payment(int, double);
void getDate(int);

int payMethod, numBoxes, length, width, height, volume;
double costPer, thisDelivery, deliveryPrice, salesTax, shippingCost, taxCost, totalCost, totalSubTotal;
char date[10];
bool is65orLess = false;
bool done = false;
bool didpay = false;
string responce, customer, lastname;
stringstream reciept;

struct box{
    int size;
    double price;
    string shippingType;
    int shippingTypeNum;
    double shippingCost;
};

box order[30];

int main() {
    cout << setprecision(2) << fixed;

    cout << "****East County Cargo Transport****" << endl;
    cout << endl;
    cout << "Cashiering system 2.0" << endl;
    cout << "Starting Transactions - date - ";
    for (int i = 0; i < 10; i++){
        cin >> date[i];
    }
    cout << "  -  " << endl;
    cout << "Starting at Transaction #1" << endl;
    cout << endl;
    cout << "Enter Customer's name: ";
    cin >> customer;
    cin >> lastname;
    cout << "-" << endl;
    cout << "Customer - " << customer << " " << lastname << endl;
    cout << endl;
    
    
    //adding stuff to reciept
    reciept <<setprecision (2) << fixed << "East County Cargo Transport" << endl
    << endl
    << "123 First Street" << endl
    << "El Cajon, CA  92071" << endl
    << endl
    << "Customer Receipt - ";
    
    for (int i = 0; i < 10; i++){
        reciept << date[i];
    }
    reciept << endl
    << "Customer Name: " << customer << " " << lastname << endl
    << endl;
    
    totalSubTotal = 0;
    numBoxes = 1;
    totalSubTotal += addBox(numBoxes);
    
    while(!done){
        cout << "Another container (Y/N): ";
        cin >> responce;
        cout << "-" << endl;
        
        int yes = responce.compare("Y");
        int no = responce.compare("N");
        
        if (yes == 0){
            numBoxes = numBoxes + 1;
            totalSubTotal = totalSubTotal + addBox(numBoxes);
        } else if (no == 0){
            cout << "-" << endl;
            cout << "-" << endl;
            cout << "-" << endl;
            cout << "-" << endl;
            cout << "-" << endl;
            break;
        } 
    }
    
    salesTax = 0.0775;
    taxCost = totalSubTotal * salesTax;
    totalCost = totalSubTotal + taxCost;
    
    cout << " " << endl;
    cout << setw(45) << left << "Subtotal:" << setw(2) << left << "$" << setw(5) << right << totalSubTotal << endl;
    cout << setw(45) << left << "Sales Tax - 7.75%" << setw(2) << left << "$" << setw(8) << right << taxCost << endl;
    cout << endl;
    cout << setw(45) << left << "Total" << setw(2) << left << "$" << setw(8) << right << totalCost << endl;
    cout << endl;
    
    while (!didpay){
        cout << "Payment (1. Cash, 2. Check, 3. Credit): ";
        cin >> payMethod;
        if (payment(payMethod, totalCost)){
            didpay = true;
        } else {
            cout << "-" << endl;
            cout << "You must pay using one of the methods" << endl;
            cout << endl;
        }
    }
    
    cout << endl;
    cout << "________________________________________________________________________" << endl;
    cout << endl;
    
    reciept << setw(45) << left << "Subtotal" << setw(2) << left << "$" << setw(5) << right << totalSubTotal << endl
    << setw(45) << left << "Sales Tax - 7.75%" << setw(2) << left << "$" << setw(8) << right << taxCost << endl
    << endl
    << setw(45) << left << "Total" << setw(2) << left << "$" << setw(8) << right << totalCost << endl
    << endl;
    
    string outreciept = reciept.str();
    cout << outreciept;
   
    return 0;
}

void getDate(int deliveryType){
    bool leapYear = false;
    int daysIncrease;
    if (deliveryType == 1){
        daysIncrease = 14;
    } else if (deliveryType == 2){
        daysIncrease = 5;
    } else {
        daysIncrease = 2;
    }
    
    int month = (date[1] - '0');
    month = month + (10 * (date[0] - '0'));

    int day = (date[4] - '0');
    day = day + (10 * (date[3] - '0'));
    
    int year = (date[9] - '0');
    year = year + (10 * (date[8] - '0'));
    year = year + (100 * (date[7] - '0'));
    year = year + (1000 * (date[6] - '0'));
    
    if (year % 4 == 0){
        leapYear = true;
    }
    
    int maxDays = -1;
    if (month == 4 || month == 6 || month == 9 || month == 11){
        maxDays = 30;
    } else if (month == 2){
        maxDays = 28;
        if (leapYear){
            maxDays = 29;
        }
    } else {
        maxDays = 31;
    }
    
    //new date
    
    day = day + daysIncrease;
    if (day > maxDays){
        day = day - maxDays;
        month = month + 1;
        if (month > 12){
            month = 1;
            year = year + 1;
        }
    }
    
    
    int sVar = 9;
    
    if (order[numBoxes-1].shippingTypeNum == 2){
        sVar = sVar + 1;
    }
    if (month > 9){
        sVar = sVar - 1;
    }
    if (day > 9){
        sVar = sVar - 1;
    }
    
    reciept << month << "/" << day << "/" << setw(sVar) << left << year;
}

int vol(int l, int w, int h){
    return l*w*h;
}

double shipping(double size){
    double shipcost = 0.0;
    int shippingchoice = 0;
    while (true){
        cout << "-" << endl;
        cout << "How is this container to be shipped (choose one):" << endl;
        cout << endl;
        if (size < 30){
            cout << "(1) Standard - (one to two weeks) - No change to the price" << endl;
            cout << "(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot" << endl;
            cout << "(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot" << endl;
            cout << endl;
            cout << "Delivery Method: ";
        } else {
            cout << "(1) Standard - (one to two weeks) - No change to the price" << endl;
            cout << "(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot" << endl;
            cout << endl;
            cout << "Delivery Method: ";
        }
        cin >> shippingchoice;
        cout << "-" << endl;
        if (shippingchoice == 1){
            cout << setw(45) << left << "Standard: " << setw(5) << left << "$" << shipcost << endl;
            cout << endl;
            order[numBoxes-1].shippingType = "STD";
            order[numBoxes-1].shippingTypeNum = 1;
            return shipcost;
        } else if (shippingchoice == 2){
            shipcost = size * 1.5;
            cout << setw(45) << left << "Fast Ground ($1.50 per cu ft): " << setw(5) << left << "$" << shipcost << endl;
            cout << endl;
            order[numBoxes-1].shippingType = "FG";
            order[numBoxes-1].shippingTypeNum = 2;
            return shipcost;
        } else if (shippingchoice == 3){
            shipcost = size * 3;
            cout << setw(45) << left << "Air ($3.00 per cu ft): " << setw(5) << left << "$" << shipcost << endl;
            cout << endl;
            order[numBoxes-1].shippingType = "AIR";
            order[numBoxes-1].shippingTypeNum = 3;
            return shipcost;
        }
    }
}

double addBox(int num){
     while (!is65orLess) {
        cout << "Enter dimensions for package #" << num << " (in feet):" << endl;
        cout << "Length: ";
        cin >> length;
        cout << "Width:  ";
        cin >> width;
        cout << "Height: ";
        cin >> height;
        cout << "-" << endl;
   
        volume = vol(length, width, height);
   
        if (volume <= 65){
            order[numBoxes-1].size = volume;
            is65orLess = true;
        } else {
            cout << "This package exceeds the 65 cubic foot limit. Please input again." << endl;
        }
    }
    cout << "Volume of container #" << num << " is " << volume << " cu ft" << endl;
   
    if (volume < 15){
        costPer = 1.50;
        shippingCost = static_cast<double>(volume) * costPer;
        order[numBoxes-1].price = shippingCost;
        cout <<  setw(45) << left << "Small Package ($1.50 per cu ft):" << setw(2) << left << "$" << setw(8) << right << shippingCost << endl;
    } else if (volume < 45){
        costPer = 2.50;
        shippingCost = static_cast<double>(volume) * costPer;
        order[numBoxes-1].price = shippingCost;
        cout <<  setw(45) << left << "Medium Package ($2.50 per cu ft):" << setw(2) << left << "$" << setw(8) << right << shippingCost << endl;
    } else {
        costPer = 3.00;
        shippingCost = static_cast<double>(volume) * costPer;
        order[numBoxes-1].price = shippingCost;
        cout <<  setw(45) << left << "Large Package ($3.00 per cu ft): " << setw(2) << left << "$" << setw(8) << right << shippingCost << endl;
    }
    
    //get shipping cost
    thisDelivery = shipping(volume);
    order[numBoxes-1].shippingCost = thisDelivery;
    deliveryPrice = deliveryPrice + thisDelivery;
    shippingCost = shippingCost + thisDelivery;
    
    int cVar = 29;
    if (order[numBoxes-1].size > 9){
        cVar = cVar - 1;
    }
    
    reciept << "Container #" << numBoxes << " - " << order[numBoxes-1].size << setw(cVar) << left << " cu ft" << setw(2) << left << "$" << setw(8) << right << order[numBoxes-1].price << endl
        << "Shipping: " << order[numBoxes-1].shippingType << " - Est. Delivery - ";
        getDate(order[numBoxes-1].shippingTypeNum);
        reciept << setw(2) << left << "$" << setw(8) << right << order[numBoxes-1].shippingCost << endl
        << endl;
    
    
    
    
    
    
    
    is65orLess = false;
    return shippingCost;
}

double payment(int pay, double price){
    double cash;
    char cardtype;
    char drivers[8];
    char card[4];
    bool needpayment = true;
    bool cardtypeentered = false;
    
    if (pay == 1){
        while (needpayment){
            cout << setw(45) << left << "Accepted:" << setw(4) << left << "$";
            cin >> cash;
        
            if (cash < price){
                cout << "Your order costs $" << price << ", you must enter at least that much, change will be given" << endl;
            } else {
                cout << setw(45) << left << "Change:" << setw(2) << left << "$" << setw(8) << right << (cash - price) << endl;
                return true;
            }
        }
    } else if (pay == 2){
        while (needpayment){
            cout << setw(45) << left << "Enter Driver License No:";
            for (int x = 0; x < 8; x++){
                cin >> drivers[x];
                }
            if (static_cast<int>(drivers[0]) < 123 && static_cast<int>(drivers[0]) > 96 && static_cast<int>(drivers[1]) < 58 && static_cast<int>(drivers[1]) > 47 && static_cast<int>(drivers[2]) < 58 && static_cast<int>(drivers[2]) > 47 && static_cast<int>(drivers[3]) < 58 && static_cast<int>(drivers[3]) > 47 && static_cast<int>(drivers[4]) < 58 && static_cast<int>(drivers[4]) > 47 && static_cast<int>(drivers[5]) < 58 && static_cast<int>(drivers[5]) > 47 && static_cast<int>(drivers[6]) < 58 && static_cast<int>(drivers[6]) > 47 && static_cast<int>(drivers[7]) < 58 && static_cast<int>(drivers[7]) > 47 ){
                cout << setw(45) << left << "Accepted Check Payment:" << setw(2) << left << "$" << setw(8) << right << price << endl;
                return true;
            } else {
                cout << "error" << endl;
            }
        }
    } else if (pay == 3){
        while (needpayment){
            cout << setw(45) << left << "Visa (V) or Mastercard (M):";
            cin >> cardtype;
            switch (cardtype){
                case 'V': cardtypeentered = true;
                break;
                case 'M' : cardtypeentered = true;
                break;
                default: cout << "please select and option (V or M)" << endl;
            }
            if (cardtypeentered){
                cout << setw(45) << left << "Enter Last Four Digits of Card:";
                for (int x = 0; x < 4; x++){
                    cin >> card[x];
                }
                if (static_cast<int>(card[0]) < 58 && static_cast<int>(card[0]) > 47 && static_cast<int>(card[1]) < 58 && static_cast<int>(card[1]) > 47 && static_cast<int>(card[2]) < 58 && static_cast<int>(card[2]) > 47 && static_cast<int>(card[3]) < 58 && static_cast<int>(card[3]) > 47){
                    cout << setw(45) << left << "Accepted Credit Card Payment:" << setw(2) << left << "$" << setw(8) << right << price << endl;
                    return true;
                } else {
                cout << "error" << endl;
                cardtypeentered = false;
                }
            }
        }
    } else { return false; }
}

/*
Output:
****East County Cargo Transport****

Cashiering system 2.0
Starting Transactions - date - 05/28/2022
-  
Starting at Transaction #1

Enter Customer's name: Jerry Lewis
-
Customer - Jerry Lewis

Enter dimensions for package #1 (in feet):
Length: 3
Width:  4
Height: 2
-
Volume of container #1 is 24 cu ft
Medium Package ($2.50 per cu ft):            $    60.00
-
How is this container to be shipped (choose one):

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot
(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot

Delivery Method: 2
-
Fast Ground ($1.50 per cu ft):               $    36.00

Another container (Y/N): Y
-
Enter dimensions for package #2 (in feet):
Length: 9
Width:  2
Height: 3
-
Volume of container #2 is 54 cu ft
Large Package ($3.00 per cu ft):             $   162.00
-
How is this container to be shipped (choose one):

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot

Delivery Method: 1
-
Standard:                                    $    0.00

Another container (Y/N): Y
-
Enter dimensions for package #3 (in feet):
Length: 1
Width:  2
Height: 4
-
Volume of container #3 is 8 cu ft
Small Package ($1.50 per cu ft):             $    12.00
-
How is this container to be shipped (choose one):

(1) Standard - (one to two weeks) - No change to the price
(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot
(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet - Extra $3.00 per cubic foot

Delivery Method: 3
-
Air ($3.00 per cu ft):                       $    24.00

Another container (Y/N): N
-
-
-
-
-
-
 
Subtotal:                                    $   294.00
Sales Tax - 7.75%                            $    22.79

Total                                        $   316.79

Payment (1. Cash, 2. Check, 3. Credit): 1
Accepted:                                    $   320.00
Change:                                      $     3.21

________________________________________________________________________

East County Cargo Transport

123 First Street
El Cajon, CA  92071

Customer Receipt - 05/28/2022
Customer Name: Jerry Lewis

Container #1 - 24 cu ft                      $    60.00
Shipping: FG - Est. Delivery - 6/2/2022      $    36.00

Container #2 - 54 cu ft                      $   162.00
Shipping: STD - Est. Delivery - 6/11/2022    $     0.00

Container #3 - 8 cu ft                       $    12.00
Shipping: AIR - Est. Delivery - 5/30/2022    $    24.00

Subtotal                                     $   294.00
Sales Tax - 7.75%                            $    22.79

Total                                        $   316.79

*/
