/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
//-- unity: unit test framework
#include <stdlib.h>
#include "unity.h"
//-- module being tested
#define TYPE_OF_ELEMENT_OF_BUFFER     char
#include "circular_buffer.h"
//-- other modules that need to be compiled
//-- mocked modules
/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/
// --
circular_buffer_t rx_buffer;

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/
extern TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_pHead(circular_buffer_t *pThis);
extern TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_pTail(circular_buffer_t *pThis);
extern void c_b_move_pHead(circular_buffer_t * pThis);
extern void c_b_move_pTail(circular_buffer_t* pThis);
 /*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp(void)
{
	c_b_init(&rx_buffer);
}

void tearDown(void)
{

}
/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_init_circular_buffer(void){
	// -- Check initialization function. Kind of ugly because the last always returns 1.
    TEST_ASSERT_EQUAL_INT(1 , c_b_init(&rx_buffer));
    // -- Test that pointer to head and tail is equal.
    TEST_ASSERT_EQUAL_PTR(c_b_get_pHead(&rx_buffer), c_b_get_pTail(&rx_buffer));
    // -- Test that pointer to head points to the first element.
    TEST_ASSERT_EQUAL_PTR(&rx_buffer, c_b_get_pHead(&rx_buffer));
}

void test_push_string_to_buffer_with_not_enough_space(void){
	const char str_to_long[] = "1234567897878";
// -- The buffer has NOT enough space (7 elements) for string str_to_long
// -- (14 elements). Function should return -1.
	TEST_ASSERT_EQUAL_INT(
			-1,
			c_b_put_string(&rx_buffer, str_to_long)
			);
}

void test_push_string_to_buffer_with_enough_space(void){
	const char str_ok[] = "1234";
// -- The buffer has enough space (7 elements) for string str_ok (5 elements).
// -- Function should return (7-5) 2 elements available in buffer after
// -- pushing str_ok to the buffer.
	TEST_ASSERT_EQUAL_INT(
			2,
			c_b_put_string(&rx_buffer, str_ok)
			);
}

void test_verifying_pushed_string_to_buffer(void){
	const char *str_ok = "5432";
	c_b_put_string(&rx_buffer, str_ok);
	int i = 0;
	TYPE_OF_ELEMENT_OF_BUFFER temp;
	do {
		temp = c_b_get_from(&rx_buffer);
		TEST_ASSERT_EQUAL_INT8(str_ok[i++], temp);
	} while (temp != 0);
 }

void test_put_one_element_into_buffer(void){
	char a = 'a';
	char b = 'b';
	c_b_put(&rx_buffer, &a);
	c_b_put(&rx_buffer, &b);
	TEST_ASSERT_EQUAL_INT8(
			a,
			c_b_get_from(&rx_buffer)
			);
	TEST_ASSERT_EQUAL_INT8(
			b,
			c_b_get_from(&rx_buffer)
			);

}

void test_make_buffer_full(void){
	char a = 'a';

	int free_space      = c_b_get_free_space(&rx_buffer);
	int free_space_after = c_b_put(&rx_buffer, &a);
	TEST_ASSERT_EQUAL_INT((free_space - 1), free_space_after);

	int i = 1;
	while((c_b_get_free_space(&rx_buffer) != 0) | (i == 10) ){
		c_b_put(&rx_buffer, &a);
		i++;
	}
	TEST_ASSERT_NOT_EQUAL(i, 10);
	TEST_ASSERT_EQUAL_INT((LEN_BUFFER - 1), i);
	TEST_ASSERT_EQUAL_INT(
			-1,
			c_b_put(&rx_buffer, &a)
			);
}

void test_get_free_space_in_buffer(void){
	int i;
	// -- Empty buffer is able to take (LEN_BUFFER-1) elements.
	TEST_ASSERT_EQUAL_INT((LEN_BUFFER-1), c_b_get_free_space(&rx_buffer));
	for (i=0; i<5; i++){
		c_b_move_pHead(&rx_buffer);
	}
	TEST_ASSERT_EQUAL_INT(2, c_b_get_free_space(&rx_buffer));
	for (i=0; i<7; i++){
		c_b_move_pTail(&rx_buffer);
	}
	TEST_ASSERT_EQUAL_INT(1, c_b_get_free_space(&rx_buffer));
	c_b_move_pTail(&rx_buffer);
	TEST_ASSERT_EQUAL_INT(2, c_b_get_free_space(&rx_buffer));
	// -- made one circle around, ptr of Tail should points to first element.
	TEST_ASSERT_EQUAL_PTR(&rx_buffer, c_b_get_pTail(&rx_buffer));
}




















