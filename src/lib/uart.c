#include "uart.h"
#include <core_cm3.h>

#if USE_UART_BUFFER
#if USE_UART0
static CircularBuffer uart0ReadBuffer;
static char           uart0ReadBufferData[UART_READ_BUFFER_SIZE];
static CircularBuffer uart0WriteBuffer;
static char           uart0WriteBufferData[UART_WRITE_BUFFER_SIZE];
#endif
#if USE_UART1
static CircularBuffer uart1ReadBuffer;
static char           uart1ReadBufferData[UART_READ_BUFFER_SIZE];
static CircularBuffer uart1WriteBuffer;
static char           uart1WriteBufferData[UART_WRITE_BUFFER_SIZE];
#endif
#if USE_UART2
static CircularBuffer uart2ReadBuffer;
static char           uart2ReadBufferData[UART_READ_BUFFER_SIZE];
static CircularBuffer uart2WriteBuffer;
static char           uart2WriteBufferData[UART_WRITE_BUFFER_SIZE];
#endif
#if USE_UART3
static CircularBuffer uart3ReadBuffer;
static char           uart3ReadBufferData[UART_READ_BUFFER_SIZE];
static CircularBuffer uart3WriteBuffer;
static char           uart3WriteBufferData[UART_WRITE_BUFFER_SIZE];
#endif
#endif

#if USE_UART_TASK
static char taskBuffer0[UART_TASK_BUFFER_SIZE];
static char taskBuffer1[UART_TASK_BUFFER_SIZE];
static char taskBuffer2[UART_TASK_BUFFER_SIZE];
static char taskBuffer3[UART_TASK_BUFFER_SIZE];

static uint16 taskBufferPos0;
static uint16 taskBufferPos1;
static uint16 taskBufferPos2;
static uint16 taskBufferPos3;

static void (* taskFunctionPointer0)(char *);
static void (* taskFunctionPointer1)(char *);
static void (* taskFunctionPointer2)(char *);
static void (* taskFunctionPointer3)(char *);

static void (* errorFunctionPointer0)(void);
static void (* errorFunctionPointer1)(void);
static void (* errorFunctionPointer2)(void);
static void (* errorFunctionPointer3)(void);
#endif

//char printfBuffer[UART_PRINTF_BUFFER_SIZE];

static int8 initializeUart0(uint32 baudrate);
static int8 initializeUart1(uint32 baudrate);
static int8 initializeUart2(uint32 baudrate);
static int8 initializeUart3(uint32 baudrate);

static int8 putcharUart0(char c);
static int8 putcharUart1(char c);
static int8 putcharUart2(char c);
static int8 putcharUart3(char c);

static int8 writeDataUart0(void *data, uint32 length);
static int8 writeDataUart1(void *data, uint32 length);
static int8 writeDataUart2(void *data, uint32 length);
static int8 writeDataUart3(void *data, uint32 length);

static int8 getcharUart0(char* c);
static int8 getcharUart1(char* c);
static int8 getcharUart2(char* c);
static int8 getcharUart3(char* c);

static void flushUart0(void);  
static void flushUart1(void);  
static void flushUart2(void);  
static void flushUart3(void);  

static void setBaudrateUart0(uint32 baudrate);
static void setBaudrateUart1(uint32 baudrate);
static void setBaudrateUart2(uint32 baudrate);
static void setBaudrateUart3(uint32 baudrate);

int8 initializeUart0(uint32 baudrate)
{
#if (USE_UART_TASK == 1)
    taskFunctionPointer0 = NULL;
    errorFunctionPointer0 = NULL;
    taskBufferPos0 = 0u;
#endif
    
    UART0_POWER_ON();               // Turn on power to UART0
    UART0_ENABLE_CLK();             // Turn on UART0 peripheral clock
    
    UART0_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART0_SET_DLAB();               // set Divisor Latch Accress Bit
    UART0_SET_BAUDRATE(baudrate);   // Set baud rate
    UART0_CLEAR_DLAB();
   
    //UART0_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART0_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (Cb_initialize(&uart0ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char), (void*)uart0ReadBufferData) == (int8)(-1))      // Initialize circular read buffer
        return (int8)(-1);
    
    if (Cb_initialize(&uart0WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char), (void*)uart0WriteBufferData) == (int8)(-1))    //Initialize circular write buffer
        return (int8)(-1);
    
    UART0_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART0_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return (int8)(0);
}

int8 initializeUart1(uint32 baudrate)
{
#if (USE_UART_TASK == 1)
    taskFunctionPointer1 = NULL;
    errorFunctionPointer1 = NULL;
    taskBufferPos1 = 0u;
#endif
    
    UART1_POWER_ON();               // Turn on power to UART1
    UART1_ENABLE_CLK();             // Turn on UART1 peripheral clock
    
    UART1_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART1_SET_DLAB();               // set Divisor Latch Accress Bit
    UART1_SET_BAUDRATE(baudrate);   // Set baud rate
    UART1_CLEAR_DLAB();
   
    //UART1_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART1_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (Cb_initialize(&uart1ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char), (void*)uart1ReadBufferData) == (int8)(-1))      // Initialize circular read buffer
        return (int8)(-1);
    
    if (Cb_initialize(&uart1WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char), (void*)uart1WriteBufferData) == (int8)(-1))    //Initialize circular write buffer
        return (int8)(-1);
    
    UART1_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART1_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return (int8)(0);
}

int8 initializeUart2(uint32 baudrate)
{
#if (USE_UART_TASK == 1)
    taskFunctionPointer2 = NULL;
    errorFunctionPointer2 = NULL;
    taskBufferPos2 = 0u;
#endif
    
    UART2_POWER_ON();               // Turn on power to UART2
    UART2_ENABLE_CLK();             // Turn on UART2 peripheral clock
    
    UART2_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART2_SET_DLAB();               // set Divisor Latch Accress Bit
    UART2_SET_BAUDRATE(baudrate);   // Set baud rate
    UART2_CLEAR_DLAB();
   
    //UART2_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART2_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (Cb_initialize(&uart2ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char), (void*)uart2ReadBufferData) == (int8)(-1))      // Initialize circular read buffer
        return (int8)(-1);
    
    if (Cb_initialize(&uart2WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char), (void*)uart2WriteBufferData) == (int8)(-1))    //Initialize circular write buffer
        return (int8)(-1);
    
    UART2_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART2_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return (int8)(0);
}

int8 initializeUart3(uint32 baudrate)
{
#if (USE_UART_TASK == 1)
    taskFunctionPointer3 = NULL;
    errorFunctionPointer3 = NULL;
    taskBufferPos3 = 0u;
#endif
    
    UART3_POWER_ON();               // Turn on power to UART3
    UART3_ENABLE_CLK();             // Turn on UART3 peripheral clock
    
    UART3_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART3_SET_DLAB();               // set Divisor Latch Accress Bit
    UART3_SET_BAUDRATE(baudrate);   // Set baud rate
    UART3_CLEAR_DLAB();
   
    //UART3_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART3_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (Cb_initialize(&uart3ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char), (void*)uart3ReadBufferData) == (int8)(-1))      // Initialize circular read buffer
        return (int8)(-1);
    
    if (Cb_initialize(&uart3WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char), (void*)uart3WriteBufferData) == (int8)(-1))    //Initialize circular write buffer
        return (int8)(-1);
    
    UART3_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART3_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return (int8)(0);
}

int8 Uart_initialize(Uart uart, uint32 baudrate)
{
    if (uart == Uart0)
    {
        return initializeUart0(baudrate);
    }
    else if (uart == Uart1)
    {
        return initializeUart1(baudrate);
    }
    else if (uart == Uart2)
    {
        return initializeUart2(baudrate);
    }
    else if (uart == Uart3)
    {
        return initializeUart3(baudrate);
    }
    else
    {
        return (int8)(-1);
    }
}

