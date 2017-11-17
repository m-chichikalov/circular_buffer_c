/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
//-- unity: unit test framework
#include "test_circular_buffer_char.h"
#include "unity.h"
//-- module being tested
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

//////////////////////-- c_b_put_string --/////////////////////////////////////
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
		temp = c_b_get(&rx_buffer);
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
			c_b_get(&rx_buffer)
			);
	TEST_ASSERT_EQUAL_INT8(
			b,
			c_b_get(&rx_buffer)
			);

}

//////////////////////-- c_b_free_space --/////////////////////////////////////
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

/////////////////////////-- c_b_put_mem --/////////////////////////////////////
void test_put_mem_return_error(void){
	const char arr_to_long[10] = {1, 2, 3, 4, 5,
			                      6, 7, 8, 9, 10};
// -- The buffer has NOT enough space (7 elements) for array
// -- (10 elements). Function should return -1.
	TEST_ASSERT_EQUAL_INT(
			-1,
			c_b_put_mem(&rx_buffer, arr_to_long, 10)
			);
}

void test_put_mem_return_free_space(void){
	const char  arr_ok[5] = {1, 2, 3, 4, 5};
	const char arr1_ok[1] = {1};
// -- The buffer has enough space (7 elements) for array
// -- (5 and 1 elements). Function should return free space in buffer.
	TEST_ASSERT_EQUAL_INT(
			2,
			c_b_put_mem(&rx_buffer, arr_ok, 5)
			);
	TEST_ASSERT_EQUAL_INT(
			1,
			c_b_put_mem(&rx_buffer, arr1_ok, 1)
			);
	TEST_ASSERT_EQUAL_INT(
			0,
			c_b_put_mem(&rx_buffer, arr1_ok, 1)
			);
}

void test_put_mem_verifying_pushed_array_to_buffer(void){
	const char arr_ok[5] = {15, 26, 13, 40, 195};
	c_b_put_mem(&rx_buffer, arr_ok, 5);
	int i = 0;
	for (i=0; i<5; i++){
		TEST_ASSERT_EQUAL_INT8(arr_ok[i], c_b_get(&rx_buffer));
	}
 }

///////////////////-- c_b_find_character --/////////////////////////////////////
void test_find_character_return(){
	const char *str_ok = "Embed";
	c_b_put_string(&rx_buffer, str_ok);

	int position = c_b_find_character(&rx_buffer, 'b');
	TEST_ASSERT_EQUAL_INT(3, position);

	position = c_b_find_character(&rx_buffer, 'E');
	TEST_ASSERT_EQUAL_INT(1, position);

	position = c_b_find_character(&rx_buffer, 'A');
	TEST_ASSERT_EQUAL_INT(0, position);

	position = c_b_find_character(&rx_buffer, 0x0);
	TEST_ASSERT_EQUAL_INT(6, position);

	char data = 0x51;
	char* pdata = &data;

	c_b_init(&rx_buffer);
	for (int i=0; i<8; i++){
		c_b_put(&rx_buffer, pdata);
	}
	TEST_ASSERT_EQUAL_INT(0, c_b_get_free_space(&rx_buffer));

	position = c_b_find_character(&rx_buffer, 0x00);
	TEST_ASSERT_EQUAL_INT(0, position);

}

///////////////////-- c_b_get_string --/////////////////////////////////////////
void test_get_string_return_string(void){
	char *str_1 = "Test!";
	char *str_2 = "Test2!";
	char str[10];
	char *str_;
	int i;
	str_ = str;

	c_b_put_string(&rx_buffer, str_1);

	int result = c_b_get_string(&rx_buffer, str);
	TEST_ASSERT_EQUAL_INT(1, result);

	for (i=0; i<6; i++){
		if (*(str_1++) != str[i])
			TEST_FAIL_MESSAGE("not equal");
	}

	TEST_ASSERT_EQUAL_INT(7, c_b_get_free_space(&rx_buffer));

	c_b_put_string(&rx_buffer, str_2);

	result = c_b_get_string(&rx_buffer, str_);
	TEST_ASSERT_EQUAL_INT(1, result);

	for (i=0; i<7; i++){
		if (*(str_1++) != *(str_++))
			TEST_FAIL_MESSAGE("not equal");
	}
}

void test_get_string_return_0(void){
	char str[10];
	char data = 0x51;
	char* pdata = &data;

	c_b_init(&rx_buffer);
	for (int i=0; i<8; i++){
		c_b_put(&rx_buffer, pdata);
	}
	TEST_ASSERT_EQUAL_INT(0, c_b_get_free_space(&rx_buffer));

	int result = c_b_get_string(&rx_buffer, str);
	TEST_ASSERT_EQUAL_INT(0, result);
}

///////////////////-- c_b_get_string --/////////////////////////////////////////
void test_get_mem_return_error(void){
	char mem[10];
	int result = c_b_get_mem(&rx_buffer, mem, 10);
	TEST_ASSERT_EQUAL_INT(0, result);
}

void test_get_mem_return_ok(void){
	char mem[7];
	c_b_put_string(&rx_buffer, "1234");
	int result = c_b_get_mem(&rx_buffer, mem, 5);
	TEST_ASSERT_EQUAL_INT(1, result);

	c_b_put_string(&rx_buffer, "123456");
	result = c_b_get_mem(&rx_buffer, mem, 7);
	TEST_ASSERT_EQUAL_INT(1, result);
}

void test_get_mem_verifying_pulled_array_from_buffer(void){
	const char arr_ok[7] = {55, 126, 143, 40, 95, 0, 4};
	char  arr_veryfing[7];
	c_b_put_mem(&rx_buffer, arr_ok, 7);
	c_b_get_mem(&rx_buffer, arr_veryfing, 7);
	for (int i=0; i<7; i++){
		TEST_ASSERT_EQUAL_INT8(arr_ok[i], arr_veryfing[i]);
	}
 }

















