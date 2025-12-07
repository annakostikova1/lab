#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


// % cd ~/Desktop/cpp_labs/lab1_file
// clang++ main.cpp -o program -std=c++11
// ./program



// Та же функция обработки, что и в варианте 2
void processCString(char* str) {
    int length = strlen(str);
    int cnt = 0;
    int last = -1;
    
    // Считаем группы "еееее"
    for (int i = 0; i <= length - 5; i++) {
        bool isGroup = true;
        for (int j = 0; j < 5; j++) {
            if (str[i + j] != 'e' && str[i + j] != 'e') {
                isGroup = false;
                break;
            }
        }
        
        if (isGroup) {
            cnt++;
            last= i + 4;
        }
    }
    
    // Если групп больше одной - обрабатываем
    if (cnt > 1) {
        int process = 0;
        int i = 0;
        
        while (i <= strlen(str) - 5) {
            bool isGroup = true;
            for (int j = 0; j < 5; j++) {
                if (str[i + j] != 'e' && str[i + j] != 'e') {
                    isGroup = false;
                    break;
                }
            }
            
            if (isGroup) {
                // Заменяем "еееее" на "E"
                str[i] = 'E';
                
                // Сдвигаем остаток строки на 4 символа влево
                for (int j = i + 1; str[j + 4] != '\0'; j++) {
                    str[j] = str[j + 4];
                }
                
                // Обновляем длину
                length -= 4;
                str[length] = '\0';
                
                process++;
                
                // Если это последняя группа - добавляем "?"
                if (process == cnt) {
                    // Сдвигаем строку для вставки "?"
                    for (int j = length; j > i + 1; j--) {
                        str[j] = str[j - 1];
                    }
                    str[i + 1] = '?';
                    str[length + 1] = '\0';
                    break;
                }
                
                i--; // Проверяем текущую позицию снова
            }
            i++;
        }
    }
}


int main() {
    char str[1000];
    
    cout << "=== Вариант 3: Работа с файлами ===" << endl;
    
    // Создаём файл с тестовой строкой
    ofstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Ошибка создания файла!" << endl;
        return 1;
    }
    
    // Тестовая строка (можно изменить)
    inputFile << "тестовая строка: eeeee ee e eee eeeee eeeee." << endl;
    inputFile.close();
    
    cout << "Файл input.txt создан с тестовой строкой." << endl;
    
    // Читаем из файла
    ifstream readFile("input.txt");
    if (!readFile) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }
    
    readFile.getline(str, 1000);
    readFile.close();
    
    cout << "Прочитано из файла: " << str << endl;
    
    // Обрабатываем
    processCString(str);
    
    // Записываем результат
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cout << "Ошибка создания выходного файла!" << endl;
        return 1;
    }
    
    outputFile << str << endl;
    outputFile.close();
    
    cout << "Результат записан в output.txt" << endl;
    cout << "Результат: " << str << endl;
    
    return 0;
}