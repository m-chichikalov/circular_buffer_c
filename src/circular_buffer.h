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
	#define TYPE_OF_ELEMENT_OF_BUFFER     int
#endif /* TYPE_OF_ELEMENT_OF_BUFFER */
//
//*****************************************************************************

typedef struct {
	TYPE_OF_ELEMENT_OF_BUFFER buffer[LEN_BUFFER];
	TYPE_OF_ELEMENT_OF_BUFFER* p_actual;
	TYPE_OF_ELEMENT_OF_BUFFER* p_used;
}circular_buffer_t;

int c_b_init(circular_buffer_t *);
int c_b_put(circular_buffer_t *, TYPE_OF_ELEMENT_OF_BUFFER *);
int c_b_put_string(circular_buffer_t *, const char*);
TYPE_OF_ELEMENT_OF_BUFFER c_b_get_from(circular_buffer_t *);

#endif /* CIRCULAR_BUFFER_H */
