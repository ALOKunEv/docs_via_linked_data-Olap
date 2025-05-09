#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "SemanticNetwork.h"

// Структура для измерения OLAP-куба
struct Dimension {
    std::string name;
    std::vector<std::string> values;
};

// Класс для представления OLAP-куба
class OLAPCube {
private:
    std::vector<Dimension> dimensions;
    std::map<std::string, int> measureCounts; // Количество документов для каждого измерения
    std::map<std::string, std::map<std::string, int>> attributeCounts; // Количество документов для каждого значения атрибута

public:
    // Добавление измерения
    void addDimension(const Dimension& dim);
    
    // Обновление статистики на основе документа
    void updateStatistics(const Document& doc);
    
    // Расчет OLAP-оценки для атрибута
    double calculateOLAPScore(const std::string& attribute, const std::string& value) const;
    
    // Получение всех возможных значений для атрибута
    std::vector<std::string> getPossibleValues(const std::string& attribute) const;
}; 