#pragma once
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <map>
#include <list>

template <typename T>
class cache_t
{
public:
    size_t cache_sz;
    cache_t(size_t sz) : cache_sz (sz) {};
    bool lookup(const T *elem);
    void print_list(std::ofstream& out);
private:
    std::unordered_map<int, typename std::multimap<int, int>::iterator> hash_freq;
    std::unordered_map<int, T> cache_;
    std::multimap<int, int> freq_map; // freq, key
    bool full();
};

template <typename T>
bool cache_t<T>::full()
{
    if(cache_.size() == cache_sz)
        return true;
    else
        return false;
}

template <typename T>
bool cache_t<T>::lookup(const T *elem)
{
    auto hit = hash_freq.find(elem->id);
    if (hit == hash_freq.end())
    {
        if(full())
        {
            auto it = freq_map.begin();
            hash_freq.erase(it->second);
            cache_.erase(it->second);
            freq_map.erase(it);
        }
        std::multimap<int, int>::iterator in = freq_map.insert({1, elem->id});
        cache_.insert({elem->id, *elem});
        hash_freq[elem->id] = in;
        return false;
    }
    else
    {
        auto elem_it = hit->second;
        int key = elem_it->second;
        int freq = elem_it->first;
        freq_map.erase(hit->second);
        freq++;
        hit->second = freq_map.insert({freq, key});
        cache_[key].freq = freq;
    }
    return true;
}

template <typename T>
void cache_t<T>::print_list (std::ofstream& out)
{
    typename std::unordered_map<int, T>::iterator elem_it = cache_.begin();
    for(int i = 0; i < cache_.size(); ++i)
    {
        out << "( " << elem_it->second.id << " , " << elem_it->second.freq << " ) ";
        elem_it++;
    }
    out << "\n";
}
