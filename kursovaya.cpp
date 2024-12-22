#include <iostream>
#include <Windows.h>
#include <time.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <math.h>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <cstring>
#pragma warning(disable : 4996)
using namespace std;
using namespace chrono;
int promptMenuItem()
{

    int variant;
    cout << "Выберите задание: " << endl;
    cout << "1) Создать целочисленный несортированный массив из 100 элементов\n"
        << "2) Отсортировать заданный в пункте 1 массив\n"
        << "3) Найти максимальный и минимальный элемент данного массива\n"
        << "4) Вывести среднее значение максимального и минимального\n"
        << "5) Вывести количество элементов в отсортированном массиве, которые меньше числа a\n"
        << "6) Вывести количество элементов в отсортированном массиве, которые больше числа b\n"
        << "7) Бинарный поиск\n"
        << "8) Смена элементов массива\n"
        << "9) ИДЗ Сортировка слиянием\n" << endl;
    cout << "Задание: ";
    cin >> variant;
    return variant;
}
void preprocessBadChar(const char* pattern, unordered_map<char, int>& badChar) {
    int patternLength = strlen(pattern);
    for (int i = 0; i < patternLength; i++) {
        badChar[pattern[i]] = i;
    }
}

void boyerMooreSearch(const char* text, const char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    unordered_map<char, int> badChar;

    preprocessBadChar(pattern, badChar);

    int shift = 0;
    while (shift <= textLength - patternLength) {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            cout << "Найдено в позиции: " << shift << endl;
            shift += (shift + patternLength < textLength) ? patternLength - badChar[text[shift + patternLength]] : 1;
        }
        else {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }
}

void removeExtraSpaces(char* inputText) {
    char temp[1000];
    int j = 0;

    bool inSpace = false;

    for (int i = 0; inputText[i] != '\0'; ++i) {
        if (inputText[i] != ' ') {
            temp[j++] = inputText[i];
            inSpace = false;
        }
        else if (!inSpace) {
            temp[j++] = ' ';
            inSpace = true;
        }
    }
    temp[j] = '\0';

    strcpy(inputText, temp);
}

void removeExtraPunctuation(char* inputText) {
    char temp[1000];
    int j = 0;

    for (int i = 0; inputText[i] != '\0'; ++i) {
        if (ispunct(inputText[i])) {
            if (i == 0 || !ispunct(inputText[i - 1])) {
                temp[j++] = inputText[i];
            }
        }
        else {
            temp[j++] = inputText[i];
        }
    }
    temp[j] = '\0';

    strcpy(inputText, temp);
}
void correctCase(char* inputText) {
    bool newSentence = true;

    for (int i = 0; inputText[i] != '\0'; ++i) {
        if (newSentence && isalpha(inputText[i])) {
            inputText[i] = toupper(inputText[i]);
            newSentence = false;
        }
        else {
            inputText[i] = tolower(inputText[i]);
        }

        if (inputText[i] == '.' || inputText[i] == '!' || inputText[i] == '?') {
            newSentence = true;
        }
    }
}
void editText(char* inputText) {
    removeExtraSpaces(inputText);
    removeExtraPunctuation(inputText);
    correctCase(inputText);
}
void linearSearch(const char* text, const char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    for (int i = 0; i <= textLength - patternLength; i++) {
        int j;
        for (j = 0; j < patternLength; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == patternLength) {
            cout << "Найдено в позиции: " << i << endl;
        }
    }
}

