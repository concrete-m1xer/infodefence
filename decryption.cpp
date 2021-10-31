#include "framework.h"
#include "decryption.h"



inline std::string getFileName(std::string alert = "Пожалуйста, введите имя файла")
{
    SetConsoleCP(1251);
    std::cout << alert << ": ";
    std::string filename;
    std::cin >> filename;
    return filename;

}




inline std::vector<unsigned char> getFile(std::string filealert)
{

    std::ifstream fin(getFileName(filealert), std::ios::binary);
    if (fin.is_open())
    {
        std::vector<unsigned char> text((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
        fin.close();
        return text;
    }
    else
    {
        std::cout << "Что-то пошло не так, файл не считан, прекращаю действия.";
        return { };
    }
}

void decription()
{

    std::vector<unsigned char> encText = getFile("Пожалуйста, введите имя файла с зашифрованным текстом");

    if (encText.empty()) return;



    // for probably suiting lenght of key get index of conformity
    std::vector<double> index(20);
    for (int i(1); i <= 20; ++i)
    {
        std::vector<int> letterCount(256);

        unsigned int iter(0);
        std::for_each(letterCount.begin(), letterCount.end(), [&](int& letter)
            {


                for (unsigned int k = 0; k < encText.size(); k += i)
                {
                    unsigned char uch(iter);
                    if (encText[k] == uch) ++letter;
                }


                if (letter != 0)
                    index[i - 1] += letter * (letter - 1.) / (encText.size() * 1. / i * (encText.size() * 1. / i - 1));


                ++iter;

            });
        //std::cout << "" << index[i - 1] << "       " << i << std::endl;
    }


    {
        std::vector<std::pair<double, int>> reorder(20);
        int i(0);
        std::for_each(reorder.begin(), reorder.end(), [&i, &index](std::pair<double, int>& reordp)
        {
                reordp.first = index[i];
                reordp.second = ++i;
        });

        std::sort(reorder.begin(), reorder.end(), [](std::pair<double, int> rpf, std::pair<double, int> rps) {return rpf.first > rps.first; });

        std::for_each(reorder.begin(), reorder.end(), [](std::pair<double, int> p) {
                std::cout << " Длина ключа: " << p.second << " индекс соответствия: " << p.first << std::endl;
            });
    }



    // key length
    std::cout << "Введите длину ключа: ";
    unsigned int keyLength;
    std::cin >> keyLength;

    // most frequent char
    std::vector<unsigned char> sampleText = getFile("Пожалуйста, введите название файла с текстом на исходном языке");
    std::vector<unsigned int> sampleLetterScore(256);


    std::for_each(sampleText.begin(), sampleText.end(), [&sampleLetterScore](unsigned char& smch) { ++sampleLetterScore[smch]; });

    unsigned int maxFreq(0);
    unsigned char mostFrequentChar(0);

    for (int i(0); i < 256; ++i)
    {
        if (maxFreq < sampleLetterScore[i])
        {
            maxFreq = sampleLetterScore[i];
            unsigned char uch(i);
            mostFrequentChar = uch;
        }
    }
    //std::cout << "Самый часто встреченный символ в тексте: " << mostFrequentChar << std::endl;


    {
        std::vector<std::pair<unsigned int, unsigned char>> reorder(256);
        unsigned int i(0);
        std::for_each(reorder.begin(), reorder.end(), [&i, &sampleLetterScore](std::pair<unsigned int, unsigned char>& reordp)
            {
                reordp.first = sampleLetterScore[i];
                unsigned char uch(i++);
                reordp.second = uch;
            });

        std::sort(reorder.begin(), reorder.end(), [](std::pair<unsigned int, unsigned char> rpf, std::pair<unsigned int, unsigned char> rps) {return rpf.first > rps.first; });

        std::for_each(reorder.begin(), reorder.end(), [](std::pair<unsigned int, unsigned char> p) {
            if(p.first > 0)
                std::cout << " Символ: " << p.second << " встретился: " << p.first << " раз" << std::endl;
            });
    }

    std::vector<unsigned char> posKey(keyLength);

    for (unsigned int i(0); i < keyLength; ++i)
    {
        std::vector<unsigned int> encrLetterScore(256);


        for (unsigned int j(i); j < encText.size(); j += keyLength)
            ++encrLetterScore[encText[j]];

        unsigned char mostFrequentEncrChar(0);
        unsigned int maxFreqEncr(0);
        for (int j(0); j < 256; ++j)
        {
            if (maxFreqEncr < encrLetterScore[j])
            {
                maxFreqEncr = encrLetterScore[j];
                unsigned char uch(j);
                mostFrequentEncrChar = uch;
            }

        }
        
        unsigned char uch(mostFrequentEncrChar - mostFrequentChar);
        posKey[i] = uch;
    }
    std::cout << "Ключ: ";
    std::for_each(posKey.begin(), posKey.end(), [](const unsigned char& ch) {std::cout << ch; });
    std::cout << std::endl;

    std::ofstream fout( getFileName("Пожалуйста, введите имя файла для расшифровки"), std::ios::binary);
    if (!fout.is_open())
    {
        std::cout << "Невозможнро записать файл расшифровки. Прекращаю действия." << std::endl;
        return;
    }

    unsigned int i(0);
    std::for_each(encText.begin(), encText.end(), [&posKey, &fout, &i](unsigned char& uch) {
        unsigned char unch( (uch - posKey[(i++) % posKey.size()]) );    
        fout << unch;
        });

    return;
}
