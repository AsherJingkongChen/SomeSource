#ifndef WRAP_STD
#define WRAP_STD 1
#endif//WRAP_STD
#if     WRAP_STD
    #include <vector>   // std::vector
    #include <map>      // std::map

/* wrapper for std::vector */
    template<class TYPE>
    using vec_t = std::vector<TYPE>;

/* wrapper for std::map */
    template<class KEY, class VALUE>
    using map_t = std::map<KEY, VALUE>;

#endif
