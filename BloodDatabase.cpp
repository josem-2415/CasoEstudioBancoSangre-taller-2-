#include "BloodDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <algorithm>

using namespace std;

void BloodDatabase::displayProvinces() {
    std::cout << "Elige el departamento:\n";
    std::cout << "1. Putumayo\n";
    std::cout << "2. Cauca\n";
    std::cout << "3. Valle del Cauca\n";
    std::cout << "4. Amazonas\n";
    std::cout << "5. Risaralda\n";
    std::cout << "6. Antioquia\n";
    std::cout << "7. Norte de Santander\n";
    std::cout << "8. Chocó\n";
    std::cout << "9. Arauca\n";
    std::cout << "10. Guainía\n";
}

void BloodDatabase::displayBloodType() {
    std::cout << "Elige el tipo de sangre:\n";
    std::cout << "1. A+\n";
    std::cout << "2. A-\n";
    std::cout << "3. B+\n";
    std::cout << "4. B-\n";
    std::cout << "5. AB+\n";
    std::cout << "6. AB-\n";
    std::cout << "7. O+\n";
    std::cout << "8. O-\n";
}

void BloodDatabase::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    // system("clear");
#endif
}

void BloodDatabase::waitForKeyPress() {
    std::cout << "Presiona cualquier tecla para continuar...";
    std::cin.ignore();
    std::cin.get();
}

int BloodDatabase::getValidatedInput(const std::string& prompt) {
    int value;
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
                throw std::invalid_argument("La entrada contiene caracteres no numéricos");
            }
            value = std::stoi(input);
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << "Entrada no válida: " << e.what() << ". Por favor ingrese un número válido." << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Entrada fuera de rango. Por favor ingrese un número válido." << std::endl;
        }
    }
    return value;
}

void BloodDatabase::getDonorDetails() {
    clearConsole();
    std::cout << "Ingrese los detalles del donante\n";

    Donor newDonor;
    newDonor.setDonorId(getValidatedInput("Id: "));
    std::cout << "Nombre: ";
    std::string name; std::getline(std::cin, name);
    newDonor.setName(name);

    std::cout << "Edad: ";
    int age; std::cin >> age;
    newDonor.setAge(age);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Dirección: ";
    std::string address; std::getline(cin, address);
    newDonor.setAddress(address);

    displayProvinces();
    int district = getValidatedInput("Departamento (ingrese el número correspondiente): ");
    newDonor.setDistrict(district);

    displayBloodType();
    int bloodType = getValidatedInput("Tipo de Sangre (ingrese el número correspondiente): ");
    newDonor.setBloodType(bloodType);

    long long phone;
    while (true) {
        std::cout << "Número de móvil (10 dígitos, debe empezar por 3): ";
        std::string input;
        std::getline(std::cin, input);

        // Condiciones:
        // 1. Longitud 10
        // 2. Solo dígitos
        // 3. Primer dígito = '3'
        if (input.size() == 10 && 
            std::all_of(input.begin(), input.end(), ::isdigit) &&
            input[0] == '3') 
        {
            phone = std::stoll(input);
            break;
        } else {
            std::cout << "Error: el número debe tener 10 dígitos y empezar por 3.\n";
        }
    }
    newDonor.setNumber(phone);

    std::cout << "Unidades de sangre donadas: ";
    int units; std::cin >> units;
    newDonor.setUnits(units);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Fecha de donación (DD/MM/AAAA): ";
    std::string date; std::getline(std::cin, date);
    newDonor.setDate(date);

    donors.push_back(newDonor);
}

void BloodDatabase::writeDataToFile() {
    std::ofstream outfile(fileName, std::ios::app);
    if (!outfile) {
        std::cout << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    Donor d = donors.back();
    outfile << d.getDonorId() << ",    "
            << d.getName() << ",    "
            << d.getAge() << ",    "
            << d.getAddress() << ",    "
            << d.getDistrict() << ",    "
            << d.getBloodType() << ",    "
            << d.getNumber() << ",    "
            << d.getUnits() << ",    "
            << d.getDate() << std::endl;
    outfile.close();
}

void BloodDatabase::searchAndDisplay() const {
    clearConsole();
    displayProvinces();
    int provinceName = getValidatedInput("Ingrese el número del departamento: ");

    std::cout << "Ingrese la dirección (dejar en blanco para omitir): ";
    std::string addressFilter;
    std::getline(std::cin, addressFilter);

    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cout << "Error al abrir el archivo para leer." << std::endl;
        return;
    }

    std::vector<Donor> result;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        bool match = d.getDistrict() == provinceName &&
            (addressFilter.empty() || d.getAddress().find(addressFilter) != std::string::npos);
        if (match) {
            result.push_back(d);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No se encontraron personas del departamento " << provinceName;
        if (!addressFilter.empty()) {
            std::cout << " con dirección que contiene '" << addressFilter << "'";
        }
        std::cout << "." << std::endl;
    } else {
        for (const auto& d : result) {
            std::cout << "Nombre: " << d.getName() << std::endl;
            std::cout << "Edad: " << d.getAge() << std::endl;
            std::cout << "Dirección: " << d.getAddress() << std::endl;
            std::cout << "Departamento: " << d.getDistrict() << std::endl;
            std::cout << "Tipo de sangre: " << d.getBloodType() << std::endl;
            std::cout << "Número de móvil: " << d.getNumber() << std::endl;
            std::cout << "Unidades donadas: " << d.getUnits() << std::endl;
            std::cout << "Fecha: " << d.getDate() << std::endl;
            std::cout << std::endl;
        }
    }

    inFile.close();
    waitForKeyPress();
}

void BloodDatabase::deleteDonor(const std::string& donorName) {
    std::ifstream inFile(fileName);
    std::ofstream tempFile("temp.txt");
    if (!inFile || !tempFile) return;

    std::string line;
    bool found = false;
    while (std::getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        if (d.getName() == donorName) {
            found = true;
            std::cout << "Eliminar a " << d.getName() << "? [s/n]: ";
            char c; std::cin >> c;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (c == 's' || c == 'S') continue;
        }
        tempFile << d.getDonorId() << ",    "
                 << d.getName() << ",    "
                 << d.getAge() << ",    "
                 << d.getAddress() << ",    "
                 << d.getDistrict() << ",    "
                 << d.getBloodType() << ",    "
                 << d.getNumber() << ",    "
                 << d.getUnits() << ",    "
                 << d.getDate() << std::endl;
    }
    inFile.close(); tempFile.close();
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
    if (!found) std::cout << "No se encontró " << donorName << std::endl;
}

std::vector<Donor> BloodDatabase::getDonors(){
    std::ifstream inFile(fileName);
    std::vector<Donor> donors;
    std::string line;
    while (std::getline(inFile, line)) {
        donors.push_back(Donor::parseLine(line));
    }
    inFile.close();
    return donors;
}
