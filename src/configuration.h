/*

TTGO T-BEAM Tracker for The Things Network

Copyright (C) 2018 by Xose Pérez <xose dot perez at gmail dot com>

This code requires LMIC library by Matthijs Kooijman
https://github.com/matthijskooijman/arduino-lmic

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#pragma once

#include <Arduino.h>
// -----------------------------------------------------------------------------
// Version
// -----------------------------------------------------------------------------

// If app version is not specified we assume we are not being invoked by the build script
#ifndef APP_VERSION
#error APP_VERSION, HW_VERSION, and HW_VERSION_countryname must be set by the build environment
//#define APP_VERSION 0.0.0   // this def normally comes from build-all.sh
//#define HW_VERSION 1.0 - US // normally comes from build-all.sh and contains the region code
#endif

// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------

// If we are using the JTAG port for debugging, some pins must be left free for that (and things like GPS have to be disabled)
// we don't support jtag on the ttgo - access to gpio 12 is a PITA
#ifdef ARDUINO_HELTEC_WIFI_LORA_32_V2
//#define USE_JTAG
#endif

#define REQUIRE_RADIO true // If true, we will fail to start if the radio is not found

/// Convert a preprocessor name into a quoted string
#define xstr(s) str(s)
#define str(s) #s

/// Convert a preprocessor name into a quoted string and if that string is empty use "unset"
#define optstr(s) (xstr(s)[0] ? xstr(s) : "unset")

#ifdef NRF52840_XXAA // All of the NRF52 targets are configured using variant.h, so this section shouldn't need to be
// board specific

//
// Standard definitions for NRF52 targets
//

#define NO_ESP32 // Don't use ESP32 libs (mainly bluetooth)

// We bind to the GPS using variant.h instead for this platform (Serial1)

// FIXME, not yet ready for NRF52
#define RTC_DATA_ATTR

#define LED_PIN PIN_LED1 // LED1 on nrf52840-DK
#define BUTTON_PIN PIN_BUTTON1

// FIXME, use variant.h defs for all of this!!! (even on the ESP32 targets)
#else

//
// Standard definitions for ESP32 targets
//

#define GPS_SERIAL_NUM 1
#define GPS_RX_PIN 34
#ifdef USE_JTAG
#define GPS_TX_PIN -1
#else
#define GPS_TX_PIN 12
#endif

// -----------------------------------------------------------------------------
// LoRa SPI
// -----------------------------------------------------------------------------

#define SCK_GPIO 5
#define MISO_GPIO 19
#define MOSI_GPIO 27
#define NSS_GPIO 18

#endif

// -----------------------------------------------------------------------------
// OLED
// -----------------------------------------------------------------------------

#define SSD1306_ADDRESS 0x3C

// Flip the screen upside down by default as it makes more sense on T-BEAM
// devices. Comment this out to not rotate screen 180 degrees.
#define FLIP_SCREEN_VERTICALLY

// DEBUG LED
#define LED_INVERTED 0 // define as 1 if LED is active low (on)

// -----------------------------------------------------------------------------
// GPS
// -----------------------------------------------------------------------------

#define GPS_BAUDRATE 9600

#if defined(TBEAM_V10)
// This string must exactly match the case used in release file names or the android updater won't work
#define HW_VENDOR "tbeam"

// #define BUTTON_NEED_PULLUP // if set we need to turn on the internal CPU pullup during sleep

#define I2C_SDA 21
#define I2C_SCL 22

#define BUTTON_PIN 38

#ifndef USE_JTAG
#define RESET_GPIO 14
#endif
#define RF95_IRQ_GPIO 26
#define DIO1_GPIO 33 // Note: not really used on this board
#define DIO2_GPIO 32 // Note: not really used on this board

// Leave undefined to disable our PMU IRQ handler
#define PMU_IRQ 35

#define AXP192_SLAVE_ADDRESS 0x34

#elif defined(TBEAM_V07)
// This string must exactly match the case used in release file names or the android updater won't work
#define HW_VENDOR "tbeam0.7"

// #define BUTTON_NEED_PULLUP // if set we need to turn on the internal CPU pullup during sleep

#define I2C_SDA 21
#define I2C_SCL 22

#define BUTTON_PIN 39

#ifndef USE_JTAG
#define RESET_GPIO 23
#endif
#define RF95_IRQ_GPIO 26
#define DIO1_GPIO 33 // Note: not really used on this board
#define DIO2_GPIO 32 // Note: not really used on this board

// This board has different GPS pins than all other boards
#undef GPS_RX_PIN
#undef GPS_TX_PIN
#define GPS_RX_PIN 12
#define GPS_TX_PIN 15

#elif defined(ARDUINO_HELTEC_WIFI_LORA_32_V2)
// This string must exactly match the case used in release file names or the android updater won't work
#define HW_VENDOR "heltec"

#ifndef USE_JTAG  // gpio15 is TDO for JTAG, so no I2C on this board while doing jtag
#define I2C_SDA 4 // I2C pins for this board
#define I2C_SCL 15
#endif

#define RESET_OLED 16 // If defined, this pin will be used to reset the display controller

#define VEXT_ENABLE 21 // active low, powers the oled display and the lora antenna boost
#define LED_PIN 25     // If defined we will blink this LED
#define BUTTON_PIN 0   // If defined, this will be used for user button presses

#ifndef USE_JTAG
#define RESET_GPIO 14 // If defined, this pin will be used to reset the LORA radio
#endif
#define RF95_IRQ_GPIO 26
#define DIO1_GPIO 35 // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#define DIO2_GPIO 34 // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#elif defined(TTGO_LORA_V1)
// This string must exactly match the case used in release file names or the android updater won't work
#define HW_VENDOR "ttgo-lora32-v1"

#define I2C_SDA 4 // I2C pins for this board
#define I2C_SCL 15

#define RESET_OLED 16 // If defined, this pin will be used to reset the display controller

// #define VEXT_ENABLE 21 // active low, powers the oled display and the lora antenna boost
#define LED_PIN 2     // If defined we will blink this LED
#define BUTTON_PIN 0  // If defined, this will be used for user button presses

#define RESET_GPIO 14    // If defined, this pin will be used to reset the LORA radio
#define RF95_IRQ_GPIO 26 // IRQ line for the LORA radio
#define DIO1_GPIO 35     // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#define DIO2_GPIO 34     // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#elif defined(TTGO_LORA_V2)
// This string must exactly match the case used in release file names or the android updater won't work
#define HW_VENDOR "ttgo-lora32-v2"

#define I2C_SDA 21 // I2C pins for this board
#define I2C_SCL 22

#define RESET_OLED 16 // If defined, this pin will be used to reset the display controller

#define VEXT_ENABLE 21 // active low, powers the oled display and the lora antenna boost
#define LED_PIN 25     // If defined we will blink this LED
#define BUTTON_PIN                                                                                                               \
    0 // If defined, this will be used for user button presses, if your board doesn't have a physical switch, you can wire one
// between this pin and ground

#define RESET_GPIO 14    // If defined, this pin will be used to reset the LORA radio
#define RF95_IRQ_GPIO 26 // IRQ line for the LORA radio
#define DIO1_GPIO 35     // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#define DIO2_GPIO 34     // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number

#elif defined(TTGO_TWATCH_BASE)

#define HW_VENDOR "ttgo-twatch-base"

#define RESET_GPIO      25      // If defined, this pin will be used to reset the LORA radio
#define RF95_IRQ_GPIO   26      // IRQ line for the LORA radio
#define DIO1_GPIO       38      // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#define DIO2_GPIO       39      // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number

#undef  SCK_GPIO
#undef  MISO_GPIO
#undef  MOSI_GPIO
#undef  NSS_GPIO

#define SCK_GPIO        14
#define MISO_GPIO       2
#define MOSI_GPIO       15
#define NSS_GPIO        13

#define BUTTON_PIN      36
#endif

#ifdef ARDUINO_NRF52840_PCA10056

// This string must exactly match the case used in release file names or the android updater won't work
#define HW_VENDOR "nrf52dk"

// This board uses 0 to be mean LED on
#undef LED_INVERTED
#define LED_INVERTED 1

// Uncomment to confirm if we can build the RF95 driver for NRF52
#if 0
#define RESET_GPIO 14    // If defined, this pin will be used to reset the LORA radio
#define RF95_IRQ_GPIO 26 // IRQ line for the LORA radio
#define DIO1_GPIO 35     // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#define DIO2_GPIO 34     // DIO1 & DIO2 are not currently used, but they must be assigned to a pin number
#endif

#elif defined(ARDUINO_NRF52840_PPR)

#define HW_VENDOR "ppr"

#endif

// -----------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------

#define SERIAL_BAUD 921600 // Serial debug baud rate

#include "SerialConsole.h"

#define DEBUG_PORT console // Serial debug port

#ifdef NO_ESP32
#define USE_SEGGER
#endif
#ifdef USE_SEGGER
#include "SEGGER_RTT.h"
#define DEBUG_MSG(...) SEGGER_RTT_printf(0, __VA_ARGS__)
#else
#ifdef DEBUG_PORT
#define DEBUG_MSG(...) DEBUG_PORT.printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif
#endif

// -----------------------------------------------------------------------------
// AXP192 (Rev1-specific options)
// -----------------------------------------------------------------------------

#define GPS_POWER_CTRL_CH 3
#define LORA_POWER_CTRL_CH 2
