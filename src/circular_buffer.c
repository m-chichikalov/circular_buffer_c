/*
 * cicle_buffer.c
 * Author: m.chichikalov@outlook.com
TODO - add callback function which will execute when buffer is full.
TODO - add function which return a value of free space in the buffer.
 */
#include "circular_buffer.h"
//*****************************************************************************
// static functions
static void c_b_modify_buffer(circular_buffer_t *, TYPE_OF_ELEMENT_OF_BUFFER *);
static void c_b_set_p_actual(circular_buffer_t * pThis, TYPE_OF_ELEMENT_OF_BUFFER* new_pointer);
static void c_b_set_p_used(circular_buffer_t* pThis, TYPE_OF_ELEMENT_OF_BUFFER* new_pointer);
// -- other I used in unit-tests. Can't declare as static.
TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_p_actual(circular_buffer_t *pThis);
TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_p_used(circular_buffer_t *pThis);

//*****************************************************************************
int c_b_init(circular_buffer_t* pThis){
	pThis->p_actual = pThis->buffer;
	pThis->p_used   = pThis->buffer;
	return 1;
}

//*****************************************************************************
int c_b_put_string(circular_buffer_t* pThis, const TYPE_OF_ELEMENT_OF_BUFFER* str){
	int i = 0;
	do  {
			if ((pThis->p_actual + 1) == pThis->p_used)
				return -1;
//			c_b_modify_buffer(pThis, &str[i++]);
		} while (str[i - 1] != (TYPE_OF_ELEMENT_OF_BUFFER)0x0);
	return 0;
}

//*****************************************************************************
int c_b_put(circular_buffer_t* pThis, TYPE_OF_ELEMENT_OF_BUFFER *pData){
	if ((pThis->p_actual + 1) == pThis->p_used)
		return -1;
	c_b_modify_buffer(pThis, pData);
	return 0;
}

//*****************************************************************************
static void c_b_modify_buffer(circular_buffer_t* pThis, TYPE_OF_ELEMENT_OF_BUFFER *pData){
	*pThis->p_actual = *pData;
	c_b_set_p_actual(pThis, (pThis->p_actual + 1));
}

//*****************************************************************************
inline TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_p_actual(circular_buffer_t* pThis){
	return pThis->p_actual;
}

//*****************************************************************************
inline TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_p_used(circular_buffer_t* pThis){
	return pThis->p_used;
}

//*****************************************************************************
void c_b_set_p_actual(circular_buffer_t* pThis, TYPE_OF_ELEMENT_OF_BUFFER* index){
	pThis->p_actual = index;
	if (pThis->p_actual > (pThis->buffer + (LEN_BUFFER - 1)))
		pThis->p_actual = pThis->buffer;
}

//*****************************************************************************
void c_b_set_p_used(circular_buffer_t* pThis, TYPE_OF_ELEMENT_OF_BUFFER* index){
	pThis->p_used = index;
	if (pThis->p_used > (pThis->buffer + (LEN_BUFFER - 1)))
		pThis->p_used = pThis->buffer;
}


//*****************************************************************************
TYPE_OF_ELEMENT_OF_BUFFER c_b_get_from(circular_buffer_t* pThis){
	TYPE_OF_ELEMENT_OF_BUFFER temp = *(pThis->p_used);
	if ((pThis->p_actual) == (pThis->p_used))
		return (TYPE_OF_ELEMENT_OF_BUFFER) 0x0;
	else {
		c_b_set_p_used(pThis, (pThis->p_used + 1));
		return temp;
	}
}


