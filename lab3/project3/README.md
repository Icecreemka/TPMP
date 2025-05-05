# Patient Database Manager

A comprehensive C application for managing patient information in a SQLite database, designed for healthcare facilities to store, search, and manage patient records efficiently.

## Features

- **Patient Records Management**:
  - Add individual patients or multiple patients in a transaction
  - Update patient information
  - Delete patient records
  - Search patients by ID, surname, or department

- **Data Handling**:
  - SQLite database integration
  - Transaction support for bulk operations
  - Error handling for database operations

- **User Interface**:
  - Console-based menu system
  - Interactive data input
  - Clear data presentation

## System Requirements

- C Compiler (GCC recommended)
- SQLite3 development library
- Make (for build automation)

## Project Structure

```
patient-db-manager/
├── include/
│   ├── database.h
│   ├── menu.h
│   └── utils.h
├── src/
│   ├── database.c
│   ├── menu.c
│   ├── utils.c
│   └── main.c
├── data/
│   └── patients.db
├── Makefile
└── README.md
```

## Build and Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/patient-db-manager.git
   cd patient-db-manager
   ```

2. Build the project:
   ```
   make
   ```

3. Run the application:
   ```
   ./patient_db_manager
   ```

## Usage

The application provides a menu-driven interface:

1. **Main Menu**:
   - Search and view data
   - Add data
   - Delete data
   - Update data
   - Create report
   - Exit

2. **Search Options**:
   - Search by patient ID
   - Search by surname
   - Search by department number

3. **Data Entry**:
   - Add a single patient with automatic commit
   - Add multiple patients as a transaction

## Patient Information Fields

- Personal details (name, gender, nationality, etc.)
- Physical characteristics (height, weight)
- Birth date information
- Contact information (phone, address)
- Medical information (diagnosis, blood type, etc.)
- Department assignment

## Database Schema

The application uses a SQLite database with the following schema:

```sql
CREATE TABLE IF NOT EXISTS 'patient_info' (
  id INTEGER PRIMARY KEY,
  surname TEXT,
  name TEXT,
  patronymic TEXT,
  gender TEXT,
  nationality TEXT,
  height INTEGER,
  weight INTEGER,
  birth_year INTEGER,
  birth_month INTEGER,
  birth_day INTEGER,
  phone TEXT,
  address TEXT,
  med_card_number TEXT,
  diagnosis TEXT,
  blood_group TEXT,
  department INTEGER
);
```

## Screenshots

[Add screenshots of the application here]

## License

[Specify your license here]

## Contributors

[List contributors here]

## Acknowledgements

- SQLite development team
- [Add any other acknowledgements]