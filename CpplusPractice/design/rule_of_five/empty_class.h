/**
 * Ciis' Cplusplus class template
 * _1. private members
 * _2. public members + get + set
 * b1. destructor
 * b2. constructors (if arguments provided, tag as explicit)
 * b3. copy constructor
 * b4. move constructor
 * b5. copy assignment operator
 * b6. move assignment operator
 * _3. custom methods
 */

#ifndef CIIS_EMPTYCLASS_H
#define CIIS_EMPTYCLASS_H

class empty_class {
private:


public:
/* get & set */

// basic method section :

/* dtor */
    ~empty_class() = delete;

/* ctor0 */
    empty_class()  = delete;

/* ctorA */
    explicit
    empty_class(size_t _size) = delete;
  
/* cpctor */
    empty_class(const empty_class& _src) = delete;
  
/* mvctor */
    empty_class(empty_class&& _src) noexcept = delete;
  
/* copy = */
    void
    operator=(const empty_class& _rhs) = delete;
  
/* move = */
    void
    operator=(empty_class&& _rhs) noexcept = delete;
  
// custom method section :

};

#endif //CIIS_EMPTYCLASS_H