void quicksort(int* arr, int  end, int begin)
{
    int mid;
    int f = begin;
    int l = end;
    mid = arr[(f + l) / 2];
    while (f < l)
    {
        while (arr[f] < mid) f++;
        while (arr[l] > mid) l--;
        if (f <= l)
        {
            swap(arr[f], arr[l]);
            f++;
            l--;
        }
    }
    if (begin < l) quicksort(arr, l, begin);
    if (f < end) quicksort(arr, end, f);
}
int binarySearch(int arr[], int value, int start, int end) {
    if (end >= start) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == value) {
            return mid;
        }
        if (arr[mid] > value) {
            return binarySearch(arr, value, start, mid - 1);
        }
        return binarySearch(arr, value, mid + 1, end);
    }
    return -1;
}
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
int taskMenu()
{
    int variant;
    cout << "Выберите задание: " << endl;
    cout << "1) Вывести матрицу N*N\n"
        << "2) Перестановки матриц\n"
        << "3) Сортировка(shaker sort)\n"
        << "4) Уменьшение, увеличение, умножение или деление всех элементов матрицы на введенное пользователем число\n"
        << "5) IDZ" << endl;
    cout << "Задание: ";
    cin >> variant;
    return variant;
}

int const N = 6;

void spiraloutput(int (*arr)[N]) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;

    int top = 0, bottom = N - 1;
    int left = 0, right = N - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            destCoord.X = i * 4;
            destCoord.Y = top;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(*(arr + top) + i) << " ";
            Sleep(100);
        }
        top++;


        for (int i = top; i <= bottom; i++) {
            destCoord.X = right * 4;
            destCoord.Y = i;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(*(arr + i) + right) << " ";
            Sleep(100);
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                destCoord.X = i * 4;
                destCoord.Y = bottom;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + bottom) + i) << " ";
                Sleep(100);
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                destCoord.X = left * 4;
                destCoord.Y = i;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + i) + left) << " ";
                Sleep(100);
            }
            left++;
        }
    }

    destCoord.X = 0;
    destCoord.Y = N + 1;
    SetConsoleCursorPosition(hStdout, destCoord);
}
void zmeyaoutput(int (*arr)[N]) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;

    for (int stolb = 0; stolb < N; stolb++) {
        if (stolb % 2 == 0) {
            for (int row = 0; row < N; row++) {
                destCoord.X = (N * N) + (stolb * 4);
                destCoord.Y = row;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + row) + stolb) << " ";
                Sleep(100);
            }
        }
        else {
            for (int row = N - 1; row >= 0; row--) {
                destCoord.X = (N * N) + (stolb * 4);
                destCoord.Y = row;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + row) + stolb) << " ";
                Sleep(100);
            }
        }
    }
    destCoord.X = 0;
    destCoord.Y = N + 1;
    SetConsoleCursorPosition(hStdout, destCoord);
}


