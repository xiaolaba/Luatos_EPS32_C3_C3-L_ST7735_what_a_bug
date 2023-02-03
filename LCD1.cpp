

#include "lcd1.h"

#define LCD_SCLK_Clr() digitalWrite(SCL, LOW); //SCL=SCLK
#define LCD_SCLK_Set() digitalWrite(SCL, HIGH);

#define LCD_MOSI_Clr() digitalWrite(SDA, LOW);//SDA=MOSI
#define LCD_MOSI_Set() digitalWrite(SDA, HIGH);

#define LCD_RES_Clr()  digitalWrite(RES, LOW);//RES
#define LCD_RES_Set()  digitalWrite(RES, HIGH);

#define LCD_DC_Clr()   digitalWrite(DC, LOW);//DC
#define LCD_DC_Set()   digitalWrite(DC, HIGH);
          
#define LCD_CS_Clr()   digitalWrite(CS, LOW);//CS
#define LCD_CS_Set()   digitalWrite(CS, HIGH);

#define LCD_BLK_Clr()  digitalWrite(BL, LOW);//BLK
#define LCD_BLK_Set()  digitalWrite(BL, HIGH);


void LCD_Writ_Bus(u8 dat) 
{  
  u8 i;
  LCD_CS_Clr();
  for(i=0;i<8;i++)
  {       
    LCD_SCLK_Clr();
    if(dat&0x80)
    {
       LCD_MOSI_Set();
    }
    else
    {
       LCD_MOSI_Clr();
    }
    LCD_SCLK_Set();
    dat<<=1;
  } 
  LCD_CS_Set(); 
}

void LCD_WR_DATA8(u8 dat)
{
  LCD_Writ_Bus(dat);
}

void LCD_WR_DATA(u16 dat)
{
  LCD_Writ_Bus(dat>>8);
  LCD_Writ_Bus(dat);
}

void LCD_WR_REG(u8 dat)
{
  LCD_DC_Clr();
  LCD_Writ_Bus(dat);
  LCD_DC_Set();
}

void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
  if(USE_HORIZONTAL==0)
  {
    LCD_WR_REG(0x2a);
    LCD_WR_DATA(x1+2);
    LCD_WR_DATA(x2+2);
    LCD_WR_REG(0x2b);
    LCD_WR_DATA(y1+1);
    LCD_WR_DATA(y2+1);
    LCD_WR_REG(0x2c);
  }
  else if(USE_HORIZONTAL==1)
  {
    LCD_WR_REG(0x2a);
    LCD_WR_DATA(x1+2);
    LCD_WR_DATA(x2+2);
    LCD_WR_REG(0x2b);
    LCD_WR_DATA(y1+1);
    LCD_WR_DATA(y2+1);
    LCD_WR_REG(0x2c);
  }
  else if(USE_HORIZONTAL==2)
  {
    LCD_WR_REG(0x2a);
    LCD_WR_DATA(x1+1);
    LCD_WR_DATA(x2+1);
    LCD_WR_REG(0x2b);
    LCD_WR_DATA(y1+2);
    LCD_WR_DATA(y2+2);
    LCD_WR_REG(0x2c);
  }
  else
  {
    LCD_WR_REG(0x2a);
    LCD_WR_DATA(x1+1);
    LCD_WR_DATA(x2+1);
    LCD_WR_REG(0x2b);
    LCD_WR_DATA(y1+2);
    LCD_WR_DATA(y2+2);
    LCD_WR_REG(0x2c);
  }
}

void LCD_GPIO_Init() 
{
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(RES, OUTPUT);
  pinMode(BL, OUTPUT);
}

void LCD_Init(void)
{
  LCD_GPIO_Init();
  
  LCD_RES_Clr();
  delay(100);
  LCD_RES_Set();
  delay(100);
  
  LCD_BLK_Set();
  delay(100);
  
  //************* Start Initial Sequence **********//
  LCD_WR_REG(0x11); //Sleep out 
  delay(120);              //Delay 120ms 
  //------------------------------------ST7735S Frame Rate-----------------------------------------// 
  LCD_WR_REG(0xB1); 
  LCD_WR_DATA8(0x05); 
  LCD_WR_DATA8(0x3C); 
  LCD_WR_DATA8(0x3C); 
  LCD_WR_REG(0xB2); 
  LCD_WR_DATA8(0x05);
  LCD_WR_DATA8(0x3C); 
  LCD_WR_DATA8(0x3C); 
  LCD_WR_REG(0xB3); 
  LCD_WR_DATA8(0x05); 
  LCD_WR_DATA8(0x3C); 
  LCD_WR_DATA8(0x3C); 
  LCD_WR_DATA8(0x05); 
  LCD_WR_DATA8(0x3C); 
  LCD_WR_DATA8(0x3C); 
  //------------------------------------End ST7735S Frame Rate---------------------------------// 
  LCD_WR_REG(0xB4); //Dot inversion 
  LCD_WR_DATA8(0x03); 
  //------------------------------------ST7735S Power Sequence---------------------------------// 
  LCD_WR_REG(0xC0); 
  LCD_WR_DATA8(0x28); 
  LCD_WR_DATA8(0x08); 
  LCD_WR_DATA8(0x04); 
  LCD_WR_REG(0xC1); 
  LCD_WR_DATA8(0XC0); 
  LCD_WR_REG(0xC2); 
  LCD_WR_DATA8(0x0D); 
  LCD_WR_DATA8(0x00); 
  LCD_WR_REG(0xC3); 
  LCD_WR_DATA8(0x8D); 
  LCD_WR_DATA8(0x2A); 
  LCD_WR_REG(0xC4); 
  LCD_WR_DATA8(0x8D); 
  LCD_WR_DATA8(0xEE); 
  //---------------------------------End ST7735S Power Sequence-------------------------------------// 
  LCD_WR_REG(0xC5); //VCOM 
  LCD_WR_DATA8(0x1A); 
  LCD_WR_REG(0x36); //MX, MY, RGB mode 
  if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
  else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
  else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
  else LCD_WR_DATA8(0xA0); 
  //------------------------------------ST7735S Gamma Sequence---------------------------------// 
  LCD_WR_REG(0xE0); 
  LCD_WR_DATA8(0x04); 
  LCD_WR_DATA8(0x22); 
  LCD_WR_DATA8(0x07); 
  LCD_WR_DATA8(0x0A); 
  LCD_WR_DATA8(0x2E); 
  LCD_WR_DATA8(0x30); 
  LCD_WR_DATA8(0x25); 
  LCD_WR_DATA8(0x2A); 
  LCD_WR_DATA8(0x28); 
  LCD_WR_DATA8(0x26); 
  LCD_WR_DATA8(0x2E); 
  LCD_WR_DATA8(0x3A); 
  LCD_WR_DATA8(0x00); 
  LCD_WR_DATA8(0x01); 
  LCD_WR_DATA8(0x03); 
  LCD_WR_DATA8(0x13); 
  LCD_WR_REG(0xE1); 
  LCD_WR_DATA8(0x04); 
  LCD_WR_DATA8(0x16); 
  LCD_WR_DATA8(0x06); 
  LCD_WR_DATA8(0x0D); 
  LCD_WR_DATA8(0x2D); 
  LCD_WR_DATA8(0x26); 
  LCD_WR_DATA8(0x23); 
  LCD_WR_DATA8(0x27); 
  LCD_WR_DATA8(0x27); 
  LCD_WR_DATA8(0x25); 
  LCD_WR_DATA8(0x2D); 
  LCD_WR_DATA8(0x3B); 
  LCD_WR_DATA8(0x00); 
  LCD_WR_DATA8(0x01); 
  LCD_WR_DATA8(0x04); 
  LCD_WR_DATA8(0x13); 
  //------------------------------------End ST7735S Gamma Sequence-----------------------------// 
  LCD_WR_REG(0x3A); //65k mode 
  LCD_WR_DATA8(0x05); 
  LCD_WR_REG(0x29); //Display on 
} 

void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
  u16 i,j; 
  LCD_Address_Set(xsta,ysta,xend-1,yend-1);
  for(i=ysta;i<yend;i++)
  {                               
    for(j=xsta;j<xend;j++)
    {
      LCD_WR_DATA(color);
    }
  }                   
}


void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
  LCD_Address_Set(x,y,x,y);//ÉèÖÃ¹â±êÎ»ÖÃ 
  LCD_WR_DATA(color);
} 

//显示单个字母
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 MOD)
{
  u8 temp,sizex,t;
  u16 i,TypefaceNum;
  u16 x0=x;
  sizex=sizey/2;
  TypefaceNum=sizex/8*sizey;
  num=num-' '; 
  LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);
  for(i=0;i<TypefaceNum;i++)
  { 
    if(sizey==16)temp=ascii_1608[num][i];
    else if(sizey==32)temp=ascii_3216[num][i];
    else return;
    for(t=0;t<8;t++)
    {
      if(!MOD)
      {
        if(temp&(0x01<<t))LCD_WR_DATA(fc);
        else LCD_WR_DATA(bc);
      }
      else
      {
        if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);
        x++;
        if((x-x0)==sizex)
        {
          x=x0;
          y++;
          break;
        }
      }
    }
  }         
}
//显示字符串
void LCD_ShowString(u16 x,u16 y,char *p,u16 fc,u16 bc,u8 sizey,u8 MOD)
{         
  while(*p!='\0')
  {       
    LCD_ShowChar(x,y,*p,fc,bc,sizey,MOD);
    x+=sizey/2;
    p++;
  }  
}
//显示数字
u32 mypow(u8 m,u8 n)
{
  u32 result=1;  
  while(n--)result*=m;
  return result;
}


//显示整数变量
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{           
  u8 t,temp;
  u8 enshow=0;
  u8 sizex=sizey/2;
  for(t=0;t<len;t++)
  {
    temp=(num/mypow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
        continue;
      }else enshow=1; 
       
    }
    LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
  }
} 
//显示两位小数
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{           
  u8 t,temp,sizex;
  u16 num1;
  sizex=sizey/2;
  num1=num*100;
  for(t=0;t<len;t++)
  {
    temp=(num1/mypow(10,len-t-1))%10;
    if(t==(len-2))
    {
      LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
      t++;
      len+=1;
    }
    LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
  }
}
