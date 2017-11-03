/*
 * cicle_buffer.h
 * Author: m.chichikalov@outlook.com
 */
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

//*****************************************************************************
// You should define the length of buffer in LEN_BUFFER
#define LEN_BUFFER                    8
#ifndef TYPE_OF_ELEMENT_OF_BUFFER
	#define TYPE_OF_ELEMENT_OF_BUFFER     char
#endif /* TYPE_OF_ELEMENT_OF_BUFFER */
//
//*****************************************************************************

typedef struct {
	TYPE_OF_ELEMENT_OF_BUFFER buffer[LEN_BUFFER];
	TYPE_OF_ELEMENT_OF_BUFFER* pHead;
	TYPE_OF_ELEMENT_OF_BUFFER* pTail;
}circular_buffer_t;

int c_b_init(circular_buffer_t *);
int c_b_get_free_space(circular_buffer_t *);

int c_b_put(circular_buffer_t *, TYPE_OF_ELEMENT_OF_BUFFER *);
int c_b_put_string(circular_buffer_t *, const TYPE_OF_ELEMENT_OF_BUFFER*);

TYPE_OF_ELEMENT_OF_BUFFER c_b_get_from(circular_buffer_t *);

#endif /* CIRCULAR_BUFFER_H */
