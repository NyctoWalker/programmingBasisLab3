#include <iostream>
using namespace std;
#include <ctime>;

int** createArr(const int rows, const int cols) // Функция создания двумерного массива
{
    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols];
    }
    return arr;
}

void fillArr(int** const arr, const int rows, const int cols) //Функция заполнения массива
{
    cout << "Изначальный массив:\n";
    for (int i = 0; i < rows;i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = rand() % 100 - 50;
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void delMin(int**& arr, int &rows, int &cols, const int mini, const int minj) //Функция удаления строки и столбца минимального элемента
{
    cols--;
    rows--;
    int** newArr = createArr(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        if (i < mini)
        {
            for (int j = 0; j < cols; j++)
            {
                if (j < minj)
                {
                    newArr[i][j] = arr[i][j];
                }
                else
                {
                    newArr[i][j] = arr[i][j+1];
                }
            }
        }
        else
        {
            for (int j = 0; j < cols; j++)
            {
                if (j < minj)
                {
                    newArr[i][j] = arr[i+1][j];
                }
                else
                {
                    newArr[i][j] = arr[i+1][j + 1];
                }
            }
        }
        
    }
    delete[] arr;
    arr = newArr;
}

int main()
{
    /*Из заданной матрицы сформировать новую, удалив строку и столбец, к которым принадлежит минимальный элемент.*/
    setlocale(LC_ALL, "ru");
    srand(time(0));
    //Блок чтения и записи данных
    int rows, cols, lastMin=100, mini=0, minj=0;
    cout << "Введите количество строк:\n";
    cin >> rows;
    cout << "\nВведите количество колонок:\n";
    cin >> cols;
    cout << endl;

    int** arr=createArr(rows, cols);
    fillArr(arr, rows, cols);

    //==================================================================
    //Блок обработки результатов

    for (int i = 0; i < rows;i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] < lastMin)
            {
                lastMin = arr[i][j];
                mini = i;
                minj = j;
            }
        }
    }
    cout << "\nПоследнее найденное минимальное значение: " << lastMin << ", расположенное на [" << mini << ", " << minj << "]\n\n";
    delMin(arr, rows, cols, mini, minj); //Функция удаления лишних строки и столбца

    //==================================================================
    //Блок вывода

    cout << "Полученный массив с удалёнными строкой и столбцом:\n";
    for (int i = 0; i < rows;i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    //Удаление динамических переменных для избежания утечек памяти
    for (int i = 0; i < rows; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}