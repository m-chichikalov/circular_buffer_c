/*
 * cicle_buffer.c
 * Author: m.chichikalov@outlook.com
TODO ??? - add callback function which will execute when buffer is full.
DONE - add function which return a value of free space in the buffer.
 */
#include "circular_buffer.h"
//*****************************************************************************
// static functions
static void c_b_modify_buffer(circular_buffer_t *, const TYPE_OF_ELEMENT_OF_BUFFER *);
// -- other I used in tests. Can't declare as static.
void c_b_move_pHead(circular_buffer_t * pThis);
void c_b_move_pTail(circular_buffer_t* pThis);
TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_pHead(circular_buffer_t *pThis);
TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_pTail(circular_buffer_t *pThis);

//*****************************************************************************
int c_b_init(circular_buffer_t* pThis){
	pThis->pHead = pThis->buffer;
	pThis->pTail   = pThis->buffer;
	return 1;
}

//*****************************************************************************
// Put string in buffer. If not enough space return -1.
// String should be NULL determined.
// After the data was put return available space in buffer.
//*****************************************************************************
int c_b_put_string(circular_buffer_t* pThis, const TYPE_OF_ELEMENT_OF_BUFFER* str){
	int len = 0;
	while (str[len++] != 0x0){
	}
	int free_space_in_buffer = c_b_get_free_space(pThis);
	if (len > free_space_in_buffer)
		return -1;
	for (int i=0; i<len; i++){
		c_b_modify_buffer(pThis, &str[i]);
	}
	return (free_space_in_buffer - len);
}


//*****************************************************************************
// Put one element in buffer. If not enough space return -1.
// After the data was put return available space in buffer.
//*****************************************************************************
int c_b_put(circular_buffer_t* pThis, TYPE_OF_ELEMENT_OF_BUFFER *pData){
	int free_space_in_buffer = c_b_get_free_space(pThis);
	if (free_space_in_buffer == 0)
		return -1;
	c_b_modify_buffer(pThis, pData);
	return (free_space_in_buffer - 1);
}

//*****************************************************************************
// todo Put one element in buffer. If not enough space return -1.
// After the data was put return available space in buffer.
//*****************************************************************************
int c_b_put_mem(circular_buffer_t* pThis, const TYPE_OF_ELEMENT_OF_BUFFER* pointer, int len){
	int free_space_in_buffer = c_b_get_free_space(pThis);
	if (len > free_space_in_buffer)
		return -1;
	for (int i=0; i<len; i++){
		c_b_modify_buffer(pThis, pointer++);
	}
	return (free_space_in_buffer - len);
}

//*****************************************************************************
static void c_b_modify_buffer(circular_buffer_t* pThis, const TYPE_OF_ELEMENT_OF_BUFFER *pData){
	*pThis->pHead = *pData;
	c_b_move_pHead(pThis);
}

//*****************************************************************************
inline TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_pHead(circular_buffer_t* pThis){
	return pThis->pHead;
}

//*****************************************************************************
inline TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_pTail(circular_buffer_t* pThis){
	return pThis->pTail;
}

//*****************************************************************************
void c_b_move_pHead(circular_buffer_t* pThis){
	pThis->pHead += 1;
	if (pThis->pHead > (pThis->buffer + (LEN_BUFFER - 1)))
		pThis->pHead = pThis->buffer;
}

//*****************************************************************************
void c_b_move_pTail(circular_buffer_t* pThis){
	pThis->pTail += 1;
	if (pThis->pTail > (pThis->buffer + (LEN_BUFFER - 1)))
		pThis->pTail = pThis->buffer;
}


//*****************************************************************************
TYPE_OF_ELEMENT_OF_BUFFER c_b_get_from(circular_buffer_t* pThis){
	TYPE_OF_ELEMENT_OF_BUFFER temp = *(pThis->pTail);
	if ((pThis->pHead) == (pThis->pTail))
		return (TYPE_OF_ELEMENT_OF_BUFFER) 0x0;
	else {
		c_b_move_pTail(pThis);
		return temp;
	}
}

//*****************************************************************************
int c_b_get_free_space(circular_buffer_t* pThis){
	int temp = ((pThis->pHead + 1 ) - pThis->pTail);
	if (temp > 0)
		return (LEN_BUFFER - temp);
	else
		return abs(temp);
}


