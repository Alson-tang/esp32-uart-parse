#include <string.h>
#include "esp_system.h"
#include "esp_log.h"

#include "FreeRTOS_CLI.h"

#include "cmd_uart.h"

BaseType_t prvParameterSwitchCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
/*     char *pcParam1 = NULL;
    char *pcParam2 = NULL;
    char *pcParam3 = NULL;
    char *pcParam4 = NULL;
    BaseType_t lParameterStringLength = 0;
    uint32_t u32Index = 0;

    pcParam1 = (char *)FreeRTOS_CLIGetParameter(pcCommandString, ++u32Index, &lParameterStringLength);
    configASSERT(pcParam1);
    printf("%d parameter is : %s, len : %d\r\n", u32Index, pcParam1, lParameterStringLength);

    pcParam2 = (char *)FreeRTOS_CLIGetParameter(pcCommandString, ++u32Index, &lParameterStringLength);
    configASSERT(pcParam2);
    printf("%d parameter is : %s, len : %d\r\n", u32Index, pcParam2, lParameterStringLength);

    pcParam3 = (char *)FreeRTOS_CLIGetParameter(pcCommandString, ++u32Index, &lParameterStringLength);
    if (pcParam3 != NULL) {
        printf("%d parameter is : %s, len : %d\r\n", u32Index, pcParam3, lParameterStringLength);
    }

    pcParam4 = (char *)FreeRTOS_CLIGetParameter(pcCommandString, ++u32Index, &lParameterStringLength);
    if (pcParam4 != NULL) {
        printf("%d parameter is : %s, len : %d\r\n", u32Index, pcParam4, lParameterStringLength);
    }

    return pdFALSE; */

    char *pcParameter;
    BaseType_t lParameterStringLength, xReturn;

    /* Note that the use of the static parameter means this function is not reentrant. */
    static BaseType_t lParameterNumber = 0;

    if( lParameterNumber == 0 )
    {
        /* lParameterNumber is 0, so this is the first time the function has been
        called since the command was entered.  Return the string "The parameters
        were:" before returning any parameter strings. */
        sprintf( pcWriteBuffer, "The parameters were:\r\n" );

        /* Next time the function is called the first parameter will be echoed
        back. */
        lParameterNumber = 1L;

        /* There is more data to be returned as no parameters have been echoed
        back yet, so set xReturn to pdPASS so the function will be called again. */
        xReturn = pdPASS;
    }
    else
    {
        /* lParameter is not 0, so holds the number of the parameter that should
        be returned.  Obtain the complete parameter string. */
        pcParameter = ( char * ) FreeRTOS_CLIGetParameter
                                    (
                                        /* The command string itself. */
                                        pcCommandString,
                                        /* Return the next parameter. */
                                        lParameterNumber,
                                        /* Store the parameter string length. */
                                        &lParameterStringLength
                                    );

        if( pcParameter != NULL )
        {
            /* There was another parameter to return.  Copy it into pcWriteBuffer.
            in the format "[number]: [Parameter String". */
            memset( pcWriteBuffer, 0x00, xWriteBufferLen );
            sprintf( pcWriteBuffer, "%d: ", lParameterNumber );
            strncat( pcWriteBuffer, pcParameter, lParameterStringLength );
            printf("%s\r\n", pcWriteBuffer);

            /* There might be more parameters to return after this one, so again
            set xReturn to pdTRUE. */
            xReturn = pdTRUE;
            lParameterNumber++;
        }
        else
        {
            /* No more parameters were found.  Make sure the write buffer does
            not contain a valid string to prevent junk being printed out. */
            pcWriteBuffer[ 0 ] = 0x00;

            /* There is no more data to return, so this time set xReturn to
            pdFALSE. */
            xReturn = pdFALSE;

            /* Start over the next time this command is executed. */
            lParameterNumber = 0;
        }
    }

    return xReturn;
}

static const CLI_Command_Definition_t s_cmd[] = {
      {
        "test",
        "test <param_1>, <param_2>[, <param_3>, <param_4>] ",
        prvParameterSwitchCommand,
        -1
    },
};

void cmd_register(void)
{
    for (uint32_t i = 0; i < (sizeof(s_cmd) / sizeof(s_cmd[0])); i++) {
        FreeRTOS_CLIRegisterCommand(&s_cmd[i]);
    }
}