void shakersort(int* arr, int n) {
    bool swapped = true;
    int* start = arr;
    int* end = arr + n * n - 1;

    while (swapped) {
        swapped = false;

        for (int* i = start; i < end; ++i) {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        swapped = false;
        --end;

        for (int* i = end - 1; i >= start; --i) {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                swapped = true;
            }
        }

        ++start;
    }
}
int main(int argc, char* argv[])
{
    setlocale(0, "");

    int num;
    cout << "Выберите лабороторную работу: ";
    cin >> num;
    switch (num)
    {
    case 1: {
        //1 ЗАДАНИЕ
        cout << "Программа выводит сколько памяти (в байтах) на вашем компьютере отводится под различные типы данных" << endl;
        cout << "int = " << sizeof(int) << " байта" << endl;
        cout << "short int = " << sizeof(short int) << " байта" << endl;
        cout << "long int = " << sizeof(long int) << " байта" << endl;
        cout << "float = " << sizeof(float) << " байта" << endl;
        cout << "double = " << sizeof(double) << " байта" << endl;
        cout << "long double = " << sizeof(long double) << " байта" << endl;
        cout << "char = " << sizeof(char) << " байта" << endl;
        cout << "bool = " << sizeof(bool) << " байта" << endl;

        cout << endl << endl;

        //2 ЗАДАНИЕ
        {
            cout << "Программа выводит представление десятичного числа типа int в памяти компьютера " << endl;
            int integerNumber;

            cout << "Введите число типа intenger: ";
            cin >> integerNumber;
            cout << "Двоичное представление введенного числа: ";

            unsigned int mask = 1 << (sizeof(int) * 8 - 1);

            for (int i = 1; i < sizeof(int) * 8 + 1; i++, mask >>= 1) {
                if (integerNumber & mask) {
                    cout << "1";
                }
                else {
                    cout << "0";
                }
                if (i == 1 || i % 8 == 0) {
                    cout << " ";
                }
            }
            // ИДЗ 11
            int num;
            int numberBit;
            int integerB;
            cout << endl << "Введите бит для сдвига влево: ";
            cin >> num;
            cout << endl << "Введите насколько сдвинуть бит влево: ";
            cin >> numberBit;
            cout << "Введенное число после сдвига влево на " << numberBit << " бит(а)";


            mask = 1 << (sizeof(int) * 8 - 1);
            for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
                if (mask & integerNumber) {
                    cout << "1";
                }
                else {
                    cout << "0";
                }
                if (i == 1 || i % 8 == 0) {
                    cout << " ";
                }
                if (i == num) {
                    integerB = num << numberBit;
                    integerNumber += integerB;
                }
            }
            cout << endl << "Представление сдвинутого числа в дяситичной системе: " << integerNumber;
        }

        cout << endl << endl;

        //3 ЗАДАНИЕ
        {
            cout << "Программа выводит представление десятичного числа типа float в памяти компьютера " << endl;
            union {
                float floatNumber;
                int integerNumber;
            };
            cout << "Введите число типа float: ";
            cin >> floatNumber;
            cout << "Двоичное представление введенного числа: ";

            unsigned int mask = 1 << (sizeof(int) * 8 - 1);

            for (int i = 1; i < sizeof(int) * 8 + 1; i++, mask >>= 1) {
                if (integerNumber & mask) {
                    cout << "1";
                }
                else {
                    cout << "0";
                }
                if (i == 1 || i % 8 == 0) {
                    cout << " ";
                }
            }
            // ИДЗ 11
            int num;

            cout << endl << "Введите количество битов для сдвига влево: ";
            cin >> num;
            cout << "Введенное число после сдвига влево на " << num << " бит(а)";

            integerNumber = integerNumber << num;
            mask = 1 << (sizeof(int) * 8 - 1);
            for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
                if (mask & integerNumber) {
                    cout << "1";
                }
                else {
                    cout << "0";
                }
                if (i == 1 || i % 8 == 0) {
                    cout << " ";
                }
            }
            cout << endl << "Представление сдвинутого числа в дяситичной системе: " << floatNumber;
        }


        cout << endl << endl;

        // 4 ЗАДАНИЕ
        {
            cout << "Программа выводит представление десятичного числа типа double в памяти компьютера " << endl;
            union {

                double doubleNumber;
                unsigned int sDouble[2];

            };
            cout << "Введите число типа double: ";
            cin >> doubleNumber;
            cout << "Двоичное представление введенного числа: ";

            unsigned int mask = 1 << (sizeof(int) * 8 - 1);
            for (int n = 1; n >= 0; --n) {
                for (int i = 1; i < sizeof(int) * 8 + 1; i++, mask >>= 1) {
                    if (mask & sDouble[n]) {
                        cout << '1';
                    }
                    else {
                        cout << '0';
                    }
                    if (i == 1 && n == 1) {
                        cout << " ";
                    }
                    if (i == 11 && n == 1) {
                        cout << " ";
                    }
                }
                mask = 1 << (sizeof(int) * 8 - 1);
            }
            // ИДЗ 11
            int num;

            cout << endl << "Введите количество битов для сдвига влево: ";
            cin >> num;
            cout << "Введенное число после сдвига влево на " << num << " бит(а)";

            for (int n = 1; n >= 0; --n) {
                sDouble[n] = sDouble[n] << num;
                mask = 1 << (sizeof(int) * 8 - 1);
                for (int i = 1; i < sizeof(int) * 8 + 1; ++i, mask >>= 1) {
                    if (mask & sDouble[n])
                        cout << "1";
                    else
                        cout << "0";
                    if (i == 1 && n == 1) {
                        cout << " ";
                    }
                    if (i == 11 && n == 1) {
                        cout << " ";
                    }
                }
            }
            cout << endl << "Представление сдвинутого числа в дяситичной системе: " << doubleNumber;
        }
    }
          break;
    case 2: {
        while (true) {
            time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start1, end1;
            nanoseconds result1;
            setlocale(LC_ALL, "Russian");
            srand(time(0));
            int variant = promptMenuItem();
            const int N = 100;
            int randarr[N], randarr2[N];
            int maxrand = 99, minrand = -99;
            int begin = 0, end = N - 1;
            switch (variant) {
            case 1: {
                cout << "Случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                    cout << randarr[i] << " ";
                    randarr2[i] = randarr[i];
                }
                cout << endl;
                cout << endl;
            }
                  break;
            case 2: {
                cout << "Отсортированный случайный массив: ";
                auto start1 = steady_clock::now();
                quicksort(randarr, end, begin);
                auto end1 = steady_clock::now();
                auto result1 = duration_cast<nanoseconds>(end1 - start1);
                for (int i = 0; i < N; ++i) {
                    cout << randarr[i] << " ";
                }
                cout << endl;
                cout << "Время сортировки: " << result1.count() << " наносекунд" << endl;
                cout << endl;
            }
                  break;
            case 3: {
                int minarr, maxarr;
                cout << "Случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                    cout << randarr[i] << " ";
                }
                cout << endl;
                minarr = randarr[0];
                maxarr = randarr[0];
                auto start1 = steady_clock::now();
                for (int i = 0; i < N; i++) {
                    if (randarr[i] < minarr) {
                        minarr = randarr[i];
                    }
                    if (randarr[i] > maxarr) {
                        maxarr = randarr[i];
                    }
                }
                auto end1 = steady_clock::now();
                auto result1 = duration_cast<nanoseconds>(end1 - start1);
                quicksort(randarr, end, begin);
                cout << "Максимальный элемент несортированного массива: " << maxarr << endl << "Минимальный элемент несортированного массива: " << minarr << endl;
                cout << "Время поиска в несортированном массиве: " << result1.count() << " наносекунд" << endl;
                cout << endl;
                auto start = steady_clock::now();
                int minarrel = randarr[0];
                int maxarrel = randarr[N - 1];
                auto end = steady_clock::now();
                auto result = duration_cast<nanoseconds>(end - start);
                cout << "Максимальный элемент сортированного массива: " << maxarrel << endl << "Минимальный элемент сортированного массива: " << minarrel << endl;
                cout << "Время поиска в сортированном массиве: " << result.count() << " наносекунд" << endl;
                cout << endl;

            }
                  break;
            case 4: {
                int mid, midsort, maxarrel, minarrel;
                int minarr, maxarr;
                int knesort = 0, ksort = 0;
                int value;
                cout << "Случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                    cout << randarr[i] << " ";
                }
                cout << endl;
                minarr = randarr[0];
                maxarr = randarr[0];
                auto start1 = steady_clock::now();
                for (int i = 0; i < N; ++i) {
                    if (randarr[i] > maxarr) {
                        maxarr = randarr[i];
                    }
                    if (randarr[i] < minarr) {
                        minarr = randarr[i];
                    }
                }
                mid = round((maxarr - minarr) / 2);
                cout << endl;
                cout << "Среднее значение максимального и минимального в несортированном массиве: " << mid << endl;
                for (int i = 0; i < N; i++) {
                    if (randarr[i] == mid) {
                        cout << i << " - й элемент массива является его средним значением" << endl;
                        knesort += 1;
                    }
                }
                auto end1 = steady_clock::now();
                auto result1 = duration_cast<nanoseconds>(end1 - start1);
                cout << "Количество элементов массива равных его среднему значению: " << knesort << endl;
                cout << "Время поиска: " << result1.count() << " наносекунд" << endl;
                cout << endl;
                cout << endl;
                quicksort(randarr, end, begin);
                cout << "Отсортированный случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    cout << randarr[i] << " ";
                }
                cout << endl;
                maxarrel = randarr[N - 1];
                minarrel = randarr[0];
                midsort = round((maxarrel - minarrel) / 2);
                cout << endl;
                cout << "Среднее значение максимального и минимального в сортированном массиве: " << midsort << endl;
                auto start2 = steady_clock::now();
                value = binarySearch(randarr, midsort, begin, end);
                if (value == -100) {
                    cout << "В данном массиве нет элемента равного среднему" << endl;
                }
                else {
                    for (int i = 0; i < N; i++) {
                        if (randarr[i] == value) {
                            cout << i << " - й элемент массива является его средним значением" << endl;
                            ksort += 1;
                        }
                    }
                }
                auto end2 = steady_clock::now();
                auto result2 = duration_cast<nanoseconds>(end2 - start2);
                cout << "Количество элементов массива равных его среднему значению: " << ksort << endl;
                cout << "Время поиска: " << result2.count() << " наносекунд" << endl;
                cout << endl;
            }
                  break;
            case 5: {
                int a;
                int counter = 0;
                cout << "Случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                    cout << randarr[i] << " ";
                }
                quicksort(randarr, end, begin);
                cout << endl;
                cout << "Введите значение числа a: ";
                cin >> a;
                cout << endl;
                cout << "Отсортированный случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    cout << randarr[i] << " ";
                    if (a > randarr[i]) {
                        counter++;
                    }
                    else {
                        break;
                    }
                }
                cout << endl;
                cout << "Количество элементов меньших " << a << ": " << counter << endl;
                cout << endl;
            }
                  break;
            case 6: {
                int b;
                int counter = 0;
                cout << "Случайный массив: ";
                for (int i = 0; i < N; ++i) {


                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                    cout << randarr[i] << " ";
                }
                quicksort(randarr, end, begin);
                cout << endl;
                cout << "Введите значение числа b: ";
                cin >> b;
                cout << endl;
                cout << "Отсортированный случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    cout << randarr[i] << " ";
                    if (b < randarr[i]) {
                        counter++;
                    }
                    else {
                        break;
                    }
                }
                cout << endl;
                cout << "Количество элементов больших " << b << ": " << counter << endl;
                cout << endl;
            }
                  break;
            case 7: {
                int num, value;
                for (int i = 0; i < N; ++i) {
                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                }
                quicksort(randarr, end, begin);
                cout << "Отсортированный массив: ";
                for (int i = 0; i < N; ++i) {
                    cout << randarr[i] << " ";
                }
                cout << endl << "Введите число которое необходимо найти: ";
                cin >> num;
                cout << endl;
                auto start1 = steady_clock::now();
                value = binarySearch(randarr, num, begin, end);
                auto end1 = steady_clock::now();
                auto result1 = duration_cast<nanoseconds>(end1 - start1);
                auto start2 = steady_clock::now();
                for (int i = 0; i < N; ++i) {
                    if (randarr[i] == num) {
                        value = randarr[i];
                        break;
                    }
                    else {
                        value = -100;
                    }
                }
                if (value != -100) {
                    cout << "Введённое число есть в отсортированном массиве" << endl;
                }
                else {
                    cout << "Введённое число отсутствует" << endl;
                }
                auto end2 = steady_clock::now();
                auto result2 = duration_cast<nanoseconds>(end2 - start2);
                cout << endl;
                cout << "Время затраченное на Бинарный поиск: " << result1.count() << " наносекунд" << endl;
                cout << "Время затраченное на Поиск перебором: " << result2.count() << " наносекунд" << endl;
                cout << endl;


            }
                  break;
            case 8: {
                int a, b;
                bool check = true;
                cout << "Случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                    cout << randarr[i] << " ";
                }
                cout << endl;
                cout << endl << "Введите индекс первого элемента(от 0 до 99): ";
                cin >> a;
                while (check) {
                    if (a < 0 or a > 99) {
                        cout << "Несоответствие количеству элементов массива попробуйте ещё раз" << endl;
                        cout << "Введите индекс первого элемента(от 0 до 99): ";
                        cin >> a;
                        cout << endl;
                    }
                    else {
                        check = false;
                    }
                }
                check = true;
                cout << endl << "Введите индекс второго элемента(от 0 до 99): ";
                cin >> b;
                while (check) {
                    if (b < 0 or b > 99) {
                        cout << "Несоответствие количеству элементов массива попробуйте ещё раз" << endl;
                        cout << "Введите индекс второго элемента(от 0 до 99): ";
                        cin >> b;
                        cout << endl;
                    }
                    else {
                        check = false;
                    }
                }
                auto start1 = steady_clock::now();
                swap(randarr[a], randarr[b]);
                auto end1 = steady_clock::now();
                auto result1 = duration_cast<nanoseconds>(end1 - start1);
                cout << endl << "Изменённый массив: ";
                for (int i = 0; i < N; ++i) {
                    cout << randarr[i] << " ";
                }
                cout << endl;
                cout << "Время затраченное на смену мест: " << result1.count() << " наносекунд";
                cout << endl << endl;
            }
                  break;
            case 9: {
                cout << "Случайный массив: ";
                for (int i = 0; i < N; ++i) {
                    randarr[i] = rand() % (maxrand - minrand + 1) + minrand;
                    cout << randarr[i] << " ";
                    randarr2[i] = randarr[i];
                }
                auto start1 = steady_clock::now();
                mergeSort(randarr, 0, N - 1);
                auto end1 = steady_clock::now();
                auto result1 = duration_cast<nanoseconds>(end1 - start1);
                auto start2 = steady_clock::now();
                quicksort(randarr2, end, begin);
                auto end2 = steady_clock::now();
                auto result2 = duration_cast<nanoseconds>(end2 - start2);
                cout << endl << endl;
                cout << "Результат сортировки слиянием: ";
                for (int i = 0; i < N; ++i) {
                    cout << randarr[i] << " ";
                }
                cout << endl << endl;
                cout << "Время затраченное на сортировку слиянием: " << result1.count() << " наносекунд" << endl;
                cout << "Время сортировки этого же массива быстрой сортировкой: " << result2.count() << " наносекунд" << endl << endl;
            }
                  break;
            default:
                cout << "ОШИБКА: Некорректный ввод";
                exit(EXIT_FAILURE);
            }
        }
        cout << endl;
    }
          break;
    case 3: {
        srand(time(NULL));
        int maxvalue = N * N, minvalue = 1;
        int arr[N][N];
        int sortArr[N][N];
        int calcArr[N][N];
        int stairArr[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                arr[i][j] = rand() % (maxvalue - minvalue + 1) + minvalue;
                sortArr[i][j] = arr[i][j];
                calcArr[i][j] = arr[i][j];
                stairArr[i][j] = arr[i][j];
            }
        }
        while (true) {
            setlocale(LC_ALL, "Russian");
            int variant = taskMenu();
            switch (variant) {
            case 1: {
                system("cls");
                spiraloutput(arr);
                zmeyaoutput(arr);
            }
                  break;
            case 2: {
                int step = N / 2;
                int abcd;
                cout << "Выберите тип перестановки,введите число от 1 до 4: " << endl;
                cout << "1) a\n"
                    << "2) b\n"
                    << "3) c\n"
                    << "4) d\n" << endl;
                cin >> abcd;
                switch (abcd) {
                case 1: {
                    system("cls");
                    int change[N][N];
                    int* arr_ptr = *arr;
                    int* change_ptr = *change;
                    for (int i = 0; i < step; i++) {
                        for (int j = 0; j < step; j++) {
                            *(change_ptr + i * N + j) = *(arr_ptr + (i + step) * N + j);
                            *(change_ptr + i * N + (j + step)) = *(arr_ptr + i * N + j);
                            *(change_ptr + (i + step) * N + (j + step)) = *(arr_ptr + i * N + (j + step));
                            *(change_ptr + (i + step) * N + j) = *(arr_ptr + (i + step) * N + (j + step));
                        }
                    }
                    spiraloutput(change);
                    zmeyaoutput(arr);
                }
                      break;
                case 2: {
                    system("cls");
                    int change2[N][N];
                    int* arr_ptr = *arr;
                    int* change2_ptr = *change2;
                    for (int i = 0; i < step; i++) {
                        for (int j = 0; j < step; j++) {
                            *(change2_ptr + i * N + j) = *(arr_ptr + (i + step) * N + (j + step));
                            *(change2_ptr + i * N + (j + step)) = *(arr_ptr + (i + step) * N + j);
                            *(change2_ptr + (i + step) * N + (j + step)) = *(arr_ptr + i * N + j);
                            *(change2_ptr + (i + step) * N + j) = *(arr_ptr + i * N + (j + step));
                        }
                    }
                    spiraloutput(change2);
                    zmeyaoutput(arr);
                }
                      break;
                case 3: {
                    system("cls");
                    int change3[N][N];
                    int* arr_ptr = *arr;
                    int* change3_ptr = *change3;
                    for (int i = 0; i < step; i++) {
                        for (int j = 0; j < step; j++) {
                            *(change3_ptr + i * N + j) = *(arr_ptr + (i + step) * N + j);
                            *(change3_ptr + i * N + (j + step)) = *(arr_ptr + (i + step) * N + (j + step));
                            *(change3_ptr + (i + step) * N + j) = *(arr_ptr + i * N + j);
                            *(change3_ptr + (i + step) * N + (j + step)) = *(arr_ptr + i * N + (j + step));
                        }
                    }
                    spiraloutput(change3);
                    zmeyaoutput(arr);
                }
                      break;
                case 4: {
                    system("cls");
                    int change4[N][N];
                    int* arr_ptr = *arr;
                    int* change4_ptr = *change4;
                    for (int i = 0; i < step; i++) {
                        for (int j = 0; j < step; j++) {
                            *(change4_ptr + i * N + j) = *(arr_ptr + i * N + (j + step));
                            *(change4_ptr + (i + step) * N + j) = *(arr_ptr + (i + step) * N + (j + step));
                            *(change4_ptr + i * N + (j + step)) = *(arr_ptr + i * N + j);
                            *(change4_ptr + (i + step) * N + (j + step)) = *(arr_ptr + (i + step) * N + j);
                        }
                    }
                    spiraloutput(change4);
                    zmeyaoutput(arr);
                }
                      break;
                }
            }
                  break;
            case 3: {
                system("cls");
                shakersort(*sortArr, N);
                spiraloutput(sortArr);
                zmeyaoutput(sortArr);
            }
                  break;
            case 4: {
                int matfucn;
                cout << "Выберите тип действия: " << endl;
                cout << "1) Вычитание\n"
                    << "2) Прибавление\n"
                    << "3) Умножение\n"
                    << "4) Деление\n" << endl;
                cin >> matfucn;
                switch (matfucn) {
                case 1: {
                    int num;
                    cout << "Введите число: " << endl;
                    cin >> num;
                    system("cls");
                    int* start = *calcArr;
                    int* end = *(calcArr + N * N - 1);
                    for (int* ptr = start; ptr <= end; ++ptr) {
                        *ptr -= num;
                    }
                    spiraloutput(calcArr);
                    zmeyaoutput(arr);
                }
                      break;
                case 2: {
                    int num;
                    cout << "Введите число: " << endl;
                    cin >> num;
                    system("cls");
                    int* start = *calcArr;
                    int* end = *(calcArr + N * N - 1);
                    for (int* ptr = start; ptr <= end; ++ptr) {
                        *ptr += num;
                    }
                    spiraloutput(calcArr);
                    zmeyaoutput(arr);
                }
                      break;
                case 3: {
                    int num;
                    cout << "Введите число: " << endl;
                    cin >> num;
                    system("cls");
                    int* start = *calcArr;
                    int* end = *(calcArr + N * N - 1);
                    for (int* ptr = start; ptr <= end; ++ptr) {
                        *ptr *= num;
                    }
                    spiraloutput(calcArr);
                    zmeyaoutput(arr);
                }
                      break;
                case 4: {
                    int num;
                    cout << "Введите число: " << endl;
                    cin >> num;
                    system("cls");
                    int* start = *calcArr;
                    int* end = *(calcArr + N * N - 1);
                    for (int* ptr = start; ptr <= end; ++ptr) {
                        *ptr /= num;
                    }
                    spiraloutput(calcArr);
                    zmeyaoutput(arr);
                }
                      break;
                }
            }
                  break;
            case 5: {
                system("cls");
                int idzArr[N][N];
                int idzArr2[N][N];
                int idzArr3[N][N];
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        idzArr[i][j] = rand() % (maxvalue - minvalue + 1) + minvalue;
                        idzArr2[i][j] = rand() % (maxvalue - minvalue + 1) + minvalue;
                    }
                }
                spiraloutput(idzArr);
                zmeyaoutput(idzArr2);
                for (int i = 0; i < N; ++i) {
                    int* elIDZArr = idzArr[i];
                    int* elIDZArr2 = idzArr2[i];
                    int* elIDZArr3 = idzArr3[i];
                    for (int j = 0; j < N; ++j) {
                        *(elIDZArr3 + j) = *(elIDZArr + j) + *(elIDZArr2 + j);
                    }
                }
                int t;
                cout << "Чтобы сложить матрицу (1/2) нажмите 1" << endl;
                cin >> t;
                if (t == 1) {
                    system("cls");
                    spiraloutput(idzArr3);
                }
                else {
                    cout << "ОШИБКА: Некорректный ввод" << endl;
                    cin >> t;
                }
            }
                  break;
            default: {
                cout << "ОШИБКА: Некорректный ввод";
                exit(EXIT_FAILURE);
            }

            }


        }
    }
          break;
    case 4: {
        char inputText[1000];
        const int MAX_LENGTH = 1000;
        char words[MAX_LENGTH][MAX_LENGTH];
        int wordCount = 0;
        while (true) {
            cout << "Введите с клавиатуры(1) или с файла(2), или 0 для выхода: ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 0) {
                break;
            }

            if (choice == 1) {
                cout << "Введите текст (может не заканчиваться точкой):\n";
                cin.getline(inputText, sizeof(inputText));
            }
            else if (choice == 2) {
                char fileName[100];
                cout << "Введите имя файла:\n";
                cin.getline(fileName, sizeof(fileName));

                ifstream inputFile(fileName);
                if (!inputFile.is_open()) {
                    cerr << "Ошибка открытия файла!" << endl;
                    continue;
                }

                inputFile.getline(inputText, sizeof(inputText));
                inputFile.close();
                cout << "Текст из файла: " << inputText << endl;
            }
            else {
                cerr << "Неверный выбор!" << endl;
                continue;
            }

            editText(inputText);
            cout << "Отредактированный текст: " << inputText << endl;
            char* token = strtok(inputText, " ");
            while (token != nullptr) {
                strcpy(words[wordCount++], token);
                token = strtok(nullptr, " ");
            }
            cout << "Слова в обратном порядке: ";
            for (int i = wordCount - 1; i >= 0; --i) {
                cout << words[i] << ' ';
            }
            cout << endl;
            cout << "Количество символов в каждом слове:" << endl;
            for (int i = 0; i < wordCount; ++i) {
                cout << words[i] << ": " << strlen(words[i]) << " символов" << endl;
            }
            char text[MAX_LENGTH];
            char pattern[MAX_LENGTH];

            cout << "Введите строку: ";
            cin.getline(text, MAX_LENGTH);
            cout << "Введите подстроку для поиска: ";
            cin.getline(pattern, MAX_LENGTH);
            cout << "Результаты линейного поиска:" << endl;
            linearSearch(text, pattern);
            cout << "Введите строку: ";
            cin.getline(text, MAX_LENGTH);
            cout << "Введите подстроку для поиска: ";
            cin.getline(pattern, MAX_LENGTH);
            cout << "Результаты алгоритма Бойера-Мура:" << endl;
            boyerMooreSearch(text, pattern);

        }
    }
          break;
    default:
        break;

    }
}
    