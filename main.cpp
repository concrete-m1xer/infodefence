#include "framework.h"
#include "windows.h"

int main(int argc, char *argv[])
{

    while(true)
    {
        setlocale(LC_CTYPE, "Russian");

        std::cout << "��������, ��� �� ������ �������: " << std::endl << "1 - �����������/������������ ���� ����"
                  << std::endl << "2 - ������������ �� ���� ����"
                  << std::endl << "0 - �����" << std::endl << "�����: ";
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
