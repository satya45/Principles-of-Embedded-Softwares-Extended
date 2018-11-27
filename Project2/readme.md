-------------------------Bare Metal Firmware on FRDM KL25Z. PRINCIPLES OF EMBEDDED SOFTWARE PROJECT-2--------------------------------------


  The project covers circular buffer implementation with error handling stating if it is full or empty ,the ability to resize the buffer at any point of time, ability to return the number of elements in the buffer and also the ability to reset the buffer . The circular Buffer has been implemented in such a way that it does not reserve any unused byte of data when the buffer is full. Any number of buffers can be implemented by just using the circbuff_init function.
  
  A C-Unit Test framework  has also been implemented. Unit testing is performed on the Linux platform. The test cases cover a variety of normal operational conditions as well as all reportable error conditions. An automated long-running randomized test case has also been implemented.
  
  The Project also successfully implements UART driver with a blocking and non-blocking Mode having two separate working code files respectively. The interrupt based UART calculates all the prime numbers upto the total number of characters when the ISR is not being serviced and displays it along with the report. In addition to this, a myprintf function has also been implemented using variadic function. The LED toggles in case of blocking Mode implementation in the main loop. There is no report output corruption (due to circular buffer overflow) regardless of input character rate. This has been tested by sending a large text file.
