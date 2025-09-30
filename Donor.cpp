#include "Donor.h"
#include <sstream>
#include <iostream>
#include <algorithm>

// ---------- Métodos principales ----------
void Donor::donorDetails() const {
    std::cout << "Nombre del donante: " << name << std::endl;
    std::cout << "Edad del donante: " << age << std::endl;
    std::cout << "Distrito del donante: " << district << std::endl;
    std::cout << "Tipo de sangre del donante: " << bloodType << std::endl;
    std::cout << "Teléfono: " << number << std::endl;
    std::cout << "Unidades donadas: " << units << std::endl;
    std::cout << "Fecha última donación: " << date << std::endl;
}

Donor Donor::parseLine(const std::string& line) {
    Donor d;
    std::stringstream ss(line);
    std::string token;

    getline(ss, token, ','); d.setDonorId(std::stoi(trim(token)));
    getline(ss, token, ','); d.setName(trim(token));
    getline(ss, token, ','); d.setAge(std::stoi(trim(token)));
    getline(ss, token, ','); d.setAddress(trim(token));
    getline(ss, token, ','); d.setDistrict(std::stoi(trim(token)));
    getline(ss, token, ','); d.setBloodType(std::stoi(trim(token)));
    getline(ss, token, ','); d.setNumber(std::stoll(trim(token)));
    getline(ss, token, ','); d.setUnits(std::stoi(trim(token)));
    getline(ss, token, ','); d.setDate(trim(token));

    return d;
}

std::string Donor::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// ---------- Getters ----------
int Donor::getDonorId() const { return donorId; }
std::string Donor::getName() const { return name; }
int Donor::getAge() const { return age; }
std::string Donor::getAddress() const { return address; }
int Donor::getDistrict() const { return district; }
int Donor::getBloodType() const { return bloodType; }
long long Donor::getNumber() const { return number; }
int Donor::getUnits() const { return units; }
std::string Donor::getDate() const { return date; }

// ---------- Setters ----------
void Donor::setDonorId(int id) { donorId = id; }
void Donor::setName(const std::string& n) { name = n; }
void Donor::setAge(int a) { age = a; }
void Donor::setAddress(const std::string& addr) { address = addr; }
void Donor::setDistrict(int d) { district = d; }
void Donor::setBloodType(int bt) { bloodType = bt; }
void Donor::setNumber(long long num) { number = num; }
void Donor::setUnits(int u) { units = u; }
void Donor::setDate(const std::string& d) { date = d; }

