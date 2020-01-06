/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W25QXX_H
#define __W25QXX_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "spi.h"
	 
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup W25QXXXX
  * @{
  */

/** @defgroup W25QXXXX_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup W25QXXXX_Exported_Constants
  * @{
  */
   
/** 
  * @brief  W25QXX Configuration  
  */  
									/* W25Q32 */
#define W25QXXXX_FLASH_SIZE                  0x0400000 /* 32 MBits => 4MBytes */
#define W25QXXXX_SECTOR_COUNT                0x40      /* 64 sectors of 64KBytes */
#define W25QXXXX_SECTOR_SIZE                 0x10000   /* 64 sectors of 64KBytes */
#define W25QXXXX_SUBSECTOR_COUNT             0x0400    /* 1024 subsectors of 4kBytes */
#define W25QXXXX_SUBSECTOR_SIZE              0x1000    /* 1024 subsectors of 4kBytes */
#define W25QXXXX_PAGE_SIZE                   0x100     /* 16384 pages of 256 bytes */


#define W25QXXXX_DUMMY_CYCLES_READ           4
#define W25QXXXX_DUMMY_CYCLES_READ_QUAD      10

#define W25QXXXX_BULK_ERASE_MAX_TIME         250000
#define W25QXXXX_SECTOR_ERASE_MAX_TIME       3000
#define W25QXXXX_SUBSECTOR_ERASE_MAX_TIME    800
#define W25QXXXX_TIMEOUT_VALUE 1000

/** 
  * @brief  W25QXX Commands  
  */  
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

#define ENTER_QPI_MODE_CMD                   0x38
#define EXIT_QPI_MODE_CMD                    0xFF

/* Identification Operations */
#define READ_ID_CMD                          0x90
#define DUAL_READ_ID_CMD                     0x92
#define QUAD_READ_ID_CMD                     0x94
#define READ_JEDEC_ID_CMD                    0x9F

/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define READ_STATUS_REG3_CMD                  0x15

#define WRITE_STATUS_REG1_CMD                 0x01
#define WRITE_STATUS_REG2_CMD                 0x31
#define WRITE_STATUS_REG3_CMD                 0x11


/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QUAD_INPUT_PAGE_PROG_CMD             0x32


/* Erase Operations */
#define SECTOR_ERASE_CMD                     0x20
#define CHIP_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75


/* Flag Status Register */
#define W25QXXXX_FSR_BUSY                    ((uint8_t)0x01)    /*!< busy */
#define W25QXXXX_FSR_WREN                    ((uint8_t)0x02)    /*!< write enable */
#define W25QXXXX_FSR_QE                      ((uint8_t)0x02)    /*!< quad enable */


#define W25Qx_Enable() 			HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET)
#define W25Qx_Disable() 		HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET)

#define W25Qx_OK            ((uint8_t)0x00)
#define W25Qx_ERROR         ((uint8_t)0x01)
#define W25Qx_BUSY          ((uint8_t)0x02)
#define W25Qx_TIMEOUT				((uint8_t)0x03)


uint8_t W25Qx_Init(void);
static void	W25Qx_Reset(void);
static uint8_t W25Qx_GetStatus(void);
uint8_t W25Qx_WriteEnable(void);
void W25Qx_Read_ID(uint16_t *ID);
uint8_t W25Qx_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t W25Qx_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t W25Qx_Erase_Block(uint32_t Address);
uint8_t W25Qx_Erase_Chip(void);

/**
  * @}
  */
  
/** @defgroup W25QXXXX_Exported_Functions
  * @{
  */ 
/**
  * @}
  */ 
      
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __W25Qx_H */

