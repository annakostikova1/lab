#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

void processString(char* str) {
    int len = strlen(str);
    int countGroups = 0;
    
    for (int i = 0; i <= len - 5; i++) {
        bool isGroup = true;
        for (int j = 0; j < 5; j++) {
            if (str[i + j] != 'e') {
                isGroup = false;
                break;
            }
        }
        if (isGroup) countGroups++;
    }
    
    if (countGroups > 1) {
        int processedGroups = 0;
        int i = 0;
        int newLen = len;
        
        while (i <= newLen - 5) {
            bool isGroup = true;
            for (int j = 0; j < 5; j++) {
                if (str[i + j] != 'e') {
                    isGroup = false;
                    break;
                }
            }
            
            if (isGroup) {
                str[i] = 'E';
                for (int j = i + 1; j < newLen - 4; j++) {
                    str[j] = str[j + 4];
                }
                newLen -= 4;
                str[newLen] = '\0';
                
                processedGroups++;
                
                if (processedGroups == countGroups) {
                    for (int j = newLen; j > i + 1; j--) {
                        str[j] = str[j - 1];
                    }
                    str[i + 1] = '?';
                    newLen++;
                    str[newLen] = '\0';
                    break;
                }
                
                i--;
            }
            i++;
        }
    }
}

int main() {
    cout << "=== Программа с файлами ===" << endl;
    
    // Ввод строки (используем вариант с calloc/realloc)
    char input[1000];
    cout << "Введите строку для записи в файл: ";
    cin.getline(input, 1000);
    
    // Запись в файл
    ofstream outFile("input.txt");
    if (!outFile) {
        cout << "Ошибка создания файла!" << endl;
        return 1;
    }
    
    outFile << input;
    outFile.close();
    cout << "Строка записана в input.txt" << endl;
    
    // Чтение из файла с динамическим выделением памяти
    ifstream inFile("input.txt");
    if (!inFile) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }
    
    // Определяем размер файла
    inFile.seekg(0, ios::end);
    int fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);
    
    // Выделяем память
    char* fileContent = (char*)malloc((fileSize + 1) * sizeof(char));
    if (fileContent == NULL) {
        cout << "Ошибка выделения памяти!" << endl;
        return 1;
    }
    
    // Читаем файл
    inFile.read(fileContent, fileSize);
    fileContent[fileSize] = '\0';
    inFile.close();
    
    cout << "\nПрочитано из файла: " << fileContent << endl;
    cout << "Размер: " << fileSize << " байт" << endl;
    
    // Обработка
    processString(fileContent);
    
    // Запись результата
    ofstream resultFile("output.txt");
    if (!resultFile) {
        cout << "Ошибка создания файла результата!" << endl;
        free(fileContent);
        return 1;
    }
    
    resultFile << fileContent;
    resultFile.close();
    
    cout << "Результат: " << fileContent << endl;
    cout << "Результат записан в output.txt" << endl;
    
    // Освобождение памяти
    free(fileContent);
    cout << "Память освобождена." << endl;
    
    return 0;
}