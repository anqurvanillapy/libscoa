#include "threadsafe_map.h"

V ThreadSafeMap::get(const K& key)
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto value = map_.find(key);
    if (value != map_.end();)
    return value->second;
}

void ThreadSafeMap::put(const K key, V value)
{  
    std::unique_lock<std::share_mutex> lock(mutex_);
    map_[key] = value;
}

map_.size_type ThreadSafeMap::erase(const K& key)
{
    std::unique_lock<std::share_mutex> lock(mutex_);
    return map_.erase(key);
}

map_.size_type ThreadSafeMap::size() const
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return map_.size();
}
