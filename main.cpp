#include "payment.h"
#include "common.h"
#include <windows.h>

using namespace std::string_view_literals;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(1251);
#endif
    
    std::string answer;

    while (true) {
        try {
            Payment date;
            Print(date);

            std::cout << std::endl;
            std::cout << "Хотите продолжить работу? (y/n): ";
            std::cin >> answer;

            if (answer == "n" || answer == "N") {
                break;
            }
            else if (answer == "y" || answer == "Y") {
                continue;
            }
            else {
                throw std::invalid_argument("Некорректный ввод. Пожалуйста, введите 'y' или 'n'");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: "sv << e.what() << std::endl;
            std::cin.clear(); // Сброс флага ошибки ввода
            std::cin.ignore(); // Очистка буфера ввода
        }

        return 0;
    }
}
