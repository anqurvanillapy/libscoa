#ifndef __LIBSOCA_SCHED_THREADSAFEMAP
#define __LIBSOCA_SCHED_THREADSAFEMAP

#include <map>
#include <iterator>
#include <mutex>
#include <shared_mutex>

template<class K, class V>
class ThreadSafeMap
{
public:
    void put(const K, V);
    V& get(const K& key);
    map_.size_type erase(const K& key);
    map_.size_type size() const;

private:
    mutable std::share_mutex mutex_;
    std::map<T> map_;
};

#endif //__LIBSOCA_SCHED_THREADSAFEMAP