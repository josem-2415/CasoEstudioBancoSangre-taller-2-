#include "BloodDatabase.h"
#include "Donor.h"
#include "Reports.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

int main() {
  std::string donorName;
  BloodDatabase database;
  Reports reporte;
  int d = 3;
  int a = 43;
  int b = 3;
  int choice;

  while (true) {
    BloodDatabase::clearConsole();
    std::cout << " ░█████╗░██████╗░██╗░░░██╗███████╗  ██████╗░░█████╗░░░░░░██╗░"
                 "█████╗░\n"
                 " ██╔══██╗██╔══██╗██║░░░██║╚════██║  ██╔══██╗██╔══██╗░░░░░██║█"
                 "█╔══██╗\n"
                 " ██║░░╚═╝██████╔╝██║░░░██║░░███╔═╝  ██████╔╝██║░░██║░░░░░██║█"
                 "██████║\n"
                 " ██║░░██╗██╔══██╗██║░░░██║██╔══╝░░  ██╔══██╗██║░░██║██╗░░██║█"
                 "█╔══██║\n"
                 " ╚█████╔╝██║░░██║╚██████╔╝███████╗  ██║░░██║╚█████╔╝╚█████╔╝█"
                 "█║░░██║\n"
                 " ░╚════╝░╚═╝░░╚═╝░╚═════╝░╚══════╝  ╚═╝░░╚═╝░╚════╝░░╚════╝░╚"
                 "═╝░░╚═╝\n";
    std::cout << "1. Registrar donante\n";
    std::cout << "2. Buscar donante\n";
    std::cout << "3. Eliminar donante\n";
    std::cout << "4. Reportes\n";
    std::cout << "5. Unidades donadas\n";
    std::cout << "6. Reporte por año/departamento\n";
    std::cout << "7. Salir\n";
    std::cout << "Ingrese su elección: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1:
      database.getDonorDetails();
      database.writeDataToFile();
      break;

    case 2:
      database.searchAndDisplay();
      break;

    case 3:
      std::cout << "Ingrese el nombre del donante a eliminar: ";
      std::getline(std::cin, donorName);
      database.deleteDonor(donorName);
      BloodDatabase::waitForKeyPress();
      break;

    case 4:
      reporte.loadDataBase(database.getDonors());
      std::cout << "Total registros: " << reporte.donorTotal() << endl;

      std::cout
          << "El total de registros del Valle del Cauca, 43 años y B+ es: "
          << reporte.donorTotal(d, a, b) << endl
          << endl;

      d = 8;
      b = 1;
      std::cout << "El total de registros de Chocoanos A+ es: "
                << reporte.donorTotal(d, b) << endl
                << endl;
      d = 9;
      b = 8;
      std::cout << "El total de registros de Aracaunos O- es: "
                << reporte.donorTotal(d, b) << endl
                << endl;
      d = 3;
      b = 3;
      std::cout << "El total de registros de Valle Caucanos B+ es: "
                << reporte.donorTotal(d, b) << endl
                << endl;

      double auxedad;
      d = 8;
      auxedad = reporte.donorMeanAge(d);
      d = 9;
      auxedad = (auxedad + reporte.donorMeanAge(d)) / 2;
      d = 3;
      auxedad = (auxedad + reporte.donorMeanAge(d)) / 2;
      std::cout << "El promedio de edad los individuos de Choco, Arauca y "
                   "Valle de Cauca: "
                << auxedad << endl
                << endl;

      d = 3;
      b = 3;
      std::cout << "El total de registros mayores de edad vallecaucanos B+: "
                << reporte.donorAdult(d, b) << endl
                << endl;
      break;

    case 5:
      std::cout << "Ingrese nombre para ver unidades donadas: ";
      std::getline(std::cin, donorName);
      reporte.bloodDonorUnits(donorName);
      break;

    case 6:
      reporte.loadDataBase(database.getDonors()); // 🔹 Esto llena auxDono
      reporte.yearAndReport();
      break;

    case 7:
      return 0;

    default:
      std::cout << "Opción no válida.\n";
      BloodDatabase::waitForKeyPress();
      break;
    }
  }
}
