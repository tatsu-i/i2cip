#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <wiringPi.h>


#define LCD_ADDRESS (0b0111110)
#define LCD_CONTRAST 100

#define LCD_RS_CMD (0x00)
#define LCD_RS_DATA (0x40)
#define LCD_CMD_CLEAR (0x01)
#define LCD_CMD_HOME (0x03)

// 関数プロトタイプ宣言。
void LCD_init(int fd);
void LCD_write(unsigned char rs, unsigned char data, int fd);
void LCD_clear(int fd);
void LCD_setCursor(unsigned char col, unsigned char row, int fd);
void LCD_putc(unsigned char c, int fd);
void LCD_puts(char *str, int fd);

int main(int argc, char **argv)
{
 int lcd;       // ファイルディスクリプタ。
 char *i2cFileName = "/dev/i2c-1"; // I2Cドライバファイル名。
 int lcdAddress = LCD_ADDRESS;  // I2C LCD のアドレス。
 if (argc < 2)return 0;
 
 // I2CポートをRead/Write属性でオープン。
 if ((lcd = open(i2cFileName, O_RDWR)) < 0)
 {
  printf("Faild to open i2c port\n");
  exit(1);
 }
 
 // 通信先アドレスの設定。
 if (ioctl(lcd, I2C_SLAVE, lcdAddress) < 0)
 {
  printf("Unable to get bus access to talk to slave\n");
  exit(1);
 }
 
 delay(100);

 // LCD初期化。
 LCD_init(lcd);
 
 // メッセージ表示。
    LCD_setCursor(0, 0, lcd);
    LCD_puts(argv[1], lcd);
    LCD_setCursor(0, 1, lcd);
    LCD_puts(argv[2], lcd);
 
 return 0;
}

void LCD_init(int fd)
{
 delay(40);
 // Function Set。8bit bus mode, 2-line mode,normal font,normal instruction mode。
    LCD_write(LCD_RS_CMD, 0b00111000, fd);
    // Function Set。extension instruction modeへ。
    LCD_write(LCD_RS_CMD, 0b00111001, fd);
    // Internal OSC frequency(extension instruction mode)設定。
    LCD_write(LCD_RS_CMD, 0b00010100, fd);
    // Contrast set(extension instruction mode)。コントラスト値下位4bit設定。
    LCD_write(LCD_RS_CMD, 0b01110000 | (LCD_CONTRAST & 0xF), fd);
    // Power/ICON/Contrast set(extension instruction mode)。
    // アイコン On,booster On,コントラスト値上位2bit設定。
    LCD_write(LCD_RS_CMD, 0b01011100 | ((LCD_CONTRAST >> 4) & 0x3), fd);
    // Follower control。internal follower on, 
    LCD_write(LCD_RS_CMD, 0b01101100, fd);
    // 時間待ち。
    delay(300);
    
    // Function Set。normal instruction mode。
    LCD_write(LCD_RS_CMD, 0b00111000, fd);
    // Display On/Off。Display Onに設定。
    LCD_write(LCD_RS_CMD, 0b00001100, fd);
    // Clear Display。
    LCD_write(LCD_RS_CMD, 0b00001100, fd);
    // 時間待ち。
    delay(2);
}

void LCD_write(unsigned char rs, unsigned char data, int fd)
{
    unsigned char buf[2];
 
    if (rs == LCD_RS_CMD || rs == LCD_RS_DATA)
    {
        // LCD_RS_CMD ならコマンドモード。LCD_RS_DATA ならデータモード。
        
  buf[0] = rs;
  buf[1] = data;
  if (write(fd, buf, 2) != 2)
  {
   printf("Error writeing to i2c slave1\n");
  }        
    }
    else
    {
        // rsの指定がLCD_RS_CMD,LCD_RS_DATA以外ならなにもしない。
    }
}

void LCD_clear(int fd)
{
    LCD_write(LCD_RS_CMD, LCD_CMD_CLEAR, fd);
    delay(2);
    LCD_write(LCD_RS_CMD, LCD_CMD_HOME, fd);
    delay(2);
}

void LCD_setCursor(unsigned char col, unsigned char row, int fd)
{
    unsigned char offset[] = {0x00, 0x40};
    
    if (row > 1)    row = 1;
    if (col > 16)    col = 16;
    
    LCD_write(LCD_RS_CMD, 0x80 | (col + offset[row]), fd);
}

void LCD_putc(unsigned char c, int fd)
{
    LCD_write(LCD_RS_DATA, c, fd);
}

void LCD_puts(char *str, int fd)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        if (str[i] == 0x00)
        {
            break;
        }
        else
        {
            LCD_putc((unsigned int)str[i], fd);
        }
    }
}

