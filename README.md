## Custom Bootloader for STM32L0

Learning resource: [YouTube - LowByte Productions](https://www.youtube.com/watch?v=06ICtJjPKlA&list=PLP29wDx6QmW7HaCrRydOnxcy8QmW0SNdQ&index=2)

Here, the main app is inside ./blinky_vsc and it uses ./bootloader/src/firmware.bin as the bootloader code in the beginning.

**Note: Since libopencm3 is used as submodules in each directory and changes were made to them locally, just cloning this repo might not work.**
