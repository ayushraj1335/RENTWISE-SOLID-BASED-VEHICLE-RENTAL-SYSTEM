# RentWise — Vehicle Rental System

## 1. Project Overview

RentWise is a console-based vehicle rental application developed in C++ using Visual Studio Code. It demonstrates the five SOLID principles of object-oriented programming through a modular and extensible design.

## 2. Features

- View available cars, bikes, and scooters.
- Rent and return vehicles.
- Calculate rental prices using different pricing strategies.
- Apply student and long-rental discounts.
- Simulate UPI, card, and cash payments.
- View rental history and generate receipts.
- Display rental notifications.

## 3. Technologies Used

- C++
- Visual Studio Code
- GCC compiler
- C++14 or newer

## 4. SOLID Principles Applied

- **SRP:** Separates vehicle management, rental operations, and receipt generation.
- **OCP:** Supports extending pricing, discount, and payment implementations.
- **LSP:** Allows different vehicle types to be used through the `Vehicle` base class.
- **ISP:** Uses separate interfaces for pricing, discounts, payments, and notifications.
- **DIP:** Uses abstractions to reduce dependencies on concrete implementations.

## 5. Project Structure

text
RentWise/
├── main.cpp
└── README.md


## 6. How to Run in Visual Studio Code

## Prerequisites

Install Visual Studio Code and a C++ compiler such as GCC. Ensure the compiler is available in your system's path.

## Steps

1. Open the `RentWise` folder in Visual Studio Code.
2. Open the integrated terminal using **Terminal → New Terminal**.
3. Compile the program:

   ```bash
   g++ -std=c++14 main.cpp -o RentWise
   ```

4. Run the program on Windows:

   ```powershell
   .\RentWise.exe
   ```

   On Linux/macOS:

   ```bash
   ./RentWise
   ```

## 7. Pricing and Discounts

- **Standard Pricing:** Uses the vehicle's daily rate.
- **Weekend Pricing:** Applies a 10% surcharge.
- **Student Discount:** Applies a 10% discount.
- **Long-Rental Discount:** Applies a 15% discount for rentals of seven days or more.

## 8. Limitations

- Rental records are stored in memory and are lost when the program exits.
- Payments are simulated and are not connected to a real payment gateway.
- Notifications are displayed in the console.

## 9. Future Enhancement

An additional notification method, such as SMS notification, could be implemented through the existing `Notifier` interface without changing the core rental logic.

## 10. Contributor

**Ayush Raj**  
Register Number: 24BCT0207


