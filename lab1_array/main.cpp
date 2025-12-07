#include <iostream>
using namespace std;


// компиляция и запуск
// cd ~/Desktop/cpp_labs/lab1_array
// clang++ main.cpp -o program -std=c++11
// ./program



// Функция для обработки строки-массива
void processCharArray(char str[], int length) {
    int cnt = 0; // сколько групп нашли
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
            last = i + 4;
        }
    }
    
    // Если групп больше одной - обрабатываем
    if (cnt > 1) {
        int process = 0; // сколько уже заменили
        
        for (int i = 0; i <= length - 5; i++) {
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
                for (int j = i + 1; j < length - 4; j++) {
                    str[j] = str[j + 4];
                }
                length -= 4;
                
                process++;
                
                // Если это последняя группа - добавляем "?"
                if (process == cnt) {
                    // Сдвигаем строку для вставки "?"
                    for (int j = length; j > i + 1; j--) {
                        str[j] = str[j - 1];
                    }
                    str[i + 1] = '?';
                    length++;
                    break;
                }
                
                i--; // Проверяем текущую позицию снова
            }
        }
    }
    
    str[length] = '\0'; // Завершаем строку
}

int main() {
    char str[1000];
    int length = 0;
    
    cout << "=== Вариант 1: Массив символов ===" << endl;
    cout << "Введите строку: ";
    
    // Читаем строку посимвольно
    char ch;
    while (cin.get(ch) && ch != '\n' && length < 1000 - 1) {
        str[length++] = ch;
    }
    str[length] = '\0';
    
    cout << "Исходная строка: " << str << endl;
    
    processCharArray(str, length);
    
    cout << "Результат: " << str << endl;
    
    return 0;
}