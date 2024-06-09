#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;


//Даны два текстовых файла. Добавить в конец каждой строки первого файла
//соответствующую строку второго файла. Если второй файл короче первого, то
//оставшиеся строки первого файла не изменять.
void task1(){
    ifstream file1("/Users/dmitrijzarikov/Projects/lab6/file1.txt");
    ifstream file2("/Users/dmitrijzarikov/Projects/lab6/file2.txt");

    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Не удалось открыть один из файлов!" << std::endl;
        return;
    }

    vector<std::string> lines1;
    vector<std::string> lines2;
    string line;

    while (getline(file1, line)) {
        lines1.push_back(line);
    }

    while (getline(file2, line)) {
        lines2.push_back(line);
    }

    file1.close();
    file2.close();

    // Проверка, что строки из второго файла добавлены в конец соответствующих строк первого файла
    size_t minSize = min(lines1.size(), lines2.size());
    for (size_t i = 0; i < minSize; ++i) {
        lines1[i] += lines2[i];
        cout << lines1[i] << endl;
    }

    // Запись результата в первый файл
    ofstream outFile("/Users/dmitrijzarikov/Projects/lab6/file1.txt");
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << std::endl;
        return;
    }

    for (const auto& str : lines1) {
        outFile << str << '\n';
        std::cout << "Записываем строку: " << str << std::endl;
    }

    outFile.close();
    std::cout << "Файлы успешно объединены!" << std::endl;
}


//На АТС информация о разговорах содержит номер телефона абонента, время
//разговора и тариф. Вывести для заданного абонента сумму, которую ему следует
//оплатить за разговоры.

struct ATS
{
    string phoneNumber;
    int duration;
    double cost;
};

// Функция для чтения данных из файла
std::vector<ATS> readCallsFromFile(const std::string& filename) {
    std::vector<ATS> listOfAts;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return listOfAts;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        ATS ats;
        if (iss >> ats.phoneNumber >> ats.duration >> ats.cost) {
            listOfAts.push_back(ats);
        }
    }

    file.close();
    return listOfAts;
}

// Функция для вычисления суммы, которую абонент должен оплатить
double calculateTotalCost(const std::vector<ATS>& listOfAts, const std::string& targetPhoneNumber) {
    double totalCost = 0.0;

    for (const auto& ats : listOfAts) {
        if (ats.phoneNumber == targetPhoneNumber) {
            totalCost += ats.duration * ats.cost;
        }
    }

    return totalCost;
}


void task2(){
    std::string filename = "/Users/dmitrijzarikov/Projects/lab6/ats.txt";
    std::vector<ATS> listOfAts = readCallsFromFile(filename);

    if (listOfAts.empty()) {
        return;
    }

    std::string targetPhoneNumber;
    std::cout << "Введите номер телефона абонента: ";
    std::cin >> targetPhoneNumber;

    double totalCost = calculateTotalCost(listOfAts, targetPhoneNumber);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Общая сумма, которую должен оплатить абонент " << targetPhoneNumber << ": " << totalCost << " руб.\n";

}

int main() {
    task1();
//    task2();
    return 0;
}
