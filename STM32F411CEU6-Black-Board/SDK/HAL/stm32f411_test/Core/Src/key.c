#include "key.h"

//代码来源网络 侵权联系删除
/*
 --------------------------------------------------------------------
|  short click                                                       |
|  ______                   ________                                 |
|     |  \                 /  |                                      |
|     |   \_______________/   |                                      |
|     |     |           |     |                                      |
|     |shake|  < long   |shake|                                      |
|                                                                    |
 -------------------------------------------------------------------
|  double click                                                      |
|  ______                   _____________                   ____     |
|     |  \                 /  |       |  \                 /  |      |
|     |   \_______________/   |       |   \_______________/   |      |
|     |     |           |     | < max |     |           |     |      |
|     |shake|  < long   |shake|dclick |shake|  any time |shake|      |
|                                                                    |
 --------------------------------------------------------------------
|  long click                                                        |
|  ______                                           ________         |
|     |  \                                         /  |              |
|     |   \_______________________________________/   |              |
|     |     |                                   |     |              |
|     |shake|             > long click          |shake|              |
|                                                                    |
 --------------------------------------------------------------------
   
*/
 
 
#define KEY_STATUS_DOWN_CHECK                0x00       
#define KEY_STATUS_DOWN_SHAKE                0x01
#define KEY_STATUS_DOWN_HANDLE               0x02
#define KEY_STATUS_LONG_CHECK                0x03
#define KEY_STATUS_SHORT_UP_SHAKE            0x04
#define KEY_STATUS_DOUBLE_CHECK              0x05
#define KEY_STATUS_SHORT_UP_HANDLE           0x06
#define KEY_STATUS_DOUBLE_DOWN_SHAKE         0x07
#define KEY_STATUS_DOUBLE_UP_CHECK           0x08
#define KEY_STATUS_DOUBLE_UP_SHAKE           0x09
#define KEY_STATUS_DOUBLE_UP_HANDLE          0x0a
#define KEY_STATUS_LONG_HANDLE               0x0b
#define KEY_STATUS_CONTINUE_CHECK            0x0c
#define KEY_STATUS_LONG_UP_SHAKE             0x0d
#define KEY_STATUS_LONG_UP_HANDLE            0x0e
 
 
#define KEY_READ_DOWN                        0x00  /* key is pressed          */
#define KEY_READ_UP                          0x01  /* Key isn't pressed       */ 
 
#define KEY_BUF_SIZE                         0x10  /* key value buffer size   */


struct
{
    unsigned short value[KEY_BUF_SIZE];
    unsigned char rd;
    unsigned char wr;
}key_buf;
 
 
struct key_dev
{
    unsigned char status;              /* state machine status                */
    unsigned char num;                 /* number                              */
    unsigned short count_ms;           /* ms counter                          */
    unsigned short long_click_ms;      /* long click check min time           */
    unsigned short shake_filter_ms;    /* shake filter time                   */
    unsigned short max_dclick_ms;      /* double click max interval time      */
    unsigned short continue_send_ms;   /* after long, continue send interval  */
    unsigned char (*read_key)(void);   /* key read pin status function pointer*/
};


/******************************************************************************
                           User Interface [START]
*******************************************************************************/
 
unsigned char key0_read(void)
{
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
    {
        return KEY_READ_DOWN;
    }
    else
    {
        return KEY_READ_UP;
    }
}
 
 
struct key_dev key_dev[] = {
    {
     KEY_STATUS_DOWN_CHECK,
     KEY0_NUM,
     0,
     1500,
     20,
     200,
     1000,
     (unsigned char (*)(void))key0_read,
    },
    /*
            .
            .
        user add other key 
            .
            .
    */
 
};


/******************************************************************************
                           User Interface [END]
*******************************************************************************/

