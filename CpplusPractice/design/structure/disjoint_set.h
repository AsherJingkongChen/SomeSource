#include <cstdint>
#include <vector>
#include <algorithm>

class DisjointSet
{
    using namesapce std;
public:
    DisjointSet(size_t _n) :
        parent(_n)
    {
        reset();
    }

    void reset()
    {
        for (auto It = parent.begin(); It != parent.end(); It++)
            *It = distance(parent.begin(), It);
    }

// [3]-2 [2]-1 --> f(3) [3] = f(2) [2] = f(1) = 1
    int findParent(int _n)
    {
        if (_n == parent[_n])
            return _n;
        return (parent[_n] = findParent(parent[_n]));
    }

    bool unionTwo(int _1, int _2)
    {
        int parent1 = findParent(_1);
        int parent2 = findParent(_2);
        if (parent1 == parent2)
            return false;
        parent[parent1] = parent2;
        return true;
    }

protected:
    vector<int> parent; // [0 .. n-1]
};
