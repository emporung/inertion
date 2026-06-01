#include "inertia.h"
#include <iostream>
#include <Eigen/Dense>

int main() {
    while (true) {
        std::cout << "\n=== Тензор инерции ===\n";
        std::cout << "1 - Куб\n";
        std::cout << "2 - Сфера\n";
        std::cout << "3 - Параллелепипед\n";
        std::cout << "4 - Цилиндр\n";
        std::cout << "0 - Выход из программы\n";
        
        int choice = (int)readFloat("Выберите тело (0-4): ");
        
        if (choice == 0) {
            std::cout << "Выход из программы. До свидания!\n";
            break;
        }
        
        if (choice < 1 || choice > 4) {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            continue;
        }
        
        float m = readFloat("Масса (кг): ");
        float x = readFloat("Абсцисса оси: ");
        float y = readFloat("Ордината оси: ");
        float z = readFloat("Аппликата оси: ");
        Eigen::Vector3f axis = normalizeVector(x, y, z);
        
        Eigen::Matrix3f I;
        float a = 0, b = 0, c = 0, r = 0, h = 0;
        
        switch (choice) {
            case 1:
                a = readFloat("Сторона куба (м): ");
                I = inertiaCube(m, a);
                break;
            case 2:
                r = readFloat("Радиус сферы (м): ");
                I = inertiaSphere(m, r);
                break;
            case 3:
                a = readFloat("Длина по X (м): ");
                b = readFloat("Длина по Y (м): ");
                c = readFloat("Длина по Z (м): ");
                I = inertiaBox(m, a, b, c);
                break;
            case 4:
                r = readFloat("Радиус (м): ");
                h = readFloat("Высота цилиндра: ");
                I = inertiaCylinder(m, r, h);
                break;
        }
        
        float moment = I(0,0) * axis(0)*axis(0) +
                       I(1,1) * axis(1)*axis(1) +
                       I(2,2) * axis(2)*axis(2);
        
        std::cout << "Тензор инерции:\n" << I << std::endl;
        std::cout << "Момент относительно оси ("
                  << axis(0) << ", " << axis(1) << ", " << axis(2)
                  << "): " << moment << std::endl;
        
        float rx = 1.0f / sqrt(I(0,0));
        float ry = 1.0f / sqrt(I(1,1));
        float rz = 1.0f / sqrt(I(2,2));
        std::cout << "Полуоси эллипсоида: "
                  << rx << ", " << ry << ", " << rz << std::endl;
        
        float I1 = I.trace();
        float I2 = I(0,0)*I(1,1) + I(1,1)*I(2,2) + I(0,0)*I(2,2) - I(0,1)*I(0,1) - I(0,2)*I(0,2) - I(1,2)*I(1,2);
        float I3 = I.determinant();
        
        std::cout << "Инварианты тензора:\n";
        std::cout << "I1 = " << I1 << "\n";
        std::cout << "I2 = " << I2 << "\n";
        std::cout << "I3 = " << I3 << std::endl;
        
        // Запуск визуализации — единая команда для всех
        int bodyType = choice;
        
        // Параметры тела (разные для разных типов)
        float p1 = 0, p2 = 0, p3 = 0;
        switch (bodyType) {
            case 1: p1 = a; break;
            case 2: p1 = r; break;
            case 3: p1 = a; p2 = b; p3 = c; break;
            case 4: p1 = r; p2 = h; break;
        }
        
        std::string cmd = "start /b build\\visualize.exe " +
                          std::to_string(bodyType) + " " +
                          std::to_string(rx) + " " +
                          std::to_string(ry) + " " +
                          std::to_string(rz) + " " +
                          std::to_string(axis(0)) + " " +
                          std::to_string(axis(1)) + " " +
                          std::to_string(axis(2)) + " " +
                          std::to_string(p1) + " " +
                          std::to_string(p2) + " " +
                          std::to_string(p3);
        
        system(cmd.c_str());
        
        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.ignore();
        std::cin.get();
    }
    
    return 0;
}