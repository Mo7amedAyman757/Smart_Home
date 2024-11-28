/* 
 * File:   chr_lcd.c
 * Author: LEGION
 *
 * Created on September 23, 2024, 11:26 PM
 */

#include "chr_lcd.h"

static STD_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd, uint8 _command);
static STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static STD_ReturnType lcd_4bit_set_cusrsor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 col);
static STD_ReturnType lcd_8bit_set_cusrsor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 col);

/**
 * 
 * @param lcd
 * @return 
 */
STD_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd) {
    STD_ReturnType ret = E_NOK;
    uint8 l_counter = 0;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_initialization(&(lcd->lcd_rs));
        ret = gpio_pin_initialization(&(lcd->lcd_en));
        for (l_counter = 0; l_counter < 4; l_counter++) {
            ret = gpio_pin_initialization(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_DDRAM_START);
    }
    return ret;
}

STD_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bit(lcd, command >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, command);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bit(lcd, data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, data);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

STD_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 data) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = lcd_4bit_set_cusrsor(lcd, row, col);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}

STD_ReturnType lcd_4bit_send_char_string(const chr_lcd_4bit_t *lcd, uint8 *str) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOK;
    } else {
        while (*str) {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_4bit_send_char_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 *str) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOK;
    } else {
        ret = lcd_4bit_set_cusrsor(lcd, row, col);
        while (*str) {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 col, const uint8 chr[], uint8 mem_pos) {
    STD_ReturnType ret = E_NOK;
    uint8 l_counter;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
        for (l_counter = 0; l_counter <= 7; l_counter++) {
            lcd_4bit_send_char_data(lcd, chr[l_counter]);
        }
        lcd_4bit_send_char_data_pos(lcd, row, col, mem_pos);
    }
    return ret;
}

STD_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd) {
    STD_ReturnType ret = E_NOK;
    uint8 l_counter = 0;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_initialization(&(lcd->lcd_rs));
        ret = gpio_pin_initialization(&(lcd->lcd_en));
        for (l_counter = 0; l_counter < 8; l_counter++) {
            ret = gpio_pin_initialization(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_DDRAM_START);
    }
    return ret;
}

STD_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command) {
    STD_ReturnType ret = E_NOK;
    uint8 l_pin_counter = 0;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for (l_pin_counter = 0; l_pin_counter < 8; l_pin_counter++) {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (command >> l_pin_counter) & (uint8) 0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data) {
    STD_ReturnType ret = E_NOK;
    uint8 l_pin_counter = 0;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for (l_pin_counter = 0; l_pin_counter < 8; l_pin_counter++) {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (data >> l_pin_counter) & (uint8) 0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 col, uint8 data) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = lcd_8bit_set_cusrsor(lcd, row, col);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}

STD_ReturnType lcd_8bit_send_char_string(const chr_lcd_8bit_t *lcd, uint8 *str) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOK;
    } else {
        while (*str) {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_8bit_send_char_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 col, uint8 *str) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOK;
    } else {
        ret = lcd_8bit_set_cusrsor(lcd, row, col);
        while (*str) {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

STD_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 col, const uint8 chr[], uint8 mem_pos) {
    STD_ReturnType ret = E_NOK;
    uint8 l_counter;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
        for (l_counter = 0; l_counter <= 7; l_counter++) {
            lcd_8bit_send_char_data(lcd, chr[l_counter]);
        }
        lcd_8bit_send_char_data_pos(lcd, row, col, mem_pos);
    }
    return ret;
}

STD_ReturnType convert_byte_to_string(uint8 value, uint8 *str) {
    STD_ReturnType ret = E_NOK;
    uint8 temp[4] = {0};
    uint8 l_counter = 0;
    if (NULL == str) {
        ret = E_NOK;
    } else {
        memset(str, ' ', 3);
        sprintf((char *) temp, "%u", value);
        while (temp[l_counter] != '\0') {
            str[l_counter] = temp[l_counter];
            l_counter++;
        }
        str[l_counter] = '\0';
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType convert_short_to_string(uint16 value, uint8 *str) {
    STD_ReturnType ret = E_NOK;
    uint8 temp[6] = {0};
    uint8 l_counter = 0;
    if (NULL == str) {
        ret = E_NOK;
    } else {
        sprintf((char *) temp, "%u", value);
        while ((temp[l_counter] != '\0') && (l_counter < 5)) {
            str[l_counter] = temp[l_counter];
            l_counter++;
        }

        // Fill remaining space with spaces if needed
        while (l_counter < 5) {
            str[l_counter] = ' ';
            l_counter++;
        }

        str[l_counter] = '\0';
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType convert_int_to_string(uint32 value, uint8 *str) {
    STD_ReturnType ret = E_NOK;
    uint8 temp[11] = {0};
    uint8 l_counter = 0;
    if (NULL == str) {
        ret = E_NOK;
    } else {
        memset(str, ' ', 10);
        sprintf((char *) temp, "%lu", value);
        while (temp[l_counter] != '\0') {
            str[l_counter] = temp[l_counter];
            l_counter++;
        }
        str[l_counter] = '\0';
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd, uint8 _command) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_command >> 0) & (uint8) 0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (_command >> 1) & (uint8) 0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (_command >> 2) & (uint8) 0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (_command >> 3) & (uint8) 0x01);
    }
    return ret;
}

STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

STD_ReturnType lcd_4bit_set_cusrsor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 col) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        col--;
        switch (row) {
            case ROW1:
                ret = lcd_4bit_send_command(lcd, (0x80 + col));
                break;
            case ROW2:
                ret = lcd_4bit_send_command(lcd, (0xC0 + col));
                break;
        }
    }
    return ret;
}

STD_ReturnType lcd_8bit_set_cusrsor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 col) {
    STD_ReturnType ret = E_NOK;
    if (NULL == lcd) {
        ret = E_NOK;
    } else {
        col--;
        switch (row) {
            case ROW1:
                ret = lcd_8bit_send_command(lcd, (0x80 + col));
                break;
            case ROW2:
                ret = lcd_8bit_send_command(lcd, (0xC0 + col));
                break;
        }
    }
    return ret;
}
