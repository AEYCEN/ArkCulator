#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

/*
===============================================================================
File:           ArkCulator.cpp
Author:         AEYCEN [Discord: aeycen] / TRAYVED [Discord: trayved]
Update date:    15. July 2025
Version:        5.3
Description:    This calculator is used to determine the amount of ammunition
                and cost of resources required to destroy structures in
                Ark: Survival Evolved and Ark: Survival Ascended. The program
                allows you to enter the type of weapon, the HP and material of
                the structure and the presence of 6x cave damage. It then
                calculates the amount of explosives/ammunition needed and
                displays the resource cost of crafting the ammo. Integrated
                adjusted BNG mode for the ASE "Beginners Next Gen" servers.
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

const string programInfo = "\033[3m\033[1m\033[33mArk\033[32mCulator\033[0m\033[0m v5.3 (15.07.25) | Copyright 2022-2025 AEYCEN / TRAYVED | MIT License";

enum class Weapon
{
    C4,
    Cannon,
    Catapult,
    Grenade,
    RocketLauncher,
    TekGrenade,
    TekRifle
};

enum class StructureType
{
    Wood,
    Stone,
    Metal,
    Tek
};

double calculateDamage(const Weapon weapon, const StructureType structureType, double qualityFactor)
{
    double damage = 0.0;

    switch (weapon) {
    case Weapon::C4:
        switch (structureType) {
            case StructureType::Wood:
                damage = 11813.0;
                break;
            case StructureType::Stone:
                damage = 99999.0;
                break;
            case StructureType::Metal:
                damage = 3544.0;
                break;
            case StructureType::Tek:
                damage = 788.0;
                break;
        }
        break;
    case Weapon::Cannon:
        switch (structureType) {
        case StructureType::Wood:
            damage = 99999.0;
            break;
        case StructureType::Stone:
            damage = 3446.0;
            break;
        case StructureType::Metal:
            damage = 355.0;
            break;
        case StructureType::Tek:
            damage = 40.0;
            break;
        }
        break;
    case Weapon::Catapult:
        switch (structureType) {
            case StructureType::Wood:
                damage = 15750.0;
                break;
            case StructureType::Stone:
                damage = 700.0;
                break;
            case StructureType::Metal:
            case StructureType::Tek:
                return 0.0;
                break;
        }
        break;
    case Weapon::Grenade:
        switch (structureType) {
        case StructureType::Wood:
            damage = 788.0;
            break;
        case StructureType::Stone:
            damage = 1838.0;
            break;
        case StructureType::Metal:
            damage = 237.0;
            break;
        case StructureType::Tek:
            damage = 53.0;
            break;
        }
        break;
    case Weapon::RocketLauncher:
        switch (structureType) {
        case StructureType::Wood:
            damage = 7350.0;
            break;
        case StructureType::Stone:
            damage = 99999.0;
            break;
        case StructureType::Metal:
            damage = 2205.0;
            break;
        case StructureType::Tek:
            damage = 596.0;
            break;
        }
        break;
    case Weapon::TekGrenade:
        switch (structureType) {
        case StructureType::Wood:
            damage = 1115.0;
            break;
        case StructureType::Stone:
            damage = 612.0;
            break;
        case StructureType::Metal:
            damage = 59.0;
            break;
        case StructureType::Tek:
            damage = 385.0;
            break;
        }
        break;
    case Weapon::TekRifle:
        switch (structureType) {
        case StructureType::Wood:
            damage = 536.0 * qualityFactor;
            break;
        case StructureType::Stone:
            damage = 294.0 * qualityFactor;
            break;
        case StructureType::Metal:
            damage = 29.0 * qualityFactor;
            break;
        case StructureType::Tek:
            damage = 185.0 * qualityFactor;
            break;
        }
        break;
    default:
        return 0.0;
    }

    return damage;
}

void calculateCost(const Weapon weapon, int amount, bool bngMode)
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
    double element = 0;

    string usingVerb = " to craft";

    switch (weapon) {
    case Weapon::C4:
        gunpowder = bngMode ? 300 : 60;
        crystal = bngMode ? 50 : 10;
        cement = bngMode ? 25 : 5;
        fiber = bngMode ? 250 : 50;
        hide = bngMode ? 25 : 5;
        polymer = bngMode ? 25 : 5;
        electronics = bngMode ? 25 : 5;
        break;
    case Weapon::Cannon:
        metal = 80;
        gunpowder = 30;
        cement = 20;
        obsidian = 4;
        break;
    case Weapon::Catapult:
        stone = 30;
        metal = 3;
        break;
    case Weapon::Grenade:
        fiber = 15;
        stone = 20;
        gunpowder = 30;
        hide = 5;
        metal = 2;
        oil = 4;
        break;
    case Weapon::RocketLauncher:
        gunpowder = 40;
        crystal = 10;
        cement = 20;
        polymer = 10;
        metal = 12;
        break;
    case Weapon::TekGrenade:
        amount = ceil(static_cast<double>(amount) / 3);
        element = 1;
        crystal = 40;
        cement = 10;
        metal = 30;
        polymer = 30;
        gunpowder = 60;
        break;
    case Weapon::TekRifle:
        usingVerb = "";
        element = 0.02;
        break;
    }

    // Ressourcenkosten berechnen und ausgeben
    cout << BOLD << "Resources needed" << usingVerb << ":" << THIN << endl;
    if (gunpowder > 0)
        cout << BOLD << gunpowder * amount << THIN << " Gunpowder" << endl;
    if (crystal > 0)
        cout << BOLD << crystal * amount << THIN << " Crystal" << endl;
    if (cement > 0)
        cout << BOLD << cement * amount << THIN << " Cementing paste" << endl;
    if (fiber > 0)
        cout << BOLD << fiber * amount << THIN << " Fiber" << endl;
    if (hide > 0)
        cout << BOLD << hide * amount << THIN << " Hide" << endl;
    if (polymer > 0)
        cout << BOLD << polymer * amount << THIN << " Polymer" << endl;
    if (electronics > 0)
        cout << BOLD << electronics * amount << THIN << " Electronics" << endl;
    if (metal > 0)
        cout << BOLD << metal * amount << THIN << " Metal" << endl;
    if (obsidian > 0)
        cout << BOLD << obsidian * amount << THIN << " Obsidian" << endl;
    if (oil > 0)
        cout << BOLD << oil * amount << THIN << " Oil" << endl;
    if (stone > 0)
        cout << BOLD << stone * amount << THIN << " Stone" << endl;
    if (element > 0)
        cout << BOLD << ceil(element * amount) << THIN << " Element" << endl;

    cout << endl;
}

bool isValidIntInput(const string& input, int maxInput)
{
    try {
        const int value = stoi(input);
        return value >= 1 && value <= maxInput;
    } catch (const invalid_argument& e) {
        return false;
    } catch (const out_of_range& e) {
        return false;
    }
}

int main()
{
    cout << programInfo << endl << endl;

    string modeInput;
    bool bngMode = false;

    cout << "Enter calculator " << BOLD << "mode" << THIN << " [" << YELLOW << "ENTER" << RESET << " for normal / " << YELLOW << "bng" << RESET << " for Beginners Next Gen] ";
    while (true) {
        cout << "> ";
        getline(cin, modeInput);

        if (modeInput.empty() || modeInput == "enter") {
            bngMode = false;
            break;
        } else if (modeInput == "bng") {
            bngMode = true;
            break;
        }

        cout << RED << "Invalid mode. Please press ENTER or enter 'bng'." << RESET << endl;
    }

    while (true) {
        try {
            cout << endl;

            // Weapon input //
            Weapon weapon;
            string weaponInput = "";
            string displayWeapon = "";
            string ammoName = "";
            int maxWeaponNumber = bngMode ? 4 : 7;

            cout << "Enter " << BOLD << "weapon" << THIN << ":" << endl;
            if (bngMode) {
                cout << YELLOW << " 1 " << RESET << "- C4" << endl
                     << YELLOW << " 2 " << RESET << "- Cannon" << endl
                     << YELLOW << " 3 " << RESET << "- Catapult" << endl
                     << YELLOW << " 4 " << RESET << "- Grenade" << endl;
            } else {
                cout << YELLOW << " 1 " << RESET << "- C4" << endl
                     << YELLOW << " 2 " << RESET << "- Cannon" << endl
                     << YELLOW << " 3 " << RESET << "- Catapult" << endl
                     << YELLOW << " 4 " << RESET << "- Grenade" << endl
                     << YELLOW << " 5 " << RESET << "- Rocket Launcher" << endl
                     << YELLOW << " 6 " << RESET << "- Tek Grenade" << endl
                     << YELLOW << " 7 " << RESET << "- Tek Rifle" << endl;
            }

            while (true) {
                cout << "> ";
                getline(cin, weaponInput);

                bool isNumeric = !weaponInput.empty() && std::all_of(weaponInput.begin(), weaponInput.end(), ::isdigit);
                if (!isNumeric) {
                    std::transform(weaponInput.begin(), weaponInput.end(), weaponInput.begin(),
                        [](unsigned char c) { return std::tolower(c); });
                }

                if (weaponInput == "1" || weaponInput == "c4") {
                    weapon = Weapon::C4;
                    displayWeapon = "C4";
                    ammoName = "C4";
                    break;
                } else if (weaponInput == "2" || weaponInput == "cannon") {
                    weapon = Weapon::Cannon;
                    displayWeapon = "Cannon";
                    ammoName = "Cannon Balls";
                    break;
                } else if (weaponInput == "3" || weaponInput == "catapult") {
                    weapon = Weapon::Catapult;
                    displayWeapon = "Catapult";
                    ammoName = "Boulders";
                    break;
                } else if (weaponInput == "4" || weaponInput == "grenade") {
                    weapon = Weapon::Grenade;
                    displayWeapon = "Grenade";
                    ammoName = "Grenades";
                    break;
                } else if (bngMode == false && (weaponInput == "5" || weaponInput == "rocket launcher")) {
                    weapon = Weapon::RocketLauncher;
                    displayWeapon = "Rocket Launcher";
                    ammoName = "Rocket Propelled Grenades";
                    break;
                } else if (bngMode == false && (weaponInput == "6" || weaponInput == "tek grenade")) {
                    weapon = Weapon::TekGrenade;
                    displayWeapon = "Tek Grenade";
                    ammoName = "Tek Grenades";
                    break;
                } else if (bngMode == false && (weaponInput == "7" || weaponInput == "tek rifle")) {
                    weapon = Weapon::TekRifle;
                    displayWeapon = "Tek Rifle";
                    ammoName = "Shots";
                    break;
                }

                cout << RED << "Invalid weapon type. Please enter a number between 1 and " << maxWeaponNumber << " or the weapon name." << RESET << endl;
            }

            // Quality input //
			double qualityFactor = 1;
            if (weapon == Weapon::TekRifle) {
                string qualityInput = "";
                double quality = 100;

                cout << "[" << BLUE << displayWeapon << RESET << "] Enter " << BOLD << "quality" << THIN << " of tek rifle ";

                while (true) {
                    cout << "> ";
                    getline(cin, qualityInput);

                    replace(qualityInput.begin(), qualityInput.end(), ',', '.');
                    try {
                        quality = stod(qualityInput);

                        if (quality >= 100.0 && quality <= 200.0) {
                            displayWeapon += " " + qualityInput + "%";
							qualityFactor = quality / 100.0;
                            break;
                        } else {
                            cout << RED << "Invalid quality input. Number must be between 100 and 200." << RESET << endl;
                        }
                    } catch (const exception& e) {
                        cout << RED << "Invalid quality input. Please enter a decimal number between 100 and 200." << RESET << endl;
                    }
                }
            }

            // StructureType input //
            StructureType structureType;
            string structureTypeInput = "";
            string displayStructure = "";

            cout << "[" << BLUE << displayWeapon << RESET << "] Enter " << BOLD << "material" << THIN << " of structure [" << YELLOW << "w" << RESET << "ood/" << YELLOW << "s" << RESET << "tone/" << YELLOW << "m" << RESET << "etal/" << YELLOW << "t" << RESET << "ek] ";

            while (true) {
                cout << "> ";
                getline(cin, structureTypeInput);

                if (structureTypeInput == "Wood" || structureTypeInput == "wood" || structureTypeInput == "w") {
                    structureType = StructureType::Wood;
                    displayStructure = "Wood";
                    break;
                } else if (structureTypeInput == "Stone" || structureTypeInput == "stone" || structureTypeInput == "s") {
                    structureType = StructureType::Stone;
                    displayStructure = "Stone";
                    break;
                } else if (structureTypeInput == "Metal" || structureTypeInput == "metal" || structureTypeInput == "m") {
                    structureType = StructureType::Metal;
                    displayStructure = "Metal";
                    break;
                } else if (structureTypeInput == "Tek" || structureTypeInput == "tek" || structureTypeInput == "t") {
                    structureType = StructureType::Tek;
                    displayStructure = "Tek";
                    break;
                }

                cout << RED << "Invalid material input. Please choose from 'wood/w', 'stone/s', 'metal/m' or 'tek/t'" << RESET << endl;
            }

            // Check if structureType is destructible //
            double damage = calculateDamage(weapon, structureType, qualityFactor);
            if (damage <= 0.0) {
                cout << "------------------------------------------------------------------------------------------" << endl << endl;
                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "] This structure is indestructible with this weapon" << endl << endl;

                cout << endl;
                cout << "Note: Press " << YELLOW << "Ctrl+C" << RESET << " at any time to end the program" << endl << endl;
                cout << "<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-< Restart \033[3m\033[1m\033[33mArk\033[32mCulator\033[0m\033[0m >->->->->->->->->->->->->->->->->->" << endl;
                continue;
            }

            // HP input //
            string hpInput = "";
            int hp = 0;

            cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "] Enter " << BOLD << "HP" << THIN << " of structure ";

            while (true) {
                cout << "> ";
                getline(cin, hpInput);

                int maxInput = bngMode ? 100000 : 250000;
                if (isValidIntInput(hpInput, maxInput)) {
                    try {
                        hp = stoi(hpInput);
                    } catch (const exception& e) {
                        cout << RED << "Invalid HP input. Please enter a valid integer." << RESET << endl;
                        continue;
                    }

                    if (hp >= 1 && hp <= maxInput) {
                        break;
                    }
                }

                cout << RED << "Invalid HP input. Please enter a valid integer between 1 and " << maxInput << RESET << endl;
            }

            // Cave damage input //
            string caveDamageInput = "";
            string displayCave = "";

            cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "|" << CYAN << hp << " HP" << RESET << "] " << BOLD << "Cave" << THIN << " damage? [" << YELLOW << "y" << RESET << "es/" << YELLOW << "n" << RESET << "o] ";

            while (true) {
                cout << "> ";
                getline(cin, caveDamageInput);

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

            // Calculation output //
            if (damage <= 0.0) {
                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET
                     << "|" << CYAN << hp << " HP" << RESET << "|" << GREEN << displayCave << " Cave" << RESET
                     << "] This structure is indestructible with this weapon." << endl << endl;
            } else {
                int amount = static_cast<int>(hp / damage + 0.99);
                if (amount < 1) amount = 1;

                cout << "[" << BLUE << displayWeapon << RESET << "|" << PURPLE << displayStructure << RESET << "|" << CYAN << hp << " HP" << RESET << "|" << GREEN << displayCave << " Cave" << RESET << "] " << ammoName << " needed to destroy: " << BOLD << amount << THIN << endl << endl;
                calculateCost(weapon, amount, bngMode);
            }

            cout << "Note: Press " << YELLOW << "Ctrl+C" << RESET << " at any time to end the program" << endl << endl;
            if (bngMode) {
                cout << "<-<-<-<-<-<-<-<-<-<-<-<-<-<-< Restart \033[3m\033[1m\033[33mArk\033[32mCulator\033[0m\033[0m in BNG mode >->->->->->->->->->->->->->->" << endl;
            } else {
                cout << "<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-< Restart \033[3m\033[1m\033[33mArk\033[32mCulator\033[0m\033[0m >->->->->->->->->->->->->->->->->->" << endl;
            }
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
