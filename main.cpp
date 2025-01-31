#include "payment.h"
#include "common.h"

using namespace std::string_view_literals;

int main() {
#ifdef _WIN32
    system("chcp 1251");
    std::cout << std::endl;
#endif

    try {
        char ch;
        do {
            Payment date;
            Print(date);
            
            std::cout << std::endl;
            std::cout << "Хотите продолжить? Y/N: "sv;
            std::cin >> ch;
            std::cin.clear();
            std::cin.ignore();

        } while ((ch != 'Y' && ch != 'y'));
        
        if (ch == 'N' || ch == 'n') {
            exit(0);
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: "sv << e.what() << std::endl;
    }

    return 0;
}
