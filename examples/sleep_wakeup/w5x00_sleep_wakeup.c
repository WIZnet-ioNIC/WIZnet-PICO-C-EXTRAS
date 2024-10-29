/**
 * Copyright (c) 2021 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * ----------------------------------------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------------------------------------
 */
#include <stdio.h>

#include "port_common.h"

#include "wizchip_conf.h"
#include "w5x00_spi.h"

#include "pico/sleep.h"
/**
 * ----------------------------------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------------------------------
 */
/* Clock */
#define PLL_SYS_KHZ (133 * 1000)

/* Socket */
#define SOCKET_WOL 0

/* Port */
#define PORT_WOL 9000

#if DEVICE_BOARD_NAME == W55RP20_EVB_PICO
#define LED_PIN     19
#else
#define LED_PIN     25
#endif

/**
 * ----------------------------------------------------------------------------------------------------
 * Variables
 * ----------------------------------------------------------------------------------------------------
 */
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


/**
 * ----------------------------------------------------------------------------------------------------
 * Functions
 * ----------------------------------------------------------------------------------------------------
 */
/* Clock */
static void set_clock_khz(void);

void gpio_callback(uint gpio, uint32_t events);
void sleep_goto_sleep_until_gpio(uint gpio_pin, bool edge, bool high);

/**
 * ----------------------------------------------------------------------------------------------------
 * Main
 * ----------------------------------------------------------------------------------------------------
 */
int main()
{
    /* Initialize */
    int retval = 0;
    uint16_t len = 0;

    set_clock_khz();

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    wizchip_spi_initialize();
    wizchip_cris_initialize();

    wizchip_reset();
    wizchip_initialize();
    wizchip_check();

    network_initialize(g_net_info);

    /* Get network information */
    print_network_information(g_net_info);

    while(getSn_SR(0) != SOCK_CLOSED);

    socket(0, Sn_MR_UDP, PORT_WOL, 0);

#if _WIZCHIP_ == W5100S
    setIMR2(0x01);      // Open WOL magic pack interrupt
    setMR2(0x08); // Receive WOL packets
#elif _WIZCHIP_ == W5500
    setIMR(0x10);     // Open WOL magic pack interrupt
    setMR(0x20); // Receive WOL packets
#endif

    sleep_run_from_xosc();

    printf("Going to sleep until receive WOL Magic packet...\n");
    uart_default_tx_wait_blocking();

    sleep_goto_sleep_until_gpio(PIN_IRQ, false, true);

    while(1){
        printf("Wake up!\n");
        gpio_xor_mask(1<<LED_PIN);
        sleep_ms(500);
    }
}

/**
 * ----------------------------------------------------------------------------------------------------
 * Functions
 * ----------------------------------------------------------------------------------------------------
 */
/* Clock */
static void set_clock_khz(void)
{
    // set a system clock frequency in khz
    set_sys_clock_khz(PLL_SYS_KHZ, true);

    // configure the specified clock
    clock_configure(
        clk_peri,
        0,                                                // No glitchless mux
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, // System PLL on AUX mux
        PLL_SYS_KHZ * 1000,                               // Input frequency
        PLL_SYS_KHZ * 1000                                // Output (must be same as no divider)
    );
}

void gpio_callback(uint gpio, uint32_t events) {
    return;
}

void sleep_goto_sleep_until_gpio(uint gpio_pin, bool edge, bool high) {
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_IN);  

    gpio_set_irq_enabled_with_callback(
        gpio_pin,
        edge ? GPIO_IRQ_EDGE_RISE : GPIO_IRQ_EDGE_FALL,
        true,
        &gpio_callback
    );

    uint32_t save = scb_hw->scr;
    scb_hw->scr = save | M0PLUS_SCR_SLEEPDEEP_BITS;

    __wfi();  
}
