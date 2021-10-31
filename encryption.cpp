#include "framework.h"
#include "encryption.h"



void getConsole(std::string& key, std::string& output, std::string& input, int& mode)
{
    SetConsoleCP(1251);
    std::cin.clear();
    std::cin.ignore(199, '\n');
    std::cout << std::string("Пожалуйста, введите название файла с исходным текстом: ");
    std::getline(std::cin, input, '\n');

    std::cout << "Пожалуйста, введите название файла, куда следует сохранить результат: ";
    std::getline(std::cin, output, '\n');

    std::cout << "Пожалуйста, введите ключ шифрования: ";
    std::getline(std::cin, key, '\n');
    
    std::cout << "Пожалуйства, выберите режим: Зашифровать - 1, Расшифровать - 0: ";
    std::cin >> mode;
    

    return;

}



void encryption()
{
    std::string keyStr(""), output(""), input("");
    int mode(0);

    getConsole(keyStr, output, input, mode);

    std::vector<unsigned char> key(keyStr.length());
    for(unsigned int i(0); i < key.size(); ++i)
    {
        unsigned char c(keyStr[i]);
        key[i] = c;
    }


    std::ofstream fout;
    fout.open(output, std::ofstream::binary);
    

    std::ifstream fin(input, std::ios::binary);


    if(fout.is_open())
    {

        if (mode == 1)
        {
            //encryption
            unsigned char c(0);
            unsigned int i(0);
            while(fin >> std::noskipws >> c)
            {
                unsigned char uch(c + (key[(i++) % key.size()]));
                fout << uch;
            }
        } 
        else 
        {
            //decryption
            unsigned char c(0);
            unsigned int i(0);
            while (fin >> std::noskipws >> c)
            {
                unsigned char uch(c - (key[(i++) % key.size()]));
                fout << uch;
            }
        }

        fout.close();

        fin.close();


    }

    return;


}


