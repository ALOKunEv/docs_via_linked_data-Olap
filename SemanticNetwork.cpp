#include "SemanticNetwork.h"

void SemanticNetwork::addDocument(const Document& doc) {
    documents[doc.id] = std::make_shared<Document>(doc);
}

void SemanticNetwork::addConnection(int docId1, int docId2) {
    if (documents.find(docId1) != documents.end() && documents.find(docId2) != documents.end()) {
        connections[docId1].push_back(docId2);
        connections[docId2].push_back(docId1);
    }
}

std::vector<int> SemanticNetwork::getNeighbors(int docId) const {
    auto it = connections.find(docId);
    if (it != connections.end()) {
        return it->second;
    }
    return {};
}

std::shared_ptr<Document> SemanticNetwork::getDocument(int docId) const {
    auto it = documents.find(docId);
    if (it != documents.end()) {
        return it->second;
    }
    return nullptr;
}

double SemanticNetwork::calculateGraphScore(int docId, const std::string& attribute, const std::string& value) const {
    auto neighbors = getNeighbors(docId);
    if (neighbors.empty()) {
        return 0.0;
    }

    int count = 0;
    for (int neighborId : neighbors) {
        auto doc = getDocument(neighborId);
        if (doc) {
            if (attribute == "author" && doc->author == value) count++;
            else if (attribute == "date" && doc->date == value) count++;
            else if (attribute == "topic" && doc->topic == value) count++;
        }
    }

    return static_cast<double>(count) / neighbors.size();
} 