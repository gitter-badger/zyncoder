/*
 * ******************************************************************
 * ZYNTHIAN PROJECT: Zyncoder Library
 * 
 * Library for interfacing Rotary Encoders & Switches connected 
 * to RBPi native GPIOs or expanded with MCP23008. Includes an 
 * emulator mode to ease developping.
 * 
 * Copyright (C) 2015-2016 Fernando Moyano <jofemodo@zynthian.org>
 *
 * ******************************************************************
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the LICENSE.txt file.
 * 
 * ******************************************************************
 */

//-----------------------------------------------------------------------------
// Library Initialization
//-----------------------------------------------------------------------------

int init_zyncoder(int osc_port);
int end_zyncoder();

//-----------------------------------------------------------------------------
// MIDI Send
//-----------------------------------------------------------------------------

int zynmidi_set_control(unsigned char chan, unsigned char ctrl, unsigned char val);
int zynmidi_set_program(unsigned char chan, unsigned char pgrm);

//-----------------------------------------------------------------------------
// GPIO Switches
//-----------------------------------------------------------------------------

// The real limit in RPi2 is 17
#define max_zynswitches 8

struct zynswitch_st
{
	unsigned int enabled;
	unsigned int pin;
	volatile double tsus;
	volatile unsigned int dtus;
	volatile unsigned int status;
};
struct zynswitch_st zynswitches[max_zynswitches];

struct zynswitch_st *setup_zynswitch(unsigned int i, unsigned int pin); 
unsigned int get_zynswitch(unsigned int i);
unsigned int get_zynswitch_dtus(unsigned int i);

//-----------------------------------------------------------------------------
// MIDI Rotary Encoders
//-----------------------------------------------------------------------------

// 17 pins / 2 pins per encoder = 8 maximum encoders
#define max_zyncoders 8

struct zyncoder_st
{
	unsigned int enabled;
	unsigned int pin_a;
	unsigned int pin_b;
	unsigned int midi_chan;
	unsigned int midi_ctrl;
	char osc_path[512];
	unsigned int max_value;
	unsigned int step;
	volatile unsigned int value;
	volatile unsigned int last_encoded;
};
struct zyncoder_st zyncoders[max_zyncoders];

struct zyncoder_st *setup_zyncoder(unsigned int i, unsigned int pin_a, unsigned int pin_b, unsigned int midi_chan, unsigned int midi_ctrl, char *osc_path, unsigned int value, unsigned int max_value, unsigned int step); 
unsigned int get_value_zyncoder(unsigned int i);
void set_value_zyncoder(unsigned int i, unsigned int v);
