#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vga_color { // text mode color constants
    VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) // fg - foreground | bg - gackground
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) // gets "string's" length
{
	size_t len = 0;
	while (str[len])
	{
		len++;
	}
	return len;
}

static const size_t VGA_WIDTH = 80;  	// number of characters vertically
static const size_t VGA_HEIGHT = 25; 	// number of characters horizontally 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n') 
	{	
		terminal_newline();
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH)
	{
		terminal_column = 0; // goes to the first column if we already used the last one

		if (++terminal_row == VGA_HEIGHT) terminal_row = 0; // goes to the first row when the first last one was used
	}
}

void terminal_writestring(const char* str)
{
	size_t size = strlen(str);
	for (size_t i = 0; i < size; i++) terminal_putchar(str[i]);
}

void terminal_info_color(bool b)
{
	if (b) terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
	else terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void terminal_newline()
{
	terminal_row = terminal_row + 1;
	terminal_column = 0;
}

void kernel_main(void)
{
	terminal_initialize(); // initializes the terminal interface

	terminal_writestring("Welcome to IT-OS 0.0.1\n");
	/*
	terminal_info_color(true);
	terminal_writestring("This is a deveopler version, not and official release.\n");
	terminal_info_color(false);
	*/
}