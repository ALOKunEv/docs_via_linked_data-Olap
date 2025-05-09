#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

// Структура для хранения документа
struct Document {
    int id;
    std::string author;
    std::string date;
    std::string topic;
    std::string content;
};

// Класс для представления семантической сети
class SemanticNetwork {
private:
    std::map<int, std::shared_ptr<Document>> documents;
    std::map<int, std::vector<int>> connections; // Граф связей между документами

public:
    // Добавление документа в сеть
    void addDocument(const Document& doc);
    
    // Добавление связи между документами
    void addConnection(int docId1, int docId2);
    
    // Получение соседей документа
    std::vector<int> getNeighbors(int docId) const;
    
    // Получение документа по ID
    std::shared_ptr<Document> getDocument(int docId) const;
    
    // Подсчет частоты реквизита среди соседей
    double calculateGraphScore(int docId, const std::string& attribute, const std::string& value) const;
}; 