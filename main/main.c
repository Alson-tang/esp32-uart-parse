#include "cmd_uart.h"
#include "cmd.h"

void app_main(void)
{
    comm_uart_init();

    cmd_register();
}