static void key_write_value(unsigned short key_val);
static void key_status_down_check(struct key_dev *key_dev);
static void key_status_down_shake(struct key_dev *key_dev);
static void key_status_down_handle(struct key_dev *key_dev);
static void key_status_long_check(struct key_dev *key_dev);
static void key_status_short_up_shake(struct key_dev *key_dev);
static void key_status_double_check(struct key_dev *key_dev);
static void key_status_short_up_handle(struct key_dev *key_dev);
static void key_status_double_down_shake(struct key_dev *key_dev);
static void key_status_double_up_check(struct key_dev *key_dev);
static void key_status_double_up_shake(struct key_dev *key_dev);
static void key_status_double_up_handle(struct key_dev *key_dev);
static void key_status_long_hanle(struct key_dev *key_dev);
static void key_status_continue_check(struct key_dev *key_dev);
static void key_status_long_up_shake(struct key_dev *key_dev);
static void key_status_long_up_handle(struct key_dev *key_dev);
 
 
/**
description : write key vaule to buffer
param :  key_val - key value , (KEY_EVENT | KEY_NUMBER<<8) 
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_write_value(unsigned short key_val)
{   
    key_buf.value[key_buf.wr++] = key_val;
    key_buf.wr %= KEY_BUF_SIZE;
 
    /*
        overflow handle
    */
    if(key_buf.wr == key_buf.rd)
    {
        key_buf.rd++;
        key_buf.rd %= KEY_BUF_SIZE;
    }
}
 
/**
description : read key vaule from buffer
param : None
retval : key_val - key value , (KEY_EVENT | KEY_NUMBER<<8)
author : huohongpeng
data : 2017-03-02
*/
unsigned short key_read_value(void)
{
    unsigned short key_val;
 
    if(key_buf.wr == key_buf.rd)
    {
        key_val = KEY_EVENT_NULL;
    }
    else
    {
        key_val = key_buf.value[key_buf.rd++];
        key_buf.rd %= KEY_BUF_SIZE;
    }
 
    return key_val;
}
 
/**
description : check key whether press down
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_down_check(struct key_dev *key_dev)
{
    unsigned char key_read;
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_DOWN)
    {
        key_dev->status = KEY_STATUS_DOWN_SHAKE;
        key_dev->count_ms = 0;
    }
}
 
/**
description : filter shake after key pressed down
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_down_shake(struct key_dev *key_dev)
{
    unsigned char key_read;
 
    key_dev->count_ms++;
 
    if(key_dev->count_ms < key_dev->shake_filter_ms)
    {
        return;
    }
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_DOWN)
    {
        key_dev->status = KEY_STATUS_DOWN_HANDLE;
    }
    else
    {
        key_dev->status = KEY_STATUS_DOWN_CHECK;
    }
}
 
 
/**
description : key press down handle after pressed down filter shake  
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_down_handle(struct key_dev *key_dev)
{
    unsigned short key_val = key_dev->num<<8 | KEY_EVENT_DOWN;
    
    key_write_value(key_val);
 
    key_dev->status = KEY_STATUS_LONG_CHECK;
    key_dev->count_ms = 0;
 
}
 
/**
description : check key whether long click   
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_long_check(struct key_dev *key_dev)
{
    unsigned char key_read;
 
    key_dev->count_ms++;
    key_read = key_dev->read_key();
    
    if(key_dev->count_ms < key_dev->long_click_ms)
    {
        if(key_read == KEY_READ_UP)
        {
            key_dev->status = KEY_STATUS_SHORT_UP_SHAKE;                 
        }
 
        return;
    }
 
    key_dev->status = KEY_STATUS_LONG_HANDLE;            
    
}
 
/**
description : short cilck key up filter shake   
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_short_up_shake(struct key_dev *key_dev)
{
    unsigned char key_read;
    static unsigned short old = 0xffff;
 
    if(old == 0xffff)
    {
        old = key_dev->count_ms;
        key_dev->count_ms = 0;
    }
 
    key_dev->count_ms++;
 
    if(key_dev->count_ms < key_dev->shake_filter_ms)
    {
        return;
    }
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_UP)
    {
        key_dev->status = KEY_STATUS_DOUBLE_CHECK;
        key_dev->count_ms = 0;
    }
    else
    {
        key_dev->status = KEY_STATUS_LONG_CHECK;
        key_dev->count_ms += old;        
    }
 
    old = 0xffff;
}
 
/**
description : double cilck check. we consider double click event if key pressed 
              down when after short click up and within max double click interval
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_double_check(struct key_dev *key_dev)
{
    unsigned char key_read;
 
    key_dev->count_ms++;
    key_read = key_dev->read_key();
    
    if(key_dev->count_ms < key_dev->max_dclick_ms)
    {
        if(key_read == KEY_READ_DOWN)
        {
            key_dev->status = KEY_STATUS_DOUBLE_DOWN_SHAKE;
            key_dev->count_ms = 0;                 
        }
    }
    else
    {
        key_dev->status = KEY_STATUS_SHORT_UP_HANDLE;            
    }
 
}
 
/**
description : short click key up handle
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_short_up_handle(struct key_dev *key_dev)
{
    unsigned short key_val;
 
    key_val= key_dev->num<<8 | KEY_EVENT_SHORT;
    
    key_write_value(key_val);
 
    key_val= key_dev->num<<8 | KEY_EVENT_UP_SHORT;
    
    key_write_value(key_val);
 
    key_dev->status = KEY_STATUS_DOWN_CHECK;
}
 
/**
description : double click key down filter shake
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_double_down_shake(struct key_dev *key_dev)
{
    unsigned char key_read;
    static unsigned short old = 0xffff;
 
    if(old == 0xffff)
    {
        old = key_dev->count_ms;
        key_dev->count_ms = 0;
    }
 
    key_dev->count_ms++;
 
    if(key_dev->count_ms < key_dev->shake_filter_ms)
    {
        return;
    }
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_DOWN)
    {
        unsigned short key_val;
 
        key_val= key_dev->num<<8 | KEY_EVENT_DOUBLE;
    
        key_write_value(key_val);
 
        key_dev->status = KEY_STATUS_DOUBLE_UP_CHECK;
        key_dev->count_ms = 0;
    }
    else
    {
        key_dev->status = KEY_STATUS_DOUBLE_CHECK;
        key_dev->count_ms += old;        
    }
 
    old = 0xffff;
}
 
/**
description : double click key up check
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_double_up_check(struct key_dev *key_dev)
{
    unsigned char key_read;
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_UP)
    {
        key_dev->status = KEY_STATUS_DOUBLE_UP_SHAKE;
        key_dev->count_ms = 0;
    }
}
 
/**
description : double click key up filter shake
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_double_up_shake(struct key_dev *key_dev)
{
    unsigned char key_read;
 
    key_dev->count_ms++;
 
    if(key_dev->count_ms < key_dev->shake_filter_ms)
    {
        return;
    }
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_UP)
    {
        key_dev->status = KEY_STATUS_DOUBLE_UP_HANDLE;
    }
    else
    {
        key_dev->status = KEY_STATUS_DOUBLE_UP_CHECK;
    }
 
}
 
/**
description : double click key up handle
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_double_up_handle(struct key_dev *key_dev)
{
    unsigned short key_val;
 
    key_val= key_dev->num<<8 | KEY_EVENT_UP_DOUBLE;
    
    key_write_value(key_val);
 
    key_dev->status = KEY_STATUS_DOWN_CHECK;
}
 
/**
description : long click handle after long click check
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_long_hanle(struct key_dev *key_dev)
{
    unsigned short key_val;
 
    key_val= key_dev->num<<8 | KEY_EVENT_LONG;
    
    key_write_value(key_val);
 
    key_dev->status = KEY_STATUS_CONTINUE_CHECK;
    key_dev->count_ms = 0;
}
 
/**
description : continue send short click if long click time overflow
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_continue_check(struct key_dev *key_dev)
{
    unsigned char key_read;
    unsigned short key_val;
 
    key_dev->count_ms++;
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_UP)
    {
        key_dev->status = KEY_STATUS_LONG_UP_SHAKE;
    }
 
    if(key_dev->count_ms < key_dev->continue_send_ms)
    {
        return;
    }
 
    if(key_dev->continue_send_ms == 0)
    {
        return;
    }
  
    key_val= key_dev->num<<8 | KEY_EVENT_SHORT;
    
    key_write_value(key_val);
    key_dev->count_ms = 0;
}
 
/**
description : long click key up filter shake
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_long_up_shake(struct key_dev *key_dev)
{
    unsigned char key_read;
    static unsigned short old = 0xffff;
 
    if(old == 0xffff)
    {
        old = key_dev->count_ms;
        key_dev->count_ms = 0;
    }
 
    key_dev->count_ms++;
 
    if(key_dev->count_ms < key_dev->shake_filter_ms)
    {
        return;
    }
 
    key_read = key_dev->read_key();
 
    if(key_read == KEY_READ_UP)
    {
        key_dev->status = KEY_STATUS_LONG_UP_HANDLE;
    }
    else
    {
        key_dev->status = KEY_STATUS_CONTINUE_CHECK;
        key_dev->count_ms += old;      
    }
    
    old = 0xffff;
}
 
/**
description : long click key up filter handle
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_status_long_up_handle(struct key_dev *key_dev)
{
    unsigned short key_val;
 
    key_val= key_dev->num<<8 | KEY_EVENT_UP_LONG;
    
    key_write_value(key_val);
 
    key_dev->status = KEY_STATUS_DOWN_CHECK;
}
 
/**
description : run key state machine once every 1ms
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
*/
static void key_check_1ms(struct key_dev *key_dev)
{
    switch(key_dev->status)
    {
        case KEY_STATUS_DOWN_CHECK :
             key_status_down_check(key_dev);
             break;      
        case KEY_STATUS_DOWN_SHAKE : 
             key_status_down_shake(key_dev);
             break;           
        case KEY_STATUS_DOWN_HANDLE : 
             key_status_down_handle(key_dev);
             break;          
        case KEY_STATUS_LONG_CHECK : 
             key_status_long_check(key_dev);
             break;              
        case KEY_STATUS_SHORT_UP_SHAKE :  
             key_status_short_up_shake(key_dev);
             break;
        case KEY_STATUS_DOUBLE_CHECK :
             key_status_double_check(key_dev);
             break;
        case KEY_STATUS_SHORT_UP_HANDLE :
             key_status_short_up_handle(key_dev);
             break;
        case KEY_STATUS_DOUBLE_DOWN_SHAKE : 
             key_status_double_down_shake(key_dev);
             break;
        case KEY_STATUS_DOUBLE_UP_CHECK :
             key_status_double_up_check(key_dev);
             break;
        case KEY_STATUS_DOUBLE_UP_SHAKE :
             key_status_double_up_shake(key_dev);
             break;
        case KEY_STATUS_DOUBLE_UP_HANDLE :
             key_status_double_up_handle(key_dev);
             break;         
        case KEY_STATUS_LONG_HANDLE :
             key_status_long_hanle(key_dev);
             break;
        case KEY_STATUS_CONTINUE_CHECK : 
             key_status_continue_check(key_dev);
             break;
        case KEY_STATUS_LONG_UP_SHAKE : 
             key_status_long_up_shake(key_dev);
             break;
        case KEY_STATUS_LONG_UP_HANDLE :  
             key_status_long_up_handle(key_dev);
             break;
        default:
             key_dev->status = key_dev->status;
    }
}
 
/**
description : run all key state machine once every 1ms
param : key_dev - key device pointer
retval : None
author : huohongpeng
data : 2017-03-02
call :
       timer(1ms) interrupt handle 
*/
void key_check_all_loop_1ms(void)
{
    unsigned char key_num, i;
 
    key_num = sizeof(key_dev)/sizeof(struct key_dev);
 
    for(i = 0; i < key_num; i++)
    {
        key_check_1ms(&key_dev[i]);
    }
 
}

