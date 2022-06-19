/*
   LS7366.h - Library for using the LSI/CSI LS7366 quadrature encoder counter with serial interface
   Created by David Jabon
   License: GPL 3.0
  The count values that are returned are always unsigned longs (32 bit integers) .
*/

#pragma once

#include "Arduino.h"
#include <SPI.h>

/* MDR0 configuration data
   The configutation byte is formed by choosing one element from each group.
*/

// Count modes
constexpr auto NQUAD = 0x00;    // non-quadrature mode
constexpr auto QUADRX1 = 0x01;  // X1 quadrature mode
constexpr auto QUADRX2 = 0x02;  // X2 quadrature mode
constexpr auto QUADRX4 = 0x03;  // X4 quadrature mode

// Running modes
constexpr auto FREE_RUN = 0x00;
constexpr auto SINGE_CYCLE = 0x04;
constexpr auto RANGE_LIMIT = 0x08;
constexpr auto MODULO_N = 0x0C;

// Index modes
constexpr auto DISABLE_INDX = 0x00;  // index_disabled 
constexpr auto INDX_LOADC = 0x10;    // index_load_CNTR
constexpr auto INDX_RESETC = 0x20;   // index_rest_CNTR 
constexpr auto INDX_LOADO = 0x30;    // index_load_OL 

//
constexpr auto ASYNCH_INDX = 0x00;  // asynchronous index 
constexpr auto SYNCH_INDX = 0x40;   // synchronous index 

// Clock filter modes 
constexpr auto FILTER_1 = 0x00;  // filter clock frequncy division factor 1 
constexpr auto FILTER_2 = 0x80;  // filter clock frequncy division factor 2 


/* MDR1 configuration data
   The configutation byte is formed by choosing one element from each group.
*/

// Flag modes 
constexpr auto NO_FLAGS = 0x00;  // all flags disabled
constexpr auto IDX_FLAG = 0x10;  // Index flag 
constexpr auto CMP_FLAG = 0x20;  // Compare flag 
constexpr auto BW_FLAG = 0x40;   // Borrow flag 
constexpr auto CY_FLAG = 0x80;   // Carry flag

// Enable or disable counter  
constexpr auto EN_CNTR = 0x00;   // counting enabled 
constexpr auto DIS_CNTR = 0x04;  // counting disabled 
 
// 1 to 4 bytes data-width 
constexpr auto BYTE_4 = 0x00;  // four byte mode           
constexpr auto BYTE_3 = 0x01;  // three byte mode           
constexpr auto BYTE_2 = 0x02;  // two byte mode           
constexpr auto BYTE_1 = 0x03;  // one byte mode

// LS7366R op-code list
constexpr auto CLR_MDR0 = 0x08;
constexpr auto CLR_MDR1 = 0x10;
constexpr auto CLR_CNTR = 0x20;
constexpr auto CLR_STR = 0x30;
constexpr auto READ_MDR0 = 0x48;
constexpr auto READ_MDR1 = 0x50;
constexpr auto READ_CNTR = 0x60;
constexpr auto READ_OTR = 0x68;
constexpr auto READ_STR = 0x70;
constexpr auto WRITE_MDR1 = 0x90;
constexpr auto WRITE_MDR0 = 0x88;
constexpr auto WRITE_DTR = 0x98;
constexpr auto LOAD_CNTR = 0xE0;
constexpr auto LOAD_OTR = 0xE4;


class LS7366 {
 public:
  LS7366(byte CS_pin);
  void clear_mode_register_0();
  void clear_mode_register_1();
  void clear_counter();
  void clear_status_register();
  byte read_mode_register_0();
  byte read_mode_register_1();
  unsigned long read_counter();
  unsigned long read_OTR();
  byte read_status_register();
  void write_mode_register_0(byte val);
  void write_mode_register_1(byte val);
  void write_data_register(unsigned long val);
  void load_counter();
  void load_OTR();

 private:
  byte CS_pin;
  byte datawidth;
  long left_extend_MSB(long val);
};
