/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * HD44780 LCD display driver
 *
 * $Id: hd44780.h 2002 2009-06-25 20:21:16Z joerg_wunsch $
 */

/* CPU frequency */
#define F_CPU 16000000UL

/* HD44780 LCD port connections */
#define HD44780_RS D, 6
#define HD44780_RW D, 4
#define HD44780_E  D, 5
/* The data bits have to be not only in ascending order but also consecutive. */
#define HD44780_D4 D, 0

// Macros
#define GLUE(a, b)     a##b
/* single-bit macros, used for control bits */
#define SET_(what, p, m) GLUE(what, p) |= (1 << (m))
#define CLR_(what, p, m) GLUE(what, p) &= ~(1 << (m))
#define GET_(/* PIN, */ p, m) GLUE(PIN, p) & (1 << (m))
#define SET(what, x) SET_(what, x)
#define CLR(what, x) CLR_(what, x)
#define GET(/* PIN, */ x) GET_(x)

/* nibble macros, used for data path */
#define ASSIGN_(what, p, m, v) GLUE(what, p) = (GLUE(what, p) & \
~((1 << (m)) | (1 << ((m) + 1)) | \
(1 << ((m) + 2)) | (1 << ((m) + 3)))) | \
((v) << (m))
#define READ_(what, p, m) (GLUE(what, p) & ((1 << (m)) | (1 << ((m) + 1)) | \
(1 << ((m) + 2)) | (1 << ((m) + 3)))) >> (m)
#define ASSIGN(what, x, v) ASSIGN_(what, x, v)
#define READ(what, x) READ_(what, x)

/*
 * Send byte b to the LCD.  rs is the RS signal (register select), 0
 * selects instruction register, 1 selects the data register.
 */
void	hd44780_outbyte(uint8_t b, uint8_t rs);

/*
 * Initialize the LCD controller hardware.
 */
void	hd44780_init(void);

/* Send a command to the LCD controller. */
#define hd44780_outcmd(n)	hd44780_outbyte((n), 0)

/* Send a data byte to the LCD controller. */
#define hd44780_outdata(n)	hd44780_outbyte((n), 1)

/* Clear LCD display command. */
#define HD44780_CLR \
	0x01

/* Home cursor command. */
#define HD44780_HOME \
	0x02

/*
 * Select the entry mode.  inc determines whether the address counter
 * auto-increments, shift selects an automatic display shift.
 */
#define HD44780_ENTMODE(inc, shift) \
	(0x04 | ((inc)? 0x02: 0) | ((shift)? 1: 0))

/*
 * Selects disp[lay] on/off, cursor on/off, cursor blink[ing]
 * on/off.
 */
#define HD44780_DISPCTL(disp, cursor, blink) \
	(0x08 | ((disp)? 0x04: 0) | ((cursor)? 0x02: 0) | ((blink)? 1: 0))

/*
 * Function set.  if8bit selects an 8-bit data path, twoline arranges
 * for a two-line display, font5x10 selects the 5x10 dot font (5x8
 * dots if clear).
 */
#define HD44780_FNSET(if8bit, twoline, font5x10) \
	(0x20 | ((if8bit)? 0x10: 0) | ((twoline)? 0x08: 0) | \
		((font5x10)? 0x04: 0))

/*
 * Set the next character generator address to addr.
 */
#define HD44780_CGADDR(addr) \
	(0x40 | ((addr) & 0x3f))

/*
 * Set the next display address to addr.
 */
#define HD44780_DDADDR(addr) \
	(0x80 | ((addr) & 0x7f))

/*
 * Initialize LCD controller.  Performs a software reset.
 */
void lcd_init(void);

/*
 * Send one character to the LCD.
 */
int	lcd_putchar(char c);