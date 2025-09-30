/* 
Clase: BloodDataBase
Curso: Fundamanetos de programacion orientada a objetos (FPOO)
UNIVERSIDAD EL VALLE
informacion CRC:
Responsabilidades:
-Gestionar y administrar la base de datos completa de donantes de sangre, incluyendo operaciones de creación,
lectura, actualización y eliminación de registros.
-Mostrar interfaz de usuario para permitir la intereccion de la perosna con el sistema, donde le muestra el menu
, las opciones y los resultados.
-Manejar la resitencia de datos en archivos, garantizando que la información se almacene y recupere correctamente.
-Validar y procesar entradas del usuario, asegurando la integridad y corrección de los datos ingresados.
-Coordinar las operaciones del sistema entre las diferentes funcionalidades y la interfaz de usuario.

Colaboradores:
-Colabora con la clase Donor, que representa a cada donante individual y proporciona la estructura de datos para almacenar la información.
-Interactúa con std::vector para gestionar colecciones de objetos Donor en memoria.
-Utiliza std::fstream para operaciones de lectura y escritura en archivos de persistencia.
-Colabora con std::cin y std::cout para la interacción con el usuario mediante consola.

*/
#ifndef BLOODDATABASE_H
#define BLOODDATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Donor.h"

class BloodDatabase {
private:
    const std::string fileName = "data.txt";
    std::vector<Donor> donors;

    static void displayProvinces();
    static void displayBloodType();
public:
    static void clearConsole();
    static void waitForKeyPress();
    static int getValidatedInput(const std::string& prompt);

    void getDonorDetails();
    void writeDataToFile();
    void searchAndDisplay() const;
    void deleteDonor(const std::string& donorName);
    std::vector<Donor> getDonors();
};

#endif // BLOODDATABASE_H
