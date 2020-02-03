# smoc
SMOC project

## Building Accelerometer

- Import the `accelerometer` project into STM32CubeIDE. If asked, update it.
- Debug `accelerometer.elf` as STM32 Application.
- Run the code by clicking on `play` button.

## Building game server

- Import the `game_server` project into STM32CubeIDE. If asked, update it.
- Debug `game_server.elf` as STM32 Application.
- Run the code by clicking on `play` button.

## Connect accelerometer and server

- Accelerometer is sending through USART2. Make sure it is correctly set up in STM32CubeMX.
- Server is receiving through USART3. Make sure it is correctly set up in STM32CubeMX.
- Connect **PA2** (USART2_TX) on accelerometer to **PD9** (USART3_RX) on server.
- Connect both accelerometer and server GND.