#include <iostream> // Include input-output stream library for console operations
#include <vector>   // Include vector library to store dynamic lists of donors and patients
#include <string>   // Include string library for handling text data
#include <cctype>   // Include cctype library for character manipulation (e.g., toupper)
#include <set>      // Include set library for efficient blood group validation
using namespace std; // Use standard namespace to avoid prefixing std:: for standard library components

// Function to convert a string to uppercase for consistent blood group formatting
string toUpperCase(string str) {
    for (size_t i = 0; i < str.length(); i++) { // Loop through each character in the string
        str[i] = toupper(str[i]); // Convert each character to uppercase using toupper
    }
    return str; // Return the modified uppercase string
}

// Function to validate blood group against a set of valid blood types
bool isValidBloodGroup(const string& bloodGroup) {
    set<string> validBloodGroups = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"}; // Define valid blood groups
    return validBloodGroups.find(bloodGroup) != validBloodGroups.end(); // Return true if blood group is in the set
}

// Class to represent a blood donor
class Donor {
public:
    string name;       // Store the donor's name
    string bloodGroup; // Store the donor's blood group (e.g., A+, O-)
    int age;           // Store the donor's age
    string address;    // Store the donor's address

    // Constructor to initialize a Donor object
    Donor(string n, string bg, int a, string addr) : name(n), bloodGroup(bg), age(a), address(addr) {} // Initialize member variables
};

// Class to represent a patient needing blood
class Patient {
public:
    string name;       // Store the patient's name
    string bloodGroup; // Store the patient's blood group
    int age;           // Store the patient's age
    string address;    // Store the patient's address

    // Constructor to initialize a Patient object
    Patient(string n, string bg, int a, string addr) : name(n), bloodGroup(bg), age(a), address(addr) {} // Initialize member variables
};

// Class to manage the blood bank system
class BloodBank {
private:
    vector<Donor> donors;    // Vector to store all donor objects
    vector<Patient> patients; // Vector to store all patient objects

public:
    // Function to add a new donor to the system
    void addDonor(string name, string bloodGroup, int age, string address) {
        if (!isValidBloodGroup(bloodGroup)) { // Check if the blood group is valid
            cout << "Invalid blood group! Must be one of: A+, A-, B+, B-, AB+, AB-, O+, O-\n"; // Display error for invalid blood group
            return; // Exit the function if validation fails
        }
        if (age < 18 || age > 65) { // Check if age is within acceptable range for donors
            cout << "Invalid age! Donors must be between 18 and 65 years old.\n"; // Display error for invalid age
            return; // Exit the function if validation fails
        }
        donors.push_back(Donor(name, bloodGroup, age, address)); // Add new donor to the vector
        cout << "Donor '" << name << "' added successfully.\n"; // Confirm successful addition
    }

    // Function to add a new patient to the system
    void addPatient(string name, string bloodGroup, int age, string address) {
        if (!isValidBloodGroup(bloodGroup)) { // Check if the blood group is valid
            cout << "Invalid blood group! Must be one of: A+, A-, B+, B-, AB+, AB-, O+, O-\n"; // Display error for invalid blood group
            return; // Exit the function if validation fails
        }
        patients.push_back(Patient(name, bloodGroup, age, address)); // Add new patient to the vector
        cout << "Patient '" << name << "' added successfully.\n"; // Confirm successful addition
    }

    // Function to display all donors
    void displayDonors() {
        if (donors.empty()) { // Check if the donor list is empty
            cout << "No donors available.\n"; // Inform user if no donors exist
            return; // Exit the function
        }
        cout << "\nList of Donors:\n"; // Display header for donor list
        cout << string(60, '-') << endl; // Print a separator line for readability
        for (const auto& donor : donors) { // Loop through each donor in the vector
            cout << "Name: " << donor.name << ", Blood Group: " << donor.bloodGroup
                 << ", Age: " << donor.age << ", Address: " << donor.address << endl; // Print donor details
        }
        cout << string(60, '-') << endl; // Print closing separator line
    }

