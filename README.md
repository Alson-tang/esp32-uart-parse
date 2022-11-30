| Supported Targets | ESP32-S3 |
| ----------------- | -------- |

This is a RF test firmware project. The default communication UART port is ``UART0`` (Default UART baud rate is 115200, 8 data bits, 1 stop bit, no parity bit).

After the firmware is running, all operations can be performed by sending commands through the communication UART. Please end all commands with ``CR``.

**NOTE:**

* This example uses the [ESP32-C3 development board](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/hw-reference/esp32c3/user-guide-devkitm-1.html).

# How to use it

Follow detailed instructions provided specifically for this project. 

1. Select the instructions depending on Espressif chip installed on your development board:

    - [ESP32-C3 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/get-started/index.html)

    ESP-IDF v4.4 or above is recommended for this project. (The test ESP-IDF version of this project is [release/v4.4](https://github.com/espressif/esp-idf/tree/release/v4.4), commit id: ``39189e752230db6668b64481b03d2be5ad591a69``)

2. Remove the old configuration:

    ```
    rm -rf build sdkconfig
    ```

3. Project compilation:

    ```
    idf.py build
    ```

4. Download firmware based on script output or execute the following command:

    ```
    idf.py -p PORTNAME flash
    ```

    Replace ``PORTNAME`` with your port name.

# Folder contents

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).  

Below is short explanation of remaining files in the project folder.

```
├── components
│   ├── FreeRTOS-Plus-CLI
├── main
│   ├── include
│   ├── CMakeLists.txt
│   └── cmd_parse.c     This file is responsible for UART data parse
│   └── cmd_uart.c      This file is responsible for UART initialization
│   └── cmd.c           This file is the specific implementation of various commands
│   └── main.c          Main entrance
├── CMakeLists.txt
├── LICENSE
├── README.md           This is the file you are currently reading
└── sdkconfig.defaults
```

# Command test

You can enter the `test <param_1>, <param_2>[, <param_3>, <param_4>]` command through the serial port tool. This command has 2 required parameters and 2 parameters that can be omitted.

If you enter the following command：

```
test 1 12 123 1234
```

ESP32-C3 will output the following command responses:

```
1: 1
2: 12
3: 123
4: 1234
```

# License

This document and the attached source code are released as Free Software under ESPRESSIF MIT License. See the accompanying LICENSE file for a copy.
