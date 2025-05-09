#include "OLAPCube.h"

void OLAPCube::addDimension(const Dimension& dim) {
    dimensions.push_back(dim);
    measureCounts[dim.name] = 0;
}

void OLAPCube::updateStatistics(const Document& doc) {
    // Обновляем статистику для каждого атрибута
    if (!doc.author.empty()) {
        measureCounts["author"]++;
        attributeCounts["author"][doc.author]++;
    }
    if (!doc.date.empty()) {
        measureCounts["date"]++;
        attributeCounts["date"][doc.date]++;
    }
    if (!doc.topic.empty()) {
        measureCounts["topic"]++;
        attributeCounts["topic"][doc.topic]++;
    }
}

double OLAPCube::calculateOLAPScore(const std::string& attribute, const std::string& value) const {
    auto it = measureCounts.find(attribute);
    if (it == measureCounts.end() || it->second == 0) {
        return 0.0;
    }

    auto attrIt = attributeCounts.find(attribute);
    if (attrIt == attributeCounts.end()) {
        return 0.0;
    }

    auto valueIt = attrIt->second.find(value);
    if (valueIt == attrIt->second.end()) {
        return 0.0;
    }

    return static_cast<double>(valueIt->second) / it->second;
}

std::vector<std::string> OLAPCube::getPossibleValues(const std::string& attribute) const {
    std::vector<std::string> values;
    auto it = attributeCounts.find(attribute);
    if (it != attributeCounts.end()) {
        for (const auto& pair : it->second) {
            values.push_back(pair.first);
        }
    }
    return values;
} 