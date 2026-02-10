/*  Function pointer is a variable that stores the address of a function, enabling us to call the functions 
    through pointer. simple syntax of a function pointer looks like this:
    return_type (* pointer_name)(param_types);
ex: void (*handler)(int); / here declared a pointer to the function which takes int & returns void /
    to assign a function to this function pointer, if a function is " void myFunc(int); ", then we can just do
    handler = myFunc;   /without any paranthesis/ 

    to call or invoke it, 
    (*handler)(5); /or in modern C/ handler(5);
*/



/* Implement a simple command handler using function pointers.
1. Define three functions: led_on(), led_off(), and get_status(). Each function should take no arguments and return void. 
Inside each function, simply print a message indicating which function was called (e.g., "LED is ON").
2. Define a function pointer type named CommandHandler that points to a function with a void return type and no parameters.
3. Create an array of CommandHandler pointers named command_table. This array should be populated with the addresses of your three functions.
4. In the main function, use a loop to iterate through the command_table and call each function using its pointer.
*/



#include <stdio.h>
#include <stdint.h>

void led_on(void);
void led_off(void);
void get_status(void);

typedef void (*CommandHandler)(void);

CommandHandler command_table[] = {
    led_on,
    led_off,
    get_status
};

int main(void)
{
    for(int i=0;i<3;i++)
    {
        command_table[i]();
    }
    return 0;
}

void led_on(void)
{
    printf("LED is ON\n");
}
void led_off(void)
{
    printf("LED is OFF\n");
}
void get_status(void)
{
    printf("Get Status\n");
}