    // Function to display all patients
    void displayPatients() {
        if (patients.empty()) { // Check if the patient list is empty
            cout << "No patients available.\n"; // Inform user if no patients exist
            return; // Exit the function
        }
        cout << "\nList of Patients:\n"; // Display header for patient list
        cout << string(60, '-') << endl; // Print a separator line for readability
        for (const auto& patient : patients) { // Loop through each patient in the vector
            cout << "Name: " << patient.name << ", Blood Group: " << patient.bloodGroup
                 << ", Age: " << patient.age << ", Address: " << patient.address << endl; // Print patient details
        }
        cout << string(60, '-') << endl; // Print closing separator line
    }

    // Function to check availability of a specific blood group
    void checkBloodAvailability(string bloodGroup) {
        if (!isValidBloodGroup(bloodGroup)) { // Validate the input blood group
            cout << "Invalid blood group! Must be one of: A+, A-, B+, B-, AB+, AB-, O+, O-\n"; // Display error for invalid blood group
            return; // Exit the function if validation fails
        }
        int count = 0; // Initialize counter for matching donors
        for (const auto& donor : donors) { // Loop through all donors
            if (donor.bloodGroup == bloodGroup) { // Check if donor's blood group matches
                count++; // Increment counter for each match
            }
        }
        cout << "Blood Group " << bloodGroup << " is available with " << count << " donors.\n"; // Display result
    }

    // Function to check compatible blood groups for a patient
    void checkBloodCompatibility(string bloodGroup) {
        if (!isValidBloodGroup(bloodGroup)) { // Validate the input blood group
            cout << "Invalid blood group! Must be one of: A+, A-, B+, B-, AB+, AB-, O+, O-\n"; // Display error for invalid blood group
            return; // Exit the function if validation fails
        }
        set<string> compatibleGroups; // Set to store compatible blood groups
        // Define compatibility rules based on blood group
        if (bloodGroup == "A+") { // A+ can receive from A+, A-, O+, O-
            compatibleGroups = {"A+", "A-", "O+", "O-"};
        } else if (bloodGroup == "A-") { // A- can receive from A-, O-
            compatibleGroups = {"A-", "O-"};
        } else if (bloodGroup == "B+") { // B+ can receive from B+, B-, O+, O-
            compatibleGroups = {"B+", "B-", "O+", "O-"};
        } else if (bloodGroup == "B-") { // B- can receive from B-, O-
            compatibleGroups = {"B-", "O-"};
        } else if (bloodGroup == "AB+") { // AB+ can receive from all blood types
            compatibleGroups = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
        } else if (bloodGroup == "AB-") { // AB- can receive from A-, B-, AB-, O-
            compatibleGroups = {"A-", "B-", "AB-", "O-"};
        } else if (bloodGroup == "O+") { // O+ can receive from O+, O-
            compatibleGroups = {"O+", "O-"};
        } else if (bloodGroup == "O-") { // O- can receive from O-
            compatibleGroups = {"O-"};
        }

        cout << "\nCompatible blood groups for " << bloodGroup << ":\n"; // Display header
        cout << string(60, '-') << endl; // Print separator line
        for (const auto& group : compatibleGroups) { // Loop through compatible blood groups
            int count = 0; // Initialize counter for donors of this blood group
            for (const auto& donor : donors) { // Loop through all donors
                if (donor.bloodGroup == group) { // Check if donor's blood group matches
                    count++; // Increment counter for each match
                }
            }
            cout << "Blood Group " << group << ": " << count << " donors available\n"; // Display count for each compatible group
        }
        cout << string(60, '-') << endl; // Print closing separator line
    }
};

