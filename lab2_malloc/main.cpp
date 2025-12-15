#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


// (Ctrl+D в конце)


// Функция обработки строки (твоё задание)
void processString(char* str) {
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
    char* str = NULL;
    char* newStr = NULL;
    int capacity = 0;
    char ch;
    
    cout << "-> Реализация malloc() и free() " << endl;
    cout << "Введите строку:" << endl;
    
    // Ввод по одному символу с динамическим перераспределением
    while (cin.get(ch) && ch != '\n') {
        // Увеличиваем размер на 1 символ
        newStr = (char*)malloc((capacity + 2) * sizeof(char)); // +2: символ + '\0'
        
        if (newStr == NULL) {
            cout << "Ошибка выделения памяти!" << endl;
            free(str);
            return 1;
        }
        
        // Копируем старые символы
        if (str != NULL) {
            strcpy(newStr, str);
            free(str); // Освобождаем старую память
        } else {
            newStr[0] = '\0';
        }
        
        // Добавляем новый символ
        newStr[capacity] = ch;
        newStr[capacity + 1] = '\0';
        
        str = newStr;
        capacity++;
        
        cout << "Текущая строка: " << str << " (память: " << capacity + 1 << " байт)" << endl;
    }
    
    if (str == NULL) {
        cout << "Строка пустая!" << endl;
        return 0;
    }
    
    cout << "\nИсходная строка: " << str << endl;
    cout << "Длина: " << strlen(str) << " символов" << endl;
    
    // Обработка строки
    processString(str);
    
    cout << "Результат: " << str << endl;
    
    // Освобождение памяти
    free(str);
    cout << "Память освобождена." << endl;
    
    return 0;
}