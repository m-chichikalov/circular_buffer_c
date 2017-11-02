/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
//-- unity: unit test framework
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
extern TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_p_actual(circular_buffer_t *pThis);
extern TYPE_OF_ELEMENT_OF_BUFFER* c_b_get_p_used(circular_buffer_t *pThis);
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
    TEST_ASSERT_EQUAL_PTR(c_b_get_p_actual(&rx_buffer), c_b_get_p_used(&rx_buffer));
    // -- Test that pointer to head points to the first element.
    TEST_ASSERT_EQUAL_PTR(&rx_buffer, c_b_get_p_actual(&rx_buffer));
}

void test_full_buffer(void){
	const char *str_to_long = "1234567897878";
	TEST_ASSERT_EQUAL_INT(
			-1,
			c_b_put_string(&rx_buffer, str_to_long)
			);
}

void test_full_buffer_ok(void){
	const char *str_ok = "1234";
	TEST_ASSERT_EQUAL_INT(
			0,
			c_b_put_string(&rx_buffer, str_ok)
			);
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



























