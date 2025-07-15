#include <iostream>
#include <string>
#include <limits>
using namespace std;

/*
===============================================================================
File:           ArkCulator_v5.2-bng.cpp
Author:         AEYCEN [Discord: aeycen] / TRAYVED [Discord: trayved]
Update date:    11. July 2025
Version:        5.2-bng
Description:    This calculator is used to determine the amount of ammunition
                and cost of resources required to destroy structures in
                Ark: Survival Evolved and Ark: Survival Ascended. The program
                allows you to enter the type of weapon, the HP and material of
                the structure and the presence of 6x cave damage. It then
                calculates the amount of explosives/ammunition needed and
                displays the resource cost of crafting the ammo.
                Adjusted to the ASE "Beginners Next Gen" servers.
===============================================================================
*/

const string RESET = "\033[0m";
const string THIN = "\033[22m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string BLUE = "\033[34m";
const string GREEN = "\033[32m";
const string PURPLE = "\033[35m";
const string CYAN = "\033[36m";
const string YELLOW = "\033[33m";

const string programInfo = "\033[3m\033[1m\033[33mArk\033[32mCulator\033[0m\033[0m v5.2-bng (11.07.25) | Copyright 2022-2025 AEYCEN / TRAYVED | MIT License";

enum class Weapon
{
    C4,
    Cannon,
    Grenade,
    Catapult
};

enum class Material
{
    Wood,
    Stone,
    Metal,
    Tek
};

double calculateDamage(const Weapon weapon, const Material material)
{
    double damage = 0.0;

    switch (weapon) {
    case Weapon::C4:
        switch (material) {
        case Material::Wood:
            damage = 11813.0;
            break;
        case Material::Stone:
            damage = 99999.0;
            break;
        case Material::Metal:
            damage = 3544.0;
            break;
        case Material::Tek:
            damage = 788.0;
            break;
        }
        break;
    case Weapon::Cannon:
        switch (material) {
        case Material::Wood:
            damage = 99999.0;
            break;
        case Material::Stone:
            damage = 3446.0;
            break;
        case Material::Metal:
            damage = 355.0;
            break;
        case Material::Tek:
            damage = 40.0;
            break;
        }
        break;
    case Weapon::Grenade:
        switch (material) {
        case Material::Wood:
            damage = 788.0;
            break;
        case Material::Stone:
            damage = 1838.0;
            break;
        case Material::Metal:
            damage = 237.0;
            break;
        case Material::Tek:
            damage = 53.0;
            break;
        }
        break;
    case Weapon::Catapult:
        switch (material) {
        case Material::Wood:
            damage = 15750.0;
            break;
        case Material::Stone:
            damage = 700.0;
            break;
        case Material::Metal:
        case Material::Tek:
            return 0.0;
        }
        break;
    default:
        return 0.0;
    }

    return damage;
}

void calculateCost(const Weapon weapon, const int amount)
{
    int gunpowder = 0;
    int crystal = 0;
    int cement = 0;
    int fiber = 0;
    int hide = 0;
    int polymer = 0;
    int electronics = 0;
    int metal = 0;
    int obsidian = 0;
    int oil = 0;
    int stone = 0;

    switch (weapon) {
    case Weapon::C4:
        gunpowder = 300;
        crystal = 50;
        cement = 25;
        fiber = 250;
        hide = 25;
        polymer = 25;
        electronics = 25;
        break;
    case Weapon::Cannon:
        metal = 80;
        gunpowder = 30;
        cement = 20;
        obsidian = 4;
        break;
    case Weapon::Grenade:
        fiber = 15;
        stone = 20;
        gunpowder = 30;
        hide = 5;
        metal = 2;
        oil = 4;
        break;
    case Weapon::Catapult:
        stone = 30;
        metal = 3;
        break;
    }

    // Ressourcenkosten berechnen und ausgeben
    cout << BOLD << "Resources needed to craft:" << THIN << endl;
    if (gunpowder > 0)
        cout << "Gunpowder: " << gunpowder * amount << endl;
    if (crystal > 0)
        cout << "Crystal: " << crystal * amount << endl;
    if (cement > 0)
        cout << "Cementing paste: " << cement * amount << endl;
    if (fiber > 0)
        cout << "Fiber: " << fiber * amount << endl;
    if (hide > 0)
        cout << "Hide: " << hide * amount << endl;
    if (polymer > 0)
        cout << "Polymer: " << polymer * amount << endl;
    if (electronics > 0)
        cout << "Electronics: " << electronics * amount << endl;
    if (metal > 0)
        cout << "Metal: " << metal * amount << endl;
    if (obsidian > 0)
        cout << "Obsidian: " << obsidian * amount << endl;
    if (oil > 0)
        cout << "Oil: " << oil * amount << endl;
    if (stone > 0)
        cout << "Stone: " << stone * amount << endl;

    cout << endl;
}

bool isValidIntInput(const string& input)
{
    try {
        const int value = stoi(input);
        return value >= 1 && value <= 100000;
    } catch (const invalid_argument& e) {
        return false;
    } catch (const out_of_range& e) {
        return false;
    }
}

int main()
{
    cout << programInfo << endl;

    while (true) {
        try {
            cout << endl;

            Weapon weapon;
            int weaponInput;
            string displayWeapon;
            string ammoName;
            while (true) {
                cout << "Enter " << BOLD << "weapon" << THIN << " [" << YELLOW << "1" << RESET << "(C4)/" << YELLOW << "2" << RESET << "(Cannon)/" << YELLOW << "3" << RESET << "(Grenade)/" << YELLOW << "4" << RESET << "(Catapult)] > ";
                cin >> weaponInput;

                if (weaponInput >= 1 && weaponInput <= 4) {
                    break;
                }
                cout << RED << "Invalid weapon type. Please enter 1, 2, 3 or 4." << RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            switch (weaponInput) {
                case 1:
                    weapon = Weapon::C4;
                    displayWeapon = "C4";
                    ammoName = "C4";
                    break;
                case 2:
                    weapon = Weapon::Cannon;
                    displayWeapon = "Cannon";
                    ammoName = "Cannon Balls";
                    break;
                case 3:
                    weapon = Weapon::Grenade;
                    displayWeapon = "Grenade";
                    ammoName = "Grenades";
                    break;
                case 4:
                    weapon = Weapon::Catapult;
                    displayWeapon = "Catapult";
                    ammoName = "Boulders";
                    break;
            }

            Material material;
            string materialInput;
            string displayStructure;
            while (true) {
                cout << "[" << BLUE << displayWeapon << RESET << "] Enter " << BOLD << "material" << THIN << " of structure [" << YELLOW << "w" << RESET << "ood/" << YELLOW << "s" << RESET << "tone/" << YELLOW << "m" << RESET << "etal/" << YELLOW << "t" << RESET << "ek] > ";
                cin >> materialInput;

                if (materialInput == "Wood" || materialInput == "wood" || materialInput == "w") {
                    material = Material::Wood;
                    displayStructure = "Wood";
                    break;
                } else if (materialInput == "Stone" || materialInput == "stone" || materialInput == "s") {
                    material = Material::Stone;
                    displayStructure = "Stone";
                    break;
                } else if (materialInput == "Metal" || materialInput == "metal" || materialInput == "m") {
                    material = Material::Metal;
                    displayStructure = "Metal";
                    break;
                } else if (materialInput == "Tek" || materialInput == "tek" || materialInput == "t") {
                    material = Material::Tek;
                    displayStructure = "Tek";
                    break;
                } else {
                    cout << RED << "Invalid material input. Please choose from 'wood/w', 'stone/s', 'metal/m' or 'tek/t'" << RESET << endl;
                }
            }

            double damage = calculateDamage(weapon, material);
            if (damage <= 0.0) {
                cout << "------------------------------------------------------------------------------------------" << endl << endl;
                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "] This structure is indestructible with this weapon" << endl << endl;

                cout << endl;
                cout << "Note: Press " << YELLOW << "Ctrl+C" << RESET << " at any time to end the program" << endl << endl;
                cout << "<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-< Restart \033[3m\033[1m\033[33mArk\033[32mCulator\033[0m\033[0m >->->->->->->->->->->->->->->->->->" << endl;
                continue;
            }

            string hpInput;
            int hp = 0;
            while (true) {
                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "] Enter " << BOLD << "HP" << THIN << " of structure > ";
                cin >> hpInput;

                if (isValidIntInput(hpInput)) {
                    try {
                        hp = stoi(hpInput);
                    } catch (const exception& e) {
                        cout << RED << "Error: Invalid HP input. Please enter a valid integer." << RESET << endl;
                        continue;
                    }

                    if (hp >= 1 && hp <= 100000) {
                        break;
                    }
                }

                cout << RED << "Invalid HP input. Please enter a valid integer between 1 and 100000" << RESET << endl;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            string caveDamageInput;
            string displayCave;
            while (true) {
                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "|" << CYAN << hp << " HP" << RESET << "] " << BOLD << "Cave" << THIN << " damage? [" << YELLOW << "y" << RESET << "es/" << YELLOW << "n" << RESET << "o] > ";
                cin >> caveDamageInput;

                if (caveDamageInput == "yes" || caveDamageInput == "y") {
                    displayCave = "Inside";
                    break;
                } else if (caveDamageInput == "no" || caveDamageInput == "n") {
                    displayCave = "No";
                    break;
                } else {
                    cout << RED << "Invalid input. Please enter 'yes/y' or 'no/n'." << RESET << endl;
                }
            }

            if (caveDamageInput == "yes" || caveDamageInput == "y") {
                damage *= 6;
            }

            cout << "------------------------------------------------------------------------------------------" << endl << endl;

            if (damage <= 0.0) {
                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET
                     << "|" << CYAN << hp << " HP" << RESET << "|" << GREEN << displayCave << " Cave" << RESET
                     << "] This structure is indestructible with this weapon." << endl << endl;
            } else {
                int amount = static_cast<int>(hp / damage + 0.99);
                if (amount < 1) amount = 1;

                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "|" << CYAN << hp << " HP" << RESET << "|" << GREEN << displayCave << " Cave" << RESET << "] " << ammoName << " needed to destroy: " << BOLD << amount << THIN << endl << endl;
                calculateCost(weapon, amount);
            }

            cout << "Note: Press " << YELLOW << "Ctrl+C" << RESET << " at any time to end the program" << endl << endl;
            cout << "<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-< Restart \033[3m\033[1m\033[33mArk\033[32mCulator\033[0m\033[0m >->->->->->->->->->->->->->->->->->" << endl;
            continue;
        } catch (const exception& e) {
            cout << RED << "Unexpected Error: " << e.what() << RESET << endl << endl;
            cout << "Press Enter to exit..." << endl;
            cin.ignore();
            cin.get();
            return 1;
        }
    }

    return 0;
}
