#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

// Та же функция обработки
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
    const int BLOCK_SIZE = 5; // Блок по 5 символов
    char* str = NULL;
    int capacity = 0;
    int length = 0;
    char buffer[100];
    
    cout << "=== Программа с calloc() и realloc() ===" << endl;
    cout << "Введите строку: ";
    cin.getline(buffer, 100);
    
    int inputLen = strlen(buffer);
    
    // Выделяем память calloc() блоками по 5 символов
    int blocksNeeded = (inputLen / BLOCK_SIZE) + 1;
    capacity = blocksNeeded * BLOCK_SIZE;
    
    str = (char*)calloc(capacity + 1, sizeof(char)); // +1 для '\0'
    
    if (str == NULL) {
        cout << "Ошибка выделения памяти calloc()!" << endl;
        return 1;
    }
    
    cout << "Выделено памяти: " << capacity << " символов" << endl;
    
    // Копируем введённую строку
    strcpy(str, buffer);
    length = inputLen;
    
    // Если строка не поместилась - увеличиваем realloc()
    while (length >= capacity - 1) {
        capacity += BLOCK_SIZE;
        char* temp = (char*)realloc(str, (capacity + 1) * sizeof(char));
        
        if (temp == NULL) {
            cout << "Ошибка перераспределения памяти realloc()!" << endl;
            free(str);
            return 1;
        }
        
        str = temp;
        cout << "Перераспределено памяти: " << capacity << " символов" << endl;
    }
    
    cout << "\nИсходная строка: " << str << endl;
    cout << "Длина: " << length << " символов" << endl;
    cout << "Выделено: " << capacity << " символов" << endl;
    
    // Обработка строки
    processString(str);
    
    cout << "Результат: " << str << endl;
    
    // Освобождение памяти
    free(str);
    cout << "Память освобождена." << endl;
    
    return 0;
}