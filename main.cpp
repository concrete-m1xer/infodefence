#include "framework.h"
#include "windows.h"

int main(int argc, char *argv[])
{

    while(true)
    {
        setlocale(LC_CTYPE, "Russian");

        std::cout << "Выберите, что вы хотите сделать: " << std::endl << "1 - зашифровать/расшифровать зная ключ"
                  << std::endl << "2 - расшифровать не зная ключ"
                  << std::endl << "0 - Выйти" << std::endl << "Выбор: ";
        int n(0);
        std::cin >> n;
        switch (n) {
        case 0: return 0;
        case 1: {
            encryption();
            break;
        }
        case 2: {
            decription();
            break;
        }
        default: break;
        }
    }
}
