/* Linker & Memory segments */

#include <stdio.h>
#include <stdint.h>

uint32_t config_data __attribute__((section(".my_custom_section"))) = 0xDEADBEEF;

int main(void)
{
    printf("value = %X\n",config_data);
    printf("address = %lu",&config_data);
    return 0;
}
