#include <iostream>
#include "SemanticNetwork.h"
#include "OLAPCube.h"
#include <windows.h>
using namespace std;

int main() {
    // Устанавливаем кодировку консоли
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout << "Программа запущена..." << endl;
    
    // Создаем семантическую сеть
    SemanticNetwork network;
    cout << "Семантическая сеть создана" << endl;
    
    // Создаем OLAP-куб
    OLAPCube cube;
    cout << "OLAP-куб создан" << endl;
    
    // Добавляем измерения в OLAP-куб
    Dimension authorDim{"author", {}};
    Dimension topicDim{"topic", {}};
    Dimension dateDim{"date", {}};
    
    cube.addDimension(authorDim);
    cube.addDimension(topicDim);
    cube.addDimension(dateDim);
    cout << "Измерения добавлены в куб" << endl;
    
    // Создаем и добавляем документы
    Document doc1{1, "Иванов", "2023-01-01", "", "Содержание документа 1"};
    Document doc2{2, "Петров", "2023-01-02", "Data Science", "Содержание документа 2"};
    Document doc3{3, "Иванов", "2023-01-03", "AI", "Содержание документа 3"};
    
    network.addDocument(doc1);
    network.addDocument(doc2);
    network.addDocument(doc3);
    
    // Добавляем связи между документами
    network.addConnection(1, 2);
    network.addConnection(1, 3);
    
    // Обновляем статистику в OLAP-кубе
    cube.updateStatistics(doc1);
    cube.updateStatistics(doc2);
    cube.updateStatistics(doc3);
    
    // Пример восстановления атрибута
    int targetDocId = 1;
    string attribute = "topic";
    
    // Получаем возможные значения атрибута
    auto possibleValues = cube.getPossibleValues(attribute);
    
    // Вычисляем итоговые оценки для каждого возможного значения
    map<string, double> finalScores;
    for (const auto& value : possibleValues) {
        double graphScore = network.calculateGraphScore(targetDocId, attribute, value);
        double olapScore = cube.calculateOLAPScore(attribute, value);
        
        // Используем веса w1 = 0.6 и w2 = 0.4
        finalScores[value] = 0.6 * graphScore + 0.4 * olapScore;
    }
    
    // Находим значение с максимальной оценкой
    string bestValue;
    double maxScore = -1.0;
    for (const auto& pair : finalScores) {
        cout << "Значение: " << pair.first << ", Оценка: " << pair.second << endl;
        if (pair.second > maxScore) {
            maxScore = pair.second;
            bestValue = pair.first;
        }
    }
    
    cout << "\nРезультаты:" << endl;
    cout << "Восстановленное значение атрибута '" << attribute << "': " << bestValue << endl;
    cout << "Оценка достоверности: " << maxScore << endl;
    
    return 0;
} 