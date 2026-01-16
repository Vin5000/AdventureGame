// Text-based Adventure Game - Underground Laboratory
// Meets: classes, structs, enums, arrays, menus, loops, validation, formatted output

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ========================= ENUM REQUIREMENT =========================
// Difficulty level chosen once at the start.
enum SecurityLevel {
    LOW = 1,
    MEDIUM,
    HIGH
};

// ========================= STRUCT REQUIREMENT =========================
// Represents one "location visit" in the adventure.
struct Session {
    string areaName;
    bool foundDocuments;
};

// ========================= CLASS REQUIREMENT =========================
class AdventureGame {
private:
    // Struct array requirement
    Session sessions[10];
    int sessionCount;

    // Inventory array requirement
    string inventory[5];
    int inventoryCount;

    // Player info
    string playerName;
    SecurityLevel difficulty;

    // Current location state
    string currentLocation; // "Outside", "Cave", "LabDoor", "Lab"
    bool missionComplete;

public:
    // Constructor initializes safe starting state
    AdventureGame() {
        sessionCount = 0;
        inventoryCount = 0;
        playerName = "Unknown";
        difficulty = LOW;
        currentLocation = "Outside";
        missionComplete = false;
    }

    // ========================= BANNER FUNCTION =========================
    void displayBanner() const {
        cout << "=====================================================\n";
        cout << "      WELCOME TO THE UNDERGROUND LAB ADVENTURE       \n";
        cout << "=====================================================\n";
        cout << "You begin with a keycard and stand outside a cave\n";
        cout << "that leads to a hidden underground laboratory.\n";
        cout << "Your mission: Find the research documents and escape.\n\n";
    }

    // ========================= INPUT & VALIDATION =========================
    void collectPlayerSetup() {
        cout << "Enter your operative name: ";
        getline(cin, playerName);
        while (playerName.empty()) {
            cout << "Name cannot be empty. Enter your operative name: ";
            getline(cin, playerName);
        }

        int diffChoice;
        cout << "Choose difficulty (1=Low, 2=Medium, 3=High): ";
        while (!(cin >> diffChoice) || diffChoice < 1 || diffChoice > 3) {
            cout << "Invalid choice. Enter 1, 2, or 3: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        difficulty = static_cast<SecurityLevel>(diffChoice);
        cin.ignore(1000, '\n');

        // Starting inventory: keycard
        inventory[inventoryCount++] = "Keycard";

        cout << "\nWelcome, " << playerName << ". Your keycard has been added to your inventory.\n\n";
    }

    // ========================= INVENTORY HELPERS =========================
    bool hasItem(const string& item) const {
        for (int i = 0; i < inventoryCount; ++i) {
            if (inventory[i] == item) return true;
        }
        return false;
    }

    void addSession(const string& areaName, bool foundDocs) {
        if (sessionCount >= 10) return;
        sessions[sessionCount].areaName = areaName;
        sessions[sessionCount].foundDocuments = foundDocs;
        sessionCount++;
    }

    // ========================= REPORT REQUIREMENT =========================
    void showReport() const {
        cout << "\n==================== ADVENTURE SUMMARY ====================\n";
        if (sessionCount == 0) {
            cout << "No locations visited yet.\n\n";
            return;
        }

        cout << left << setw(20) << "Area"
            << setw(15) << "Documents"
            << "\n";
        cout << string(35, '-') << "\n";

        int docsCount = 0;
        for (int i = 0; i < sessionCount; ++i) {
            cout << left << setw(20) << sessions[i].areaName
                << setw(15) << (sessions[i].foundDocuments ? "Found" : "None")
                << "\n";
            if (sessions[i].foundDocuments) docsCount++;
        }

        cout << string(35, '-') << "\n";
        cout << "Total locations visited: " << sessionCount << "\n";
        cout << "Total document finds:    " << docsCount << "\n\n";
    }

    // ========================= INVENTORY DISPLAY =========================
    void showInventory() const {
        cout << "\n--- Inventory ---\n";
        if (inventoryCount == 0) {
            cout << "(Empty)\n\n";
            return;
        }
        for (int i = 0; i < inventoryCount; ++i) {
            cout << "- " << inventory[i] << "\n";
        }
        cout << "\n";
    }

    // ========================= LOCATION MENUS =========================
    void outsideMenu() {
        int choice;
        do {
            cout << "==================== OUTSIDE THE CAVE ====================\n";
            cout << "1. Enter the cave\n";
            cout << "2. View inventory\n";
            cout << "3. View summary report\n";
            cout << "4. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-4: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            switch (choice) {
            case 1:
                currentLocation = "Cave";
                addSession("Entrance Cave", false); // Entrance cave has no documents
                caveMenu();
                break;
            case 2:
                showInventory();
                break;
            case 3:
                showReport();
                break;
            case 4:
                cout << "Exiting game. Goodbye, " << playerName << ".\n";
                return;
            default:
                cout << "Invalid choice.\n\n";
            }

        } while (choice != 4);
    }