#if (USE_UART_BUFFER == 1)
void UART0_IRQHANDLER()
{
    char c;
    
    if (UART0_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART0_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        Cb_put(&uart0ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (Cb_get(&uart0WriteBuffer,&c) == (int8)(0))   // If data is available
            UART0_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

#if (USE_UART_BUFFER == 1)
void UART1_IRQHANDLER()
{
    char c;
    
    if (UART1_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART1_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        Cb_put(&uart1ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (Cb_get(&uart1WriteBuffer,&c) == (int8)(0))   // If data is available
            UART1_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

#if (USE_UART_BUFFER == 1)
void UART2_IRQHANDLER()
{
        char c;
    
    if (UART2_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART2_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        Cb_put(&uart2ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (Cb_get(&uart2WriteBuffer,&c) == (int8)(0))   // If data is available
            UART2_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

#if (USE_UART_BUFFER == 1)
void UART3_IRQHANDLER()
{
    char c;
    
    if (UART3_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART3_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        Cb_put(&uart3ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (Cb_get(&uart3WriteBuffer,&c) == (int8)(0))   // If data is available
            UART3_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

int8 putcharUart0(char c)
{
#if (USE_UART_BUFFER == 1)
    if (Cb_put(&uart0WriteBuffer, &c) == (int8)(0))
    {
        if (UART0_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART0_SET_IRQS();
        
        return (int8)(0);
    }
    else 
        return (int8)(-1);
#else
    while(!UART0_THR_EMPTY());         // Block until THR empty
    UART0_SET_CHAR(c);
    return (int8)(0);
#endif
}

int8 putcharUart1(char c)
{
#if (USE_UART_BUFFER == 1)
    if (Cb_put(&uart1WriteBuffer, &c) == (int8)(0))
    {
        if (UART1_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART1_SET_IRQS();
        
        return (int8)(0);
    }
    else 
        return (int8)(-1);
#else
    while(!UART1_THR_EMPTY());         // Block until THR empty
    UART1_SET_CHAR(c);
    return (int8)(0);
#endif
}

int8 putcharUart2(char c)
{
#if (USE_UART_BUFFER == 1)
    if (Cb_put(&uart2WriteBuffer, &c) == (int8)(0))
    {
        if (UART2_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART2_SET_IRQS();
        
        return (int8)(0);
    }
    else 
        return (int8)(-1);
#else
    while(!UART2_THR_EMPTY());         // Block until THR empty
    UART2_SET_CHAR(c);
    return (int8)(0);
#endif
}

int8 putcharUart3(char c)
{
#if (USE_UART_BUFFER == 1)
    if (Cb_put(&uart3WriteBuffer, &c) == (int8)(0))
    {
        if (UART3_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART3_SET_IRQS();
        
        return (int8)(0);
    }
    else 
        return (int8)(-1);
#else
    while(!UART3_THR_EMPTY());         // Block until THR empty
    UART3_SET_CHAR(c);
    return (int8)(0);
#endif
}

int8 Uart_putchar(Uart uart, char c)
{
    if (uart == Uart0)
    {
        return putcharUart0(c);
    }
    else if (uart == Uart1)
    {
        return putcharUart1(c);
    }
    else if (uart == Uart2)
    {
        return putcharUart2(c);
    }
    else if (uart == Uart3)
    {
        return putcharUart3(c);
    }
    else
    {
        return (int8)(-1);
    }
}

int8 writeDataUart0(void *data, uint32 length)
{
    uint32 i;
    
    for (i = 0u; i < length; i++)
    {
        if (putcharUart0(*(char*)(data+i)) == (int8)(-1))
            return (int8)(-1);
    }
    return (int8)(0);
}

int8 writeDataUart1(void *data, uint32 length)
{
    uint32 i;
    
    for (i = 0u; i < length; i++)
    {
        if (putcharUart1(*(char*)(data+i)) == (int8)(-1))
            return (int8)(-1);
    }
    return (int8)(0);
}

int8 writeDataUart2(void *data, uint32 length)
{
    uint32 i;
    
    for (i = 0u; i < length; i++)
    {
        if (putcharUart2(*(char*)(data+i)) == (int8)(-1))
            return (int8)(-1);
    }
    return (int8)(0);
}

int8 writeDataUart3(void *data, uint32 length)
{
    uint32 i;
    
    for (i = 0u; i < length; i++)
    {
        if (putcharUart3(*(char*)(data+i)) == (int8)(-1))
            return (int8)(-1);
    }
    return (int8)(0);
}

int8 Uart_writeData(Uart uart, void *data, uint32 length)
{
    if (uart == Uart0)
    {
        return writeDataUart0(data, length);
    }
    else if (uart == Uart1)
    {
        return writeDataUart1(data, length);
    }
    else if (uart == Uart2)
    {
        return writeDataUart2(data, length);
    }
    else if (uart == Uart3)
    {
        return writeDataUart3(data, length);
    }
    else
    {
        return (int8)(-1);
    }
}

int8 getcharUart0(char *c)
{
#if (USE_UART_BUFFER == 1)
    return Cb_get(&uart0ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART0_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART0_READ_CHAR();             // Read Receiver buffer register
    return (int8)(0);
#endif
}

int8 getcharUart1(char *c)
{
#if (USE_UART_BUFFER == 1)
    return Cb_get(&uart1ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART1_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART1_READ_CHAR();             // Read Receiver buffer register
    return (int8)(0);
#endif
}

int8 getcharUart2(char *c)
{
#if (USE_UART_BUFFER == 1)
    return Cb_get(&uart2ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART2_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART2_READ_CHAR();             // Read Receiver buffer register
    return (int8)(0);
#endif
}

int8 getcharUart3(char *c)
{
#if (USE_UART_BUFFER == 1)
    return Cb_get(&uart3ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART3_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART3_READ_CHAR();             // Read Receiver buffer register
    return (int8)(0);
#endif
}

int8 Uart_getchar(Uart uart, char *c)
{
    if (uart == Uart0)
    {
        return getcharUart0(c);
    }
    else if (uart == Uart1)
    {
        return getcharUart1(c);
    }
    else if (uart == Uart2)
    {
        return getcharUart2(c);
    }
    else if (uart == Uart3)
    {
        return getcharUart3(c);
    }
    else
    {
        return (int8)(-1);
    }
}

void Uart_putat( void * ptr, const char s)
{
    Uart_putchar(*((Uart*)ptr), s);
}

void Uart_printf(Uart uart, char *args, ...)
{    
    va_list arg_ptr;
    
    va_start(arg_ptr,args);
    xformat(Uart_putat, (void*)(&uart), args, arg_ptr);
    va_end(arg_ptr);
}

void flushUart0(void)
{
    char byteRead;
    while (Cb_get(&uart0ReadBuffer, (void*)&byteRead) == (int8)(0))
        ;
    while (Cb_get(&uart0WriteBuffer, (void*)&byteRead) == (int8)(0))
        ;
}

void flushUart1(void)
{
    char byteRead;
    while (Cb_get(&uart1ReadBuffer, (void*)&byteRead) == (int8)(0))
        ;
    while (Cb_get(&uart1WriteBuffer, (void*)&byteRead) == (int8)(0))
        ;
}

void flushUart2(void)
{
    char byteRead;
    while (Cb_get(&uart2ReadBuffer, (void*)&byteRead) == (int8)(0))
        ;
    while (Cb_get(&uart2WriteBuffer, (void*)&byteRead) == (int8)(0))
        ;
}

void flushUart3(void)
{
    char byteRead;
    while (Cb_get(&uart3ReadBuffer, (void*)&byteRead) == (int8)(0))
        ;
    while (Cb_get(&uart3WriteBuffer, (void*)&byteRead) == (int8)(0))
        ;
}

void Uart_flush(Uart uart)
{
    if (uart == Uart0)
    {
        flushUart0();
    }
    else if (uart == Uart1)
    {
        flushUart1();
    }
    else if (uart == Uart2)
    {
        flushUart2();
    }
    else if (uart == Uart3)
    {
        flushUart3();
    }
}

void setBaudrateUart0(uint32 baudrate)
{
    UART0_SET_DLAB();               // set Divisor Latch Accress Bit
    UART0_SET_BAUDRATE(baudrate);   // Set baud rate
    UART0_CLEAR_DLAB();
    
    UART0_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
}

void setBaudrateUart1(uint32 baudrate)
{
    UART1_SET_DLAB();               // set Divisor Latch Accress Bit
    UART1_SET_BAUDRATE(baudrate);   // Set baud rate
    UART1_CLEAR_DLAB();
    
    UART1_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
}

void setBaudrateUart2(uint32 baudrate)
{
    UART2_SET_DLAB();               // set Divisor Latch Accress Bit
    UART2_SET_BAUDRATE(baudrate);   // Set baud rate
    UART2_CLEAR_DLAB();
    
    UART2_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
}

void setBaudrateUart3(uint32 baudrate)
{
    UART3_SET_DLAB();               // set Divisor Latch Accress Bit
    UART3_SET_BAUDRATE(baudrate);   // Set baud rate
    UART3_CLEAR_DLAB();
    
    UART3_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
}

void Uart_setBaudrate(Uart uart, uint32 baudrate)
{
    if (uart == Uart0)
    {
        setBaudrateUart0(baudrate);
    }
    else if (uart == Uart1)
    {
        setBaudrateUart1(baudrate);
    }
    else if (uart == Uart2)
    {
        setBaudrateUart2(baudrate);
    }
    else if (uart == Uart3)
    {
        setBaudrateUart3(baudrate);
    }
}

#if (USE_UART_TASK == 1)
void Uart_setProcessFunction(Uart uart, void (* func)(char *))
{
    if (uart == Uart0)
    {
        taskFunctionPointer0 = func;
    }
    else if (uart == Uart1)
    {
        taskFunctionPointer1 = func;
    }
    else if (uart == Uart2)
    {
        taskFunctionPointer2 = func;
    }
    else if (uart == Uart3)
    {
        taskFunctionPointer3 = func;
    }
}
void Uart_setErrorFunction(Uart uart, void (* func)())
{
    if (uart == Uart0)
    {
        errorFunctionPointer0 = func;
    }
    else if (uart == Uart1)
    {
        errorFunctionPointer1 = func;
    }
    else if (uart == Uart2)
    {
        errorFunctionPointer2 = func;
    }
    else if (uart == Uart3)
    {
        errorFunctionPointer3 = func;
    }
}

void Uart_processTask0()
{
    static char receivedData;
    while (getcharUart0(&receivedData) == (int8)(0))
    {
        if ((receivedData != UART0_COMMAND_CHAR) && 
            (receivedData != UART0_SECONDARY_COMMAND_CHAR))
        {
            taskBuffer0[taskBufferPos0] = receivedData;
            if (taskBufferPos0 < (UART_TASK_BUFFER_SIZE-1u))
            {
                taskBufferPos0++;
            }
            else
            {
                (*errorFunctionPointer0)();
                taskBufferPos0 = 0u;
            }
        }
        else
        {
            taskBuffer0[taskBufferPos0] = '\0';
            (*taskFunctionPointer0)(taskBuffer0);
            taskBufferPos0 = 0u;
        }
    }
}

void Uart_processTask1()
{
    static char receivedData;
    while (getcharUart1(&receivedData) == (int8)(0))
    {
        if ((receivedData != UART1_COMMAND_CHAR) && 
            (receivedData != UART1_SECONDARY_COMMAND_CHAR))
        {
            taskBuffer1[taskBufferPos1] = receivedData;
            if (taskBufferPos1 < (UART_TASK_BUFFER_SIZE-1u))
            {
                taskBufferPos1++;
            }
            else
            {
                (*errorFunctionPointer1)();
                taskBufferPos1 = 0u;
            }
        }
        else
        {
            taskBuffer1[taskBufferPos1] = '\0';
            (*taskFunctionPointer1)(taskBuffer1);
            taskBufferPos1 = 0u;
        }
    }
}

void Uart_processTask2()
{
    static char receivedData;
    while (getcharUart2(&receivedData) == (int8)(0))
    {
        if ((receivedData != UART2_COMMAND_CHAR) && 
            (receivedData != UART2_SECONDARY_COMMAND_CHAR))
        {
            taskBuffer2[taskBufferPos2] = receivedData;
            if (taskBufferPos2 < (UART_TASK_BUFFER_SIZE-1u))
            {
                taskBufferPos2++;
            }
            else
            {
                (*errorFunctionPointer2)();
                taskBufferPos2 = 0u;
            }
        }
        else
        {
            taskBuffer2[taskBufferPos2] = '\0';
            (*taskFunctionPointer2)(taskBuffer2);
            taskBufferPos2 = 0u;
        }
    }
}

void Uart_processTask3()
{
    static char receivedData;
    while (getcharUart3(&receivedData) == (int8)(0))
    {
        if ((receivedData != UART3_COMMAND_CHAR) && 
            (receivedData != UART3_SECONDARY_COMMAND_CHAR))
        {
            taskBuffer3[taskBufferPos3] = receivedData;
            if (taskBufferPos3 < (UART_TASK_BUFFER_SIZE-1u))
            {
                taskBufferPos3++;
            }
            else
            {
                (*errorFunctionPointer3)();
                taskBufferPos3 = 0u;
            }
        }
        else
        {
            taskBuffer3[taskBufferPos3] = '\0';
            (*taskFunctionPointer3)(taskBuffer3);
            taskBufferPos3 = 0u;
        }
    }
}

void Uart_processTask(Uart uart)
{
    if (uart == Uart0)
    {
        Uart_processTask0();
    }
    else if (uart == Uart1)
    {
        Uart_processTask1();
    }
    else if (uart == Uart2)
    {
        Uart_processTask2();
    }
    else if (uart == Uart3)
    {
        Uart_processTask3();
    }
}
#endif
