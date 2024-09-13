#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Character {
protected:
    string name;
    int health;
    int attack;
    int defense;
public:
    Character(string n, int health) : name(n), health(health), attack(10), defense(5) {} //contains both name and health variable to change

    virtual void displayStats() { //displays all the stats upon call
        cout << "Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defense: " << defense << endl;
        cout << endl;
    }

    virtual void train() { //adds atk and def
        attack += 5;
        defense += 2;
        cout << "Training complete! Attack +5, Defense +2." << endl;
    }

    virtual void takeDamage(int damage) {
        health -= damage;
        cout << name << " took " << damage << " damage." << endl;
        if (health <= 0) {
            cout << name << " has been defeated!" << endl;
        }
    }

    virtual void saveToFile(string filename) { //saves file with input in main
        ofstream file(filename);
        if (file.is_open()) {
            file << name << " " << health << " " << attack << " " << defense << endl;
            file.close();
            cout << "Game saved successfully." << endl;
        }
        else {
            cout << "Unable to save game." << endl;
        }
    }

    virtual void loadFromFile(string filename) { //loads the file
        ifstream file(filename);
        if (file.is_open()) {
            file >> name >> health >> attack >> defense;
            file.close();
            cout << "Game loaded successfully." << endl;
        }
        else {
            cout << "Unable to load game." << endl;
        }
    }

    virtual void attackEnemy(Character* enemy) { //uses a random number to multiply with damage, can vary in damage due to rand
        int damageDealt = (rand() % attack) - enemy->getDefense();
        if (damageDealt <= 0) {
            damageDealt = 1; // At least 1 damage is applied
        }
        cout << name << " attacks " << enemy->getName() << " for " << damageDealt << " damage!" << endl;
        enemy->takeDamage(damageDealt);
    }

    string getName() { return name; }
    int getHealth() { return health; }
    int getAttack() { return attack; }
    int getDefense() { return defense; }
};

class Player : public Character {
public:
    Player(string n, int health) : Character(n, health) {} //train method that increases atk and def from character class

    void train() override {
        attack += 10;
        defense += 5;
        cout << "Training complete! Attack +10, Defense +5." << endl;
    }
};

class Enemy : public Character { //enemy functions, uses charactar class for base stats
public:
    Enemy(string n, int health) : Character(n, health) {}

    void attackPlayer(Player* player) {
        int damageDealt = (rand() % attack) - player->getDefense();
        if (damageDealt <= 0) {
            damageDealt = 1; // Ensure at least 1 damage is dealt
        }
        cout << name << " attacks " << player->getName() << " for " << damageDealt << " damage!" << endl;
        player->takeDamage(damageDealt);
    }
};

int main() {
    srand(time(0)); // this is a rrandom number generator

    string playerName;
    cout << "Enter your name: "; //enter name
    getline(cin, playerName);

    cout << "WELCOME TO GUMMY KOMBAT!!!" << endl;
    cout << endl;
    cout << "ITS ALL ABOUT CHANCE, SWING FIRST, OR DIE FIRST!!";

    // name of player and all of the gummy opponents and their healths and names
    Player player(playerName, 100);
    Enemy enemy("Gummy Exterminator Private 1", 100);
    Enemy enemy2("Gummy COMMANDER 2", 200);
    Enemy enemy3("Gummy WARLORD", 300);
    
    //training limit, once per opponent
    int traincount = 1;

    // Game loop
    while (player.getHealth() > 0 && enemy3.getHealth() > 0) { //game ends when you or the final boss dies
        cout << "\nPlayer's Turn:" << endl;
        player.displayStats(); //your stats 
        

        // displays all of enemies stats

        if (enemy.getHealth() > 0) {
            enemy.displayStats();
        }
        else if (enemy2.getHealth() > 0) {
            traincount = 1;
            enemy2.displayStats();
        }
        else if (enemy3.getHealth() > 0) {
            traincount = 1;
            enemy3.displayStats();
        }

        //all of your options, shown by cases
        cout << "1. Engage in Kombat" << endl;
        cout << "2. Train Character" << endl;
        cout << "3. Save Game" << endl;
        cout << "4. Load Game" << endl;
        cout << "5. Exit Game" << endl;
        cout << "Choose an action: " << endl;

        string filename;
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1:
            if (enemy.getHealth() > 0) {
                player.attackEnemy(&enemy);
            }
            else if (enemy2.getHealth() > 0) {
                player.attackEnemy(&enemy2);
            }
            else if (enemy3.getHealth() > 0) {
                player.attackEnemy(&enemy3);
            }
            break;
        case 2:
            if (traincount == 0) {
                cout << "YOU'VE ALREADY TRAINED, NOW FIGHT TILL THE DEATH!!!" << endl;
                break;
            }
            else if (traincount == 1) {
                traincount = traincount - 1;
                player.train();
            }
            break;
        case 3:
            cout << "Enter Savefile name please : " << endl; 
            cin >> filename;
            player.saveToFile(filename);
            break;
        case 4:
            cout << "Enter Loadfile name please : " << endl;
            cin >> filename;
            player.loadFromFile(filename);
            break;
        case 5:
            cout << "Exiting game, take care fellow Gummy........" << endl;
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }

        if (enemy.getHealth() > 0) {
            cout << "\nEnemy's Turn:" << endl;
            enemy.attackPlayer(&player);
        }
        else if (enemy2.getHealth() > 0) {
            cout << "\nEnemy's Turn:" << endl;
            enemy.attackPlayer(&player);
        }
        else if (enemy3.getHealth() > 0) {
            cout << "\nEnemy's Turn:" << endl;
            enemy.attackPlayer(&player);
        }
    }
    if (player.getHealth() <= 0) {
        cout << "Game Over!" << endl;
        cout << endl;
        cout << "YOU HAVE FALLEN GUMMY....im sorry..." << endl; //final message
    }
    else if (enemy.getHealth() <= 0){
        cout << endl;
        cout << "The WARLORD has FALLEN, good work GUMMY SOLIDER!!:" << endl; //final message if you win
    }
    return 0;
}
