# Embedded DAP42 Debug Probe

This is the version of DAP42 used with SushiBits One version 7 and above.

## Introduction

DAP42 is a CMSIS-DAP compatible USB JTAG debug adapter for ARM Cortex-A and
Cortex-M processors, based on the [STM32F042K6][42K] microcontroller.

This project is inspired by [the original DAP42 project][DAP42]. There are some
additional features implemented on top of the original project:

*   Full JTAG support. This is useful in a daisy-chained JTAG scenario.
*	Built-in USB serial adapter for communication and ISP.
*	Control on the BOOT0 pin of the target chip for entering ISP.

## License and contact

This is open source hardware under [3-clause BSD license][3BSDL].

[42K]:   http://www.st.com/en/microcontrollers/stm32f042k6.html
[DAP42]: https://github.com/devanlai/dap42
[SBONE]: https://github.com/SushiBits/SushiBitsOne
[42F]:   http://www.st.com/en/microcontrollers/stm32f042f6.html
[3BSDL]: LICENSE.md
