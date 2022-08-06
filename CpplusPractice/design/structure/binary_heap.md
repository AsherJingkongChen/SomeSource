```h
#include <stdlib.h> /* malloc */

/* custom typename */
typedef unsigned int U32;
typedef unsigned long long U64;

struct HeapBase
{
/*** ElementType *******/
#define __ElemType__ U32
/***********************/
#define __ExceptionValue__ \
	(((__ElemType__)-1 < 0) << (sizeof(__ElemType__) * 8 - 1))
	
#define __HeapType_MIN__ 0x00
#define __HeapType_MAX__ 0x01
/*** Priority **********************/
#define __HeapType__ __HeapType_MIN__
/***********************************/
#if (__HeapType__ == __HeapType_MIN__)
	#define __HeapComp__ >
#elif (__HeapType == __HeapType_MAX__)
	#define __HeapComp__ <
#endif
	
	__ElemType__* buffer;
	size_t  size;
	size_t  cap;
};
typedef struct HeapBase Heap;

Heap* heapAlloc(size_t _cap)
{
	Heap* d = (Heap *)malloc(sizeof(Heap));
	d->cap = _cap;
	d->size = 0;
	d->buffer = (__ElemType__ *)malloc((_cap + 1) * sizeof(__ElemType__));
	d->buffer[0] = __ExceptionValue__;
	return d;
}

void heapDealloc(Heap** _refData)
{
	free((*_refData)->buffer);
	(*_refData)->buffer = NULL;
	free(*_refData);
	*_refData = NULL;
}

void heapPush(Heap* _data, __ElemType__ _newValue)
{
	if (_data->size == _data->cap)
		return;
	
	size_t I = ++_data->size;
	for (; _data->buffer[I >> 1] __HeapComp__ _newValue; I >>= 1)
		_data->buffer[I] = _data->buffer[I >> 1];
	_data->buffer[I] = _newValue;
}

__ElemType__ heapPop(Heap* _data)
{
	if (_data->size == 0) 
		return _data->buffer[0];
	
	__ElemType__ top = _data->buffer[1];
	__ElemType__ bottom = _data->buffer[_data->size--];
	size_t I = 1, L;
	for(; (I << 1) <= _data->size; I = L)
	{
		L = (I << 1) | 
		    ((I << 1 ^ _data->size) &&
		     (_data->buffer[I << 1] __HeapComp__ _data->buffer[I << 1 | 1]));
		
		if (bottom __HeapComp__ _data->buffer[L])
			_data->buffer[I] = _data->buffer[L];
		else break;
	}
	_data->buffer[I] = bottom;
	return top;
}
```
