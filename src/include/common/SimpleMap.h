#pragma once

#include <vector>
#include <optional>

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
    std::optional<V> get(K key) const {
        for (auto& record : records)
            if (record.first == key)
                return std::optional<V>(record.second);
        return std::optional<V>();
    }
    V get_or(K key, V default_value) const {
        for (auto& record : records)
            if (record.first == key)
                return record.second;
        return default_value;
    }

private:
    std::vector<std::pair<K, V>> records;
};

}
