# How to Test Dormant_Wakeup Example



## Step 1: Prepare software

The following serial terminal programs are required for Dormant_Wakeup example test, download and install from below links.

- [**Tera Term**][link-tera_term]
- [**Hercules**][link-hercules]
- [**WOL (magic packet)**][link-wol]


## Step 2: Prepare hardware

If you are using W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2, you can skip '1. Combine...'

1. Combine WIZnet Ethernet HAT with Raspberry Pi Pico.

2. Connect ethernet cable to WIZnet Ethernet HAT, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 ethernet port.

3. Connect Raspberry Pi Pico, W5100S-EVB-Pico or W5500-EVB-Pico to desktop or laptop using 5 pin micro USB cable. W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 require a USB Type-C cable.



## Step 3: Setup Dormant_Wakeup Example

To test the Dormant_Wakeup example, minor settings shall be done in code.

1. Setup SPI port and pin in 'w5x00_spi.h' in 'WIZnet-PICO-C-EXTRAS/port/ioLibrary_Driver/' directory.

Setup the SPI interface you use.
- If you use the W5100S-EVB-Pico, W5500-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2,

```cpp
/* SPI */
#define SPI_PORT spi0

#define PIN_SCK 18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS 17
#define PIN_RST 20
```

If you want to test with the Dormant_Wakeup example using SPI DMA, uncomment USE_SPI_DMA.

```cpp
/* Use SPI DMA */
//#define USE_SPI_DMA // if you want to use SPI DMA, uncomment.
```
- If you use the W55RP20-EVB-Pico,
```cpp
/* SPI */
#define USE_SPI_PIO

#define PIN_SCK 21
#define PIN_MOSI 23
#define PIN_MISO 22
#define PIN_CS 20
#define PIN_RST 25
```

2. Setup network configuration such as IP in 'w5x00_dormant_wakeup.c' which is the Dormant_wakeup example in 'WIZnet-PICO-C-EXTRAS/examples/dormant_wakeup/' directory.

Setup IP and other network settings to suit your network environment.

```cpp
/* Network */
static wiz_NetInfo g_net_info =
{
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 11, 2},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 11, 1},                     // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
        .dhcp = NETINFO_STATIC                       // DHCP enable/disable
};
```

3. Setup udp configuration in 'w5x00_dormant_wakeup.c' in 'WIZnet-PICO-C-EXTRAS/examples/dormant_wakeup/' directory.

```cpp
/* Port */
#define PORT_WOL 9000
```



## Step 4: Build

1. After completing the Dormant_Wakeup example configuration, click 'build' in the status bar at the bottom of Visual Studio Code or press the 'F7' button on the keyboard to build.

2. When the build is completed, 'w5x00_dormant_wakeup.uf2' is generated in 'WIZnet-PICO-C-EXTRAS/build/examples/dormant_wakeup/' directory.



## Step 5: Upload and Run

1. While pressing the BOOTSEL button of Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 power on the board, the USB mass storage 'RPI-RP2' is automatically mounted.

![][link-raspberry_pi_pico_usb_mass_storage]

2. Drag and drop 'w5x00_dormant_wakeup.uf2' onto the USB mass storage device 'RPI-RP2'.

3. Connect to the serial COM port of Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 with Tera Term.
Use USB-To-TTL module to connect serial with board.

![][link-uart_serial_pin_out]

![][link-connect_to_serial_com_port]

4. Reset your board.

5. If the Dormant_Wakeup example works normally on Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2, you can see the network information of Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 and go to dormant mode (User LED will not blinking).

![][link-see_network_information_of_raspberry_pi_pico_and_enter_dormant_mode]


6. Open WOL program to send WOL magic packet.
Add Module name and MAC Address in WOL program.

![][link-open_wol_program]

![][link-open_wol_program_and_add_module_information]


7. Click right button on mouse and Send WOL(magic packet).

![][link-send_wol_magic_packet]

8. You can see the Raspberry Pi Pico, W5100S-EVB-Pico, W5500-EVB-Pico, W55RP20-EVB-Pico, W5100S-EVB-Pico2 or W5500-EVB-Pico2 is wake up and running (User LED will blinking).

![][link-see_wakeup_of_raspberry_pi_pico]

&nbsp;&nbsp;For example, if you were using the W55RP20-EVB-Pico, the LEDs would blink as shown in the image below.

![][link-see_user_led_of_raspberry_pi_pico]



<!--
Link
-->

[link-tera_term]: https://osdn.net/projects/ttssh2/releases/
[link-hercules]: https://www.hw-group.com/software/hercules-setup-utility
[link-wol]: https://apps.microsoft.com/detail/9nblggh51pb3?hl=ko-KR&gl=KR
[link-raspberry_pi_pico_usb_mass_storage]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/raspberry_pi_pico_usb_mass_storage.png
[link-uart_serial_pin_out]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/uart_serial_pin_out_of_raspberry_pi_pico.png
[link-connect_to_serial_com_port]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/connect_to_serial_com_port.png
[link-see_network_information_of_raspberry_pi_pico_and_enter_dormant_mode]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/see_network_information_of_raspberry_pi_pico_and_enter_dormant_mode.png
[link-open_wol_program]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/open_wol_program.png
[link-open_wol_program_and_add_module_information]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/open_wol_program_and_add_module_information.png
[link-send_wol_magic_packet]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/send_wol_magic_packet.png
[link-see_wakeup_of_raspberry_pi_pico]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/see_wakeup_of_raspberry_pi_pico.png
[link-see_user_led_of_raspberry_pi_pico]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-C-EXTRAS/blob/main/static/images/dormant_wakeup/see_user_led_of_raspberry_pi_pico.png