MCU_SERIES = f4
CMSIS_MCU = STM32F401xC
AF_FILE = boards/stm32f401_af.csv
LD_FILES = boards/WeAct_F401CC/stm32f401xc.ld boards/common_basic.ld

# Don't include default frozen modules because MCU is tight on flash space
FROZEN_MANIFEST ?=