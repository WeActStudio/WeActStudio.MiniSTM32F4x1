# Micropython
## WeAct_F401CC
> firmware_xxxxxxx_stm32f401_vxx_v1.12-35 The Latest 最新

> `4m_flash`: External Nor Flash as MSC Dervice 外部Nor Flash 作为 MSC 设备

> `none_rom`: None MSC Dervice,Use Serial PA9PA10.使用串口PA9PA10通讯

> 使用教程：https://www.weact-tc.cn/2020/01/01/micropython/


```
SPIFLASH:
#define MICROPY_HW_SPIFLASH_CS      (pin_A4)
#define MICROPY_HW_SPIFLASH_SCK     (pin_A5)
#if VERSION_V20
	#define MICROPY_HW_SPIFLASH_MISO    (pin_B4)
#else 
	#define MICROPY_HW_SPIFLASH_MISO    (pin_A6)
#endif
#define MICROPY_HW_SPIFLASH_MOSI    (pin_A7)
```