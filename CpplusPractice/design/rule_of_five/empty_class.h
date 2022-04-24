/**
 * Ciis' Cplusplus class rule of "2 + basic 6 + custom"
 * _1. private members
 * _2. public members + get + set
 * b1. destructor
 * b2. constructors 
 * b3. copy constructor
 * b4. move constructor
 * b5. copy assignment operator
 * b6. move assignment operator
 * _3. custom methods
 */

#ifndef CIIS_EMPTYCLASS_H
#define CIIS_EMPTYCLASS_H

/* inclusion */

class empty_class {
private:
/* members */
    void* ptr;

public:
/* get & set */
    void* 
    bond;
    
    void*
    get_ptr() const
    {
        return ptr;
    }

// basic method section :

/* dtor */
    ~empty_class() = delete;

/* ctor0 */
    empty_class()
        : ptr(nullptr)
        , bond(nullptr) {}

/* ctorA */
    empty_class(size_t _size)
        : ptr(new char[_size])
        , bond(nullptr) {}
  
/* cpctor */
    empty_class(const empty_class& _src)     {};
  
/* mvctor */
    empty_class(empty_class&& _src) noexcept {};
  
/* copy = */
    void
    operator=(const empty_class& _rhs)       {};
  
/* move = */
    void
    operator=(empty_class&& _rhs)   noexcept {};
  
// custom method section :
  
/* assert equivalence */
    bool
    operator==(const empty_class& _rhs) const
    {
        return false; 
    }
  
/* assert equivalence */
    bool
    operator!=(const empty_class& _rhs) const
    {
        return !(*this == _rhs); 
    }

};

#endif //CIIS_EMPTYCLASS_H