    void caveMenu() {
        int choice;
        do {
            cout << "==================== INSIDE THE CAVE ====================\n";
            cout << "1. Leave cave (go outside)\n";
            cout << "2. Go to lab door\n";
            cout << "3. View inventory\n";
            cout << "4. View summary report\n";
            cout << "5. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-5: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            switch (choice) {
            case 1:
                currentLocation = "Outside";
                return; // back to outsideMenu
            case 2:
                currentLocation = "LabDoor";
                addSession("Lab Door", false);
                labDoorMenu();
                break;
            case 3:
                showInventory();
                break;
            case 4:
                showReport();
                break;
            case 5:
                cout << "Exiting game. Goodbye, " << playerName << ".\n";
                exit(0);
            default:
                cout << "Invalid choice.\n\n";
            }

        } while (true);
    }

    void labDoorMenu() {
        int choice;
        do {
            cout << "==================== AT THE LAB DOOR ====================\n";
            cout << "1. Use keycard to enter lab\n";
            cout << "2. Return to cave\n";
            cout << "3. View inventory\n";
            cout << "4. View summary report\n";
            cout << "5. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-5: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            switch (choice) {
            case 1:
                if (hasItem("Keycard")) {
                    cout << "You swipe the keycard. The door unlocks.\n";
                    currentLocation = "Lab";
                    addSession("Laboratory", false);
                    labMenu();
                    return;
                }
                else {
                    cout << "You do not have the keycard. You cannot enter.\n\n";
                }
                break;
            case 2:
                currentLocation = "Cave";
                return; // back to caveMenu
            case 3:
                showInventory();
                break;
            case 4:
                showReport();
                break;
            case 5:
                cout << "Exiting game. Goodbye, " << playerName << ".\n";
                exit(0);
            default:
                cout << "Invalid choice.\n\n";
            }

        } while (true);
    }

    void labMenu() {
        int choice;
        do {
            cout << "==================== INSIDE THE LAB ====================\n";
            cout << "1. Search for documents\n";
            cout << "2. View inventory\n";
            cout << "3. View summary report\n";
            cout << "4. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-4: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');

            switch (choice) {
            case 1:
                searchForDocuments();
                // After mission complete, return to outside main menu
                currentLocation = "Outside";
                return;
            case 2:
                showInventory();
                break;
            case 3:
                showReport();
                break;
            case 4:
                cout << "Exiting game. Goodbye, " << playerName << ".\n";
                exit(0);
            default:
                cout << "Invalid choice.\n\n";
            }

        } while (true);
    }

    // ========================= DOCUMENT SEARCH =========================
    void searchForDocuments() {
        if (missionComplete) {
            cout << "You have already completed your mission.\n\n";
            return;
        }

        cout << "You search the lab thoroughly...\n";
        cout << "You find the classified research documents!\n";
        if (inventoryCount < 5) {
            inventory[inventoryCount++] = "Research Documents";
        }
        // Mark last session as having documents
        if (sessionCount > 0) {
            sessions[sessionCount - 1].foundDocuments = true;
        }
        missionComplete = true;

        cout << "\n==================== MISSION COMPLETE ====================\n";
        cout << "You have secured the research documents.\n";
        cout << "You may now review your report or quit the game.\n\n";
    }

    // ========================= MAIN FLOW =========================
    void run() {
        displayBanner();
        collectPlayerSetup();
        outsideMenu();
    }
};

// ========================= MAIN =========================
int main() {
    AdventureGame game;
    game.run();
    return 0;
}
