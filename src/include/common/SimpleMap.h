#pragma once

#include <vector>

namespace game {

template<typename K, typename V>
class SimpleMap {
public:
    void set(K key, V value) {
        for (auto& record : records)
            if (record.first == key) {
                record.second = value;
                break;
            }
        records.push_back(std::make_pair(key, value));
    }

    V get_or(K key, V default_value) const {
        for (auto& record : records)
            if (record.first == key)
                return record.second;
        return default_value;
    }

    bool has(K key) {
        for (auto& record : records) {
            if (record.first == key)
                return true;
        }

        return false;
    }

private:
    std::vector<std::pair<K, V>> records;
};

}
