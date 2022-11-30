#include "driver/uart.h"
#include "esp_log.h"
#include "cmd_uart.h"

#define COMM_UART_QUEUE_SIZE            (30)
#define COMM_UART_BUFF_SIZE             (1024)
#define COMM_UART_PARSE_TASK_PRIORITY   (5)
// #define COMM_OUTPUT_RESPONSE_FLAG       (1)

extern void cmd_parse_task(void *pvParameters);

static QueueHandle_t s_comm_uart_queue = NULL;

void comm_uart_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    /* Install UART driver, and get the queue */
    uart_driver_install(COMM_UART_NUM, COMM_UART_BUFF_SIZE, COMM_UART_BUFF_SIZE, COMM_UART_QUEUE_SIZE, &s_comm_uart_queue, 0);
    uart_param_config(COMM_UART_NUM, &uart_config);
    uart_set_pin(COMM_UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    /* Reset the pattern queue length to record at most 20 pattern positions */
    uart_pattern_queue_reset(COMM_UART_NUM, COMM_UART_QUEUE_SIZE);

    xTaskCreate(cmd_parse_task, "cmd_parse_task", 1024 * 4, NULL, COMM_UART_PARSE_TASK_PRIORITY, NULL);
}

int comm_uart_write_bytes(const void* src)
{
#ifdef COMM_OUTPUT_RESPONSE_FLAG
    ESP_LOGI(TAG, "%s", src);

    return uart_write_bytes(COMM_UART_NUM, src, strlen(src));
#else
    return 0;
#endif
}
