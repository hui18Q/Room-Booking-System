# Room-Booking-System
A console-based application designed to streamline hotel room bookings, catering to both customers and administrators.

## **Table of Contents**
- [Overview](#overview)
- [Features](#features)
- [How It Works](#how-it-works)
- [Installation](#installation)
- [Usage](#usage)
- [Contributors](#contributors)
- [License](#license)

## **Overview**  
The Room Booking System provides an intuitive interface for hotel administrators to manage room pricing and booking details, while customers can easily reserve rooms based on real-time availability.

## **Features**  
- **Admin Functionality:**
  - Modify room prices.
  - View customer booking details.
  - Store and retrieve pricing information from files.
- **Customer Functionality:**
  - Book rooms by entering personal details.
  - Select room type and stay duration.
  - Calculate total charges for bookings.
  - Store booking details for later access.
- **File Handling:**
  - Reads and writes room prices (`price.txt`).
  - Stores booking details (`bookingDetails.txt`).
- **Search Feature:**
  - Allows users to search for specific booking records.

## **How It Works**  
1. **Admin Role:**
   - Logs in using a password.
   - Can update room prices stored in a file.
   - Can view all booking records.

2. **Customer Role:**
   - Provides personal details (name, ID, contact info).
   - Selects a room type and stay duration.
   - Confirms booking and stores details in a file.

## **Installation**  
To set up and run the project:  
1. **Clone the repository:**  
   ```bash
   git clone <repository-url>
   cd RoomBookingSystem
   ```
2. **Compile the program:**  
   ```bash
   g++ main.cpp -o RoomBookingSystem
   ```
3. **Run the executable:**  
   ```bash
   ./RoomBookingSystem
   ```

## **Usage**  
- **Admin Mode:**  
  - Log in as an admin to modify pricing and view bookings.  
- **Customer Mode:**  
  - Enter booking details and receive a booking confirmation.  
- **File Handling:**  
  - All booking and pricing data is stored in local text files.


## **License**  
This project is for academic purposes and is licensed under **[MIT License](LICENSE)**.