// Main function to run the blood bank management system
int main() {
    BloodBank bb; // Create a BloodBank object to manage donors and patients
    int choice;   // Variable to store the user's menu selection
    string name, bloodGroup, address; // Variables for name, blood group, and address input
    int age;      // Variable for age input

    do { // Start a loop to display the menu until the user chooses to exit
        cout << "\n\t\t\t\t\t======= BLOOD BANK MANAGEMENT =======\n"; // Display title
        cout << "\n1. Add Donor\n"; // Option to add a new donor
        cout << "2. Add Patient\n"; // Option to add a new patient
        cout << "3. Display Donors\n"; // Option to display all donors
        cout << "4. Display Patients\n"; // Option to display all patients
        cout << "5. Check Blood Availability\n"; // Option to check specific blood group availability
        cout << "6. Check Blood Compatibility\n"; // Option to check compatible blood groups
        cout << "7. Exit\n"; // Option to exit the program
        cout << "Enter your choice: "; // Prompt user for input
        cin >> choice; // Read the user's choice
        cin.ignore();  // Clear newline from input buffer to prevent issues with getline

        switch (choice) { // Switch statement to handle different menu options
        case 1: // Case for adding a donor
            cout << "Enter Donor Name: "; // Prompt for donor's name
            getline(cin, name); // Read full name (supports spaces)
            cout << "Valid Blood Groups: A+, A-, B+, B-, AB+, AB-, O+, O-\n"; // Display valid blood groups
            cout << "Enter Blood Group: "; // Prompt for blood group
            getline(cin, bloodGroup); // Read blood group
            bloodGroup = toUpperCase(bloodGroup); // Convert blood group to uppercase
            cout << "Enter Age: "; // Prompt for age
            cin >> age; // Read age
            cin.ignore(); // Clear newline from input buffer
            cout << "Enter Address: "; // Prompt for address
            getline(cin, address); // Read address (supports spaces)
            bb.addDonor(name, bloodGroup, age, address); // Add donor to the system
            break;

        case 2: // Case for adding a patient
            cout << "Enter Patient Name: "; // Prompt for patient's name
            getline(cin, name); // Read full name
            cout << "Valid Blood Groups: A+, A-, B+, B-, AB+, AB-, O+, O-\n"; // Display valid blood groups
            cout << "Enter Blood Group: "; // Prompt for blood group
            getline(cin, bloodGroup); // Read blood group
            bloodGroup = toUpperCase(bloodGroup); // Convert blood group to uppercase
            cout << "Enter Age: "; // Prompt for age
            cin >> age; // Read age
            cin.ignore(); // Clear newline from input buffer
            cout << "Enter Address: "; // Prompt for address
            getline(cin, address); // Read address
            bb.addPatient(name, bloodGroup, age, address); // Add patient to the system
            break;

       case 3: // Case for displaying donors
            bb.displayDonors(); // Call function to display donors
            break;

        case 4: // Case for displaying patients
            bb.displayPatients(); // Call function to display patients
            break;

        case 5: // Case for checking blood availability
            cout << "Enter Blood Group to Check Availability: "; // Prompt for blood group
            getline(cin, bloodGroup); // Read blood group
            bloodGroup = toUpperCase(bloodGroup); // Convert to uppercase
            bb.checkBloodAvailability(bloodGroup); // Check availability
            break;

        case 6: // Case for checking blood compatibility
            cout << "Enter Blood Group to Check Compatibility: "; // Prompt for blood group
            getline(cin, bloodGroup); // Read blood group
            bloodGroup = toUpperCase(bloodGroup); // Convert to uppercase
            bb.checkBloodCompatibility(bloodGroup); // Check compatible blood groups
            break;

        case 7: // Case for exiting the program
            cout << "Exiting...\n"; // Display exit message
            break;

        default: // Handle invalid menu choices
            cout << "Invalid choice! Please try again.\n"; // Display error message
        }
    } while (choice != 7); // Continue loop until user selects exit (7)

    return 0; // Exit the program
}
