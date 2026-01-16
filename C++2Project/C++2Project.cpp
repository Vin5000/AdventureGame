#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

// ========================= ENUM REQUIREMENT =========================
enum SecurityLevel {
    LOW = 1,
    MEDIUM,
    HIGH
};

// ========================= STRUCT REQUIREMENT =========================
struct Session {
    string areaName;
    bool foundDocuments;
};

// ========================= ARRAY PARAMETER FUNCTION =========================
void printInventory(const string inv[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "- " << inv[i] << "\n";
    }
}

// ========================= CLASS REQUIREMENT =========================
class AdventureGame {
private:
    // Constants to avoid magic numbers
    static const int MAX_SESSIONS = 10;
    static const int MAX_INVENTORY = 5;
    static const int INPUT_IGNORE = 1000;

    Session sessions[MAX_SESSIONS];
    int sessionCount;

    string inventory[MAX_INVENTORY];
    int inventoryCount;

    string playerName;
    SecurityLevel difficulty;
    double missionTimeLimit; // third user input

    string currentLocation;
    bool missionComplete;

public:
    AdventureGame() {
        sessionCount = 0;
        inventoryCount = 0;
        playerName = "Unknown";
        difficulty = LOW;
        missionTimeLimit = 0.0;
        currentLocation = "Outside";
        missionComplete = false;
    }
    //
    // ========================= BANNER =========================
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
            cin.ignore(INPUT_IGNORE, '\n');
        }
        difficulty = static_cast<SecurityLevel>(diffChoice);

        cout << "Enter your mission time limit in minutes: ";
        while (!(cin >> missionTimeLimit) || missionTimeLimit <= 0) {
            cout << "Invalid. Enter a positive number: ";
            cin.clear();
            cin.ignore(INPUT_IGNORE, '\n');
        }
        cin.ignore(INPUT_IGNORE, '\n');

        inventory[inventoryCount++] = "Keycard";

        cout << "\nWelcome, " << playerName << ". Your keycard has been added to your inventory.\n\n";
    }

    // ========================= HELPERS =========================
    bool hasItem(const string& item) const {
        for (int i = 0; i < inventoryCount; ++i) {
            if (inventory[i] == item) return true;
        }
        return false;
    }

    void addSession(const string& areaName, bool foundDocs) {
        if (sessionCount < MAX_SESSIONS) {
            sessions[sessionCount].areaName = areaName;
            sessions[sessionCount].foundDocuments = foundDocs;
            sessionCount++;
        }
    }

    // ========================= FILE OUTPUT =========================
    void saveReportToFile() const {
        ofstream out("report.txt");
        if (!out) {
            cout << "Error saving report.\n";
            return;
        }

        out << "==================== ADVENTURE SUMMARY ====================\n";
        out << left << setw(20) << "Area" << setw(15) << "Documents" << "\n";
        out << string(35, '-') << "\n";

        int docsCount = 0;
        for (int i = 0; i < sessionCount; i++) {
            out << left << setw(20) << sessions[i].areaName
                << setw(15) << (sessions[i].foundDocuments ? "Found" : "None") << "\n";
            if (sessions[i].foundDocuments) docsCount++;
        }

        double percentAreasVisited = (sessionCount / static_cast<double>(MAX_SESSIONS)) * 100.0;

        out << string(35, '-') << "\n";
        out << "Total locations visited: " << sessionCount << "\n";
        out << "Total document finds:    " << docsCount << "\n";
        out << "Percent of map explored: " << percentAreasVisited << "%\n";
        out << "Mission time limit:      " << missionTimeLimit << " minutes\n";

        out.close();
        cout << "Report saved to report.txt\n\n";
    }

    // ========================= REPORT =========================
    void showReport() const {
        cout << "\n==================== ADVENTURE SUMMARY ====================\n";

        cout << left << setw(20) << "Area"
            << setw(15) << "Documents" << "\n";
        cout << string(35, '-') << "\n";

        int docsCount = 0;
        for (int i = 0; i < sessionCount; ++i) {
            cout << left << setw(20) << sessions[i].areaName
                << setw(15) << (sessions[i].foundDocuments ? "Found" : "None") << "\n";
            if (sessions[i].foundDocuments) docsCount++;
        }

        double percentAreasVisited = (sessionCount / static_cast<double>(MAX_SESSIONS)) * 100.0;

        cout << string(35, '-') << "\n";
        cout << "Total locations visited: " << sessionCount << "\n";
        cout << "Total document finds:    " << docsCount << "\n";
        cout << "Percent of map explored: " << percentAreasVisited << "%\n";
        cout << "Mission time limit:      " << missionTimeLimit << " minutes\n\n";
    }

    // ========================= INVENTORY =========================
    void showInventory() const {
        cout << "\n--- Inventory ---\n";
        printInventory(inventory, inventoryCount);
        cout << "\n";
    }

    // ========================= MENUS =========================
    void outsideMenu() {
        int choice;
        do {
            cout << "==================== OUTSIDE THE CAVE ====================\n";
            cout << "1. Enter the cave\n";
            cout << "2. View inventory\n";
            cout << "3. View summary report\n";
            cout << "4. Save report to file\n";
            cout << "5. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-5: ";
                cin.clear();
                cin.ignore(INPUT_IGNORE, '\n');
            }
            cin.ignore(INPUT_IGNORE, '\n');

            switch (choice) {
            case 1:
                currentLocation = "Cave";
                addSession("Entrance Cave", false);
                caveMenu();
                break;
            case 2:
                showInventory();
                break;
            case 3:
                showReport();
                break;
            case 4:
                saveReportToFile();
                break;
            case 5:
                cout << "Exiting game. Goodbye, " << playerName << ".\n";
                return;
            default:
                cout << "Invalid choice.\n\n";
            }

        } while (true);
    }

    void caveMenu() {
        int choice;
        do {
            cout << "==================== INSIDE THE CAVE ====================\n";
            cout << "1. Leave cave\n";
            cout << "2. Go to lab door\n";
            cout << "3. View inventory\n";
            cout << "4. View summary report\n";
            cout << "5. Save report to file\n";
            cout << "6. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-6: ";
                cin.clear();
                cin.ignore(INPUT_IGNORE, '\n');
            }
            cin.ignore(INPUT_IGNORE, '\n');

            switch (choice) {
            case 1:
                currentLocation = "Outside";
                return;
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
                saveReportToFile();
                break;
            case 6:
                cout << "Exiting game.\n";
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
            cout << "5. Save report to file\n";
            cout << "6. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-6: ";
                cin.clear();
                cin.ignore(INPUT_IGNORE, '\n');
            }
            cin.ignore(INPUT_IGNORE, '\n');

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
                    cout << "You do not have the keycard.\n\n";
                }
                break;
            case 2:
                currentLocation = "Cave";
                return;
            case 3:
                showInventory();
                break;
            case 4:
                showReport();
                break;
            case 5:
                saveReportToFile();
                break;
            case 6:
                cout << "Exiting game.\n";
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
            cout << "4. Save report to file\n";
            cout << "5. Quit\n";
            cout << "Enter choice: ";

            while (!(cin >> choice)) {
                cout << "Invalid input. Enter 1-5: ";
                cin.clear();
                cin.ignore(INPUT_IGNORE, '\n');
            }
            cin.ignore(INPUT_IGNORE, '\n');

            switch (choice) {
            case 1:
                searchForDocuments();
                currentLocation = "Outside";
                return;
            case 2:
                showInventory();
                break;
            case 3:
                showReport();
                break;
            case 4:
                saveReportToFile();
                break;
            case 5:
                cout << "Exiting game.\n";
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

        if (inventoryCount < MAX_INVENTORY) {
            inventory[inventoryCount++] = "Research Documents";
        }

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
