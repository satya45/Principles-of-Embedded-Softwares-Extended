#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
#include "main.h"
#include "circbuff.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

circbuff *SMA;
time_t t;
int buffer_init(void);
int clean_suite(void) { return 0; }

/*First Initialization Function*/
int buffer_init()
{
   SMA = circbuff_init(ELEMENTS);
   srand(time(NULL));
   return 0;
}

void test_circbuff_init()
{
   CU_ASSERT_NOT_EQUAL(0, ELEMENTS);
   CU_ASSERT_PTR_NOT_EQUAL(NULL, SMA);
}

void test_circbuff_reset()
{
   CU_ASSERT_EQUAL(0, SMA->head);
   CU_ASSERT_EQUAL(0, SMA->tail);
   CU_ASSERT_EQUAL(0, SMA->full_status);
   printf("%d\r\n", rand() % 50);
}

void test_push()
{

   /*Test the function with push less than the total buffer size*/
   uint8_t x = rand() % 256;
   push(SMA, x);
   CU_ASSERT_FALSE(buffer_status(SMA));
   CU_ASSERT_NOT_EQUAL(ELEMENTS, count);
   //CU_ASSERT_EQUAL(1,SMA->buffer[SMA->head-1%ELEMENTS]);

   /*Test the function with push equal to the total buffer size*/
   x = rand() % 256;
   push(SMA, x);
   CU_ASSERT_TRUE(buffer_status(SMA));
   CU_ASSERT_EQUAL(ELEMENTS, count);
   //CU_ASSERT_EQUAL(2,SMA->buffer[SMA->head-1%ELEMENTS]);

   /*Test the function with push equal to the total buffer size*/
   x = rand() % 256;
   push(SMA, x);
   CU_ASSERT_TRUE(buffer_status(SMA));
   CU_ASSERT_EQUAL(ELEMENTS, count);
   //CU_ASSERT_EQUAL(2,SMA->buffer[SMA->head-1%ELEMENTS]);
}

void test_pop()
{
   /*Test the function with pop less than the total buffer size*/
   pop(SMA);
   CU_ASSERT_TRUE(buffer_status(SMA));
   CU_ASSERT_NOT_EQUAL(ELEMENTS, count);

   /*Test the function with push equal to the total buffer size*/
   pop(SMA);
   CU_ASSERT_FALSE(buffer_status(SMA));
   CU_ASSERT_NOT_EQUAL(ELEMENTS, count);
   //CU_ASSERT_EQUAL(2,SMA->buffer[SMA->head-1%ELEMENTS]);

   /*Test the function with push equal to the total buffer size*/
   pop(SMA);
   CU_ASSERT_FALSE(buffer_status(SMA));
   CU_ASSERT_EQUAL(0, count);
   //CU_ASSERT_EQUAL(2,SMA->buffer[SMA->head-1%ELEMENTS]);
}

void test_buffer_size()
{
}

/*This function should be tested at the last*/
void test_circbuff_free()
{
   circbuff_free(SMA);
   //CU_ASSERT_PTR_EQUAL(NULL,SMA);
}

int main(void)
{

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   CU_pSuite pSuite = NULL;
   pSuite = CU_add_suite("CIRCULAR BUFFER TEST", buffer_init, clean_suite);
   if (NULL == pSuite)
   {
      CU_cleanup_registry();
      return -1;
   }
   if ((NULL == CU_add_test(pSuite, "Buffer Initialization Test", test_circbuff_init)) ||
       (NULL == CU_add_test(pSuite, "Buffer Reset Test", test_circbuff_reset)) ||
       (NULL == CU_add_test(pSuite, "Buffer Push Test", test_push)) ||
       (NULL == CU_add_test(pSuite, "Buffer Pop Test", test_pop)) ||
       (NULL == CU_add_test(pSuite, "Buffer Free Test", test_circbuff_free)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_set_output_filename("test");
   CU_automated_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
