/*
 * FXLS8974C.h
 *
 *  Created on: Jan 11, 2025
 *      Author: Fato
 */

#ifndef INC_FXLS8974C_H_
#define INC_FXLS8974C_H_

#include <stdint.h>
#include "main.h"
#include "stm32h7xx_hal_i2c.h"

// Device addresses definitions

#define FXLS8974_DEVICE_ADDRESS_SA0_0 				(0x18) 			// Device Address Value
#define FXLS8974_DEVICE_ADDRESS_SA0_1 				(0x19)			// Device Address Value

// Device known values definitions

#define FXLS8974_WHOAMI_VALUE 						(0x86)    		// Who AM I Value of FXLS8974CF

#define FXLS8974_SYS_MODE_BUF_GARE_ERROR_NO 		((uint8_t)0x00) // SYS_MODE - Not Detected
#define FXLS8974_SYS_MODE_BUF_GARE_ERROR_YES 		((uint8_t)0x80)	// SYS_MODE - Detected
#define FXLS8974_SYS_MODE_SYS_MODE_STANDBY 			((uint8_t)0x00) // SYS_MODE - Standby Mode
#define FXLS8974_SYS_MODE_SYS_MODE_WAKE 			((uint8_t)0x01) // SYS_MODE - Wake Mode
#define FXLS8974_SYS_MODE_SYS_MODE_SLEEP 			((uint8_t)0x02) // SYS_MODE - Sleep Mode
#define FXLS8974_SYS_MODE_SYS_MODE_EXT_TRIG 		((uint8_t)0x03) // SYS_MODE - External Trigger Mode

#define FXLS8974_SENS_CONFIG1_RST_RST 				((uint8_t)0x80)	// SENS_CONFIG1 - Trigger Reset
#define FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_DISABLED 	((uint8_t)0x00) // SENS_CONFIG1 - Self-Test function is disabled
#define FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_X 		((uint8_t)0x20) // SENS_CONFIG1 - Self-Test function is enabled for X-axis
#define FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_Y 		((uint8_t)0x40) // SENS_CONFIG1 - Self-Test function is enabled for Y-axis
#define FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_Z 		((uint8_t)0x60) // SENS_CONFIG1 - Self-Test function is enabled for Z-axis
#define FXLS8974_SENS_CONFIG1_ST_POL_POSITIVE 		((uint8_t)0x00) // SENS_CONFIG1 - Proof mass displacement for the selected axis is in the positive direction
#define FXLS8974_SENS_CONFIG1_ST_POL_NEGATIVE 		((uint8_t)0x10) // SENS_CONFIG1 - Proof mass displacement for the selected axis is in the negative direction
#define FXLS8974_SENS_CONFIG1_SPI_M_FOUR 			((uint8_t)0x00) // SENS_CONFIG1 - 4-wire interface mode is selected
#define FXLS8974_SENS_CONFIG1_SPI_M_THREE 			((uint8_t)0x08) // SENS_CONFIG1 - 3-wire interface mode is selected
#define FXLS8974_SENS_CONFIG1_FSR_2G 				((uint8_t)0x00) // SENS_CONFIG1 - ±2g; 0.98 mg/LSB (1024 LSB/g) nominal sensitivity
#define FXLS8974_SENS_CONFIG1_FSR_4G 				((uint8_t)0x02) // SENS_CONFIG1 - ±4g; 1.95 mg/LSB (512 LSB/g) nominal sensitivity
#define FXLS8974_SENS_CONFIG1_FSR_8G 				((uint8_t)0x04) // SENS_CONFIG1 - ±8g; 3.91 mg/LSB (256 LSB/g) nominal sensitivity
#define FXLS8974_SENS_CONFIG1_FSR_16G 				((uint8_t)0x06) // SENS_CONFIG1 - ±16g; 7.81 mg/LSB (128 LSB/g) nominal sensitivity
#define FXLS8974_SENS_CONFIG1_ACTIVE_STANDBY 		((uint8_t)0x00) // SENS_CONFIG1 - Standby mode
#define FXLS8974_SENS_CONFIG1_ACTIVE_ACTIVE 		((uint8_t)0x01) // SENS_CONFIG1 - Active mode

#define FXLS8974_SENS_CONFIG2_WAKE_PM_LOW_POWER 	((uint8_t)0x00) // SENS_CONFIG2 - Low Power mode is selected
#define FXLS8974_SENS_CONFIG2_WAKE_PM_HIGH_PERF 	((uint8_t)0x40) // SENS_CONFIG2 - High Performance Mode is selected
#define FXLS8974_SENS_CONFIG2_WAKE_PM_FLEX_PERF 	((uint8_t)0x80) // SENS_CONFIG2 - Flexible Performance Mode is selected
#define FXLS8974_SENS_CONFIG2_SLEEP_PM_LOW_POWER 	((uint8_t)0x00) // SENS_CONFIG2 - Low Power mode is selected
#define FXLS8974_SENS_CONFIG2_SLEEP_PM_HIGH_PERF 	((uint8_t)0x10)	// SENS_CONFIG2 - High Performance Mode is selected
#define FXLS8974_SENS_CONFIG2_SLEEP_PM_FLEX_PERF 	((uint8_t)0x20)	// SENS_CONFIG2 - Flexible Performance Mode is selected
#define FXLS8974_SENS_CONFIG2_LE_BE_LE 				((uint8_t)0x00) // SENS_CONFIG2 - Little-endian output mode is selected
#define FXLS8974_SENS_CONFIG2_LE_BE_BE 				((uint8_t)0x08) // SENS_CONFIG2 - Big-endian output mode is selected
#define FXLS8974_SENS_CONFIG2_ANIC_TEMP_DIS 		((uint8_t)0x00) // SENS_CONFIG2 - TEMP_OUT register content is not included in auto-increment address range
#define FXLS8974_SENS_CONFIG2_ANIC_TEMP_EN 			((uint8_t)0x02) // SENS_CONFIG2 - TEMP_OUT register content is included in auto-increment address range
#define FXLS8974_SENS_CONFIG2_F_READ_NORMAL 		((uint8_t)0x00) // SENS_CONFIG2 - Normal read mode
#define FXLS8974_SENS_CONFIG2_F_READ_FAST 			((uint8_t)0x01) // SENS_CONFIG2 - Fast read mode

#define FXLS8974_SENS_CONFIG3_WAKE_ODR_3200HZ 		((uint8_t)0x00)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_1600HZ 		((uint8_t)0x10)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_800HZ 		((uint8_t)0x20)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_400HZ 		((uint8_t)0x30)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_200HZ 		((uint8_t)0x40)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_100HZ 		((uint8_t)0x50)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_50HZ 		((uint8_t)0x60)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_25HZ 		((uint8_t)0x70)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_12_5HZ 		((uint8_t)0x80)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_6_25HZ 		((uint8_t)0x90) // SENS_CONFIG3 - 6.25 HZ
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_3_125HZ 		((uint8_t)0xa0) // SENS_CONFIG3 - 3.125 HZ
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_1_563HZ 		((uint8_t)0xb0) // SENS_CONFIG3 - 1.563 HZ
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_0_781HZ 		((uint8_t)0xc0) // SENS_CONFIG3 - 0.781 HZ
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_3200HZ 		((uint8_t)0x00)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_1600HZ 		((uint8_t)0x01)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_800HZ 		((uint8_t)0x02)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_400HZ 		((uint8_t)0x03)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_200HZ 		((uint8_t)0x04)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_100HZ 		((uint8_t)0x05)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_50HZ 		((uint8_t)0x06)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_25HZ 		((uint8_t)0x07)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_12_5HZ 		((uint8_t)0x08)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_6_25HZ 		((uint8_t)0x09) // SENS_CONFIG3 - 6.25 HZ
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_3_125HZ 	((uint8_t)0x0a) // SENS_CONFIG3 - 3.125 HZ
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_1_563HZ 	((uint8_t)0x0b) // SENS_CONFIG3 - 1.563 HZ
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_0_781HZ 	((uint8_t)0x0c) // SENS_CONFIG3 - 0.781 HZ

#define FXLS8974_SENS_CONFIG4_EXT_TRIG_M_SINGLE 	((uint8_t)0x00) // SENS_CONFIG4 - Each positive going trigger edge causes a single ADC acquisition to be made
#define FXLS8974_SENS_CONFIG4_EXT_TRIG_M_MULTIPLE 	((uint8_t)0x80) // SENS_CONFIG4 - Each positive going trigger edge causes the number of acquisitions
#define FXLS8974_SENS_CONFIG4_WK_SDCD_WT_DIS 		((uint8_t)0x00) // SENS_CONFIG4 - SDCD within thresholds event is not used to prevent entry into/trigger
#define FXLS8974_SENS_CONFIG4_WK_SDCD_WT_EN 		((uint8_t)0x40) // SENS_CONFIG4 - SDCD within thresholds event is used to prevent entry into/trigger an exit from SLEEP mode
#define FXLS8974_SENS_CONFIG4_WK_SDCD_OT_DIS 		((uint8_t)0x00) // SENS_CONFIG4 - SDCD outside thresholds event is not used to prevent entry into/trigger
#define FXLS8974_SENS_CONFIG4_WK_SDCD_OT_EN 		((uint8_t)0x20) // SENS_CONFIG4 - SDCD outside thresholds event is used to prevent entry into/trigger an exit from SLEEP mode
#define FXLS8974_SENS_CONFIG4_WK_ORIENT_DIS 		((uint8_t)0x00) // SENS_CONFIG4 - Orientation change condition is not used as an event to prevent entry into /trigger an exit from SLEEP mode
#define FXLS8974_SENS_CONFIG4_WK_ORIENT_EN 			((uint8_t)0x10) // SENS_CONFIG4 - Orientation change condition is used as an event to prevent entry into/trigger an exit from SLEEP mode
#define FXLS8974_SENS_CONFIG4_DRDY_PUL_DIS 			((uint8_t)0x00) // SENS_CONFIG4 - A SRC_DRDY event is output on the INTx pin as an active high or active low signal
#define FXLS8974_SENS_CONFIG4_DRDY_PUL_EN 			((uint8_t)0x08) // SENS_CONFIG4 - A 32 μs (nominal) duration pulse is output on the configured INTx pin once per ODR cycle
#define FXLS8974_SENS_CONFIG4_INT2_FUNC_INT2 		((uint8_t)0x00) // SENS_CONFIG4 - INT2/EXT_TRIG pin is configured for the INT2 output function
#define FXLS8974_SENS_CONFIG4_INT2_FUNC_EXT_TRIG   	((uint8_t)0x04) // SENS_CONFIG4 - INT2/EXT_TRIG pin is configured as the EXT_TRIG input function
#define FXLS8974_SENS_CONFIG4_INT_PP_OD_PUSH_PULL 	((uint8_t)0x00) // SENS_CONFIG4 - INTx output pin driver is push-pull type
#define FXLS8974_SENS_CONFIG4_INT_PP_OD_OPEN_DRAIN 	((uint8_t)0x02) // SENS_CONFIG4 - INTx output pin driver is open-drain/open-source type
#define FXLS8974_SENS_CONFIG4_INT_POL_ACT_LOW 		((uint8_t)0x00) // SENS_CONFIG4 - Active low:Interrupt events are signaled with a logical 0 level
#define FXLS8974_SENS_CONFIG4_INT_POL_ACT_HIGH 		((uint8_t)0x01) // SENS_CONFIG4 - Active high: interrupt events are signaled with a logical 1 level

#define FXLS8974_SENS_CONFIG5_VECM_EN_DIS 			((uint8_t)0x00) // SENS_CONFIG5 - 12-bit vector magnitude result is not calculated on every ODR cycle
#define FXLS8974_SENS_CONFIG5_VECM_EN_EN 			((uint8_t)0x10) // SENS_CONFIG5 - 12-bit vector magnitude result is calculated on every ODR cycle
#define FXLS8974_SENS_CONFIG5_X_DIS_EN 				((uint8_t)0x00) // SENS_CONFIG5 - X-axis measurement is included in the auto-increment address range
#define FXLS8974_SENS_CONFIG5_X_DIS_DIS 			((uint8_t)0x08) // SENS_CONFIG5 - X-axis measurement is excluded from the auto-increment address range
#define FXLS8974_SENS_CONFIG5_Y_DIS_EN 				((uint8_t)0x00) // SENS_CONFIG5 - Y-axis measurement is included in the auto-increment address range
#define FXLS8974_SENS_CONFIG5_Y_DIS_DIS 			((uint8_t)0x04) // SENS_CONFIG5 - Y-axis measurement is excluded from the auto-increment address range
#define FXLS8974_SENS_CONFIG5_Z_DIS_EN 				((uint8_t)0x00) // SENS_CONFIG5 - Z-axis measurement is included in the auto-increment address range
#define FXLS8974_SENS_CONFIG5_Z_DIS_DIS 			((uint8_t)0x02) // SENS_CONFIG5 - Z-axis measurement is excluded from the auto-increment address range
#define FXLS8974_SENS_CONFIG5_HIBERNATE_EN_DIS 		((uint8_t)0x00) // SENS_CONFIG5 - Hibernate mode not enabled
#define FXLS8974_SENS_CONFIG5_HIBERNATE_EN_EN 		((uint8_t)0x01) // SENS_CONFIG5 - Commands device to enter Hibernate mode

// INT_EN - Bit field value definitions

#define FXLS8974_INT_EN_DRDY_EN_DIS 				((uint8_t)0x00)	// INT_EN - Interrupt is disabled
#define FXLS8974_INT_EN_DRDY_EN_EN 					((uint8_t)0x80) // INT_EN - Interrupt enabled
#define FXLS8974_INT_EN_BUF_EN_DIS 					((uint8_t)0x00) // INT_EN - Interrupt is disabled
#define FXLS8974_INT_EN_BUF_EN_EN 					((uint8_t)0x40) // INT_EN - Interrupt enabled
#define FXLS8974_INT_EN_SDCD_OT_EN_DIS 				((uint8_t)0x00) // INT_EN - Interrupt is disabled
#define FXLS8974_INT_EN_SDCD_OT_EN_EN 				((uint8_t)0x20) // INT_EN - Interrupt is routed to either the INT1 or INT2
#define FXLS8974_INT_EN_SDCD_WT_EN_DIS 				((uint8_t)0x00) // INT_EN - Interrupt is disabled
#define FXLS8974_INT_EN_SDCD_WT_EN_EN 				((uint8_t)0x10) // INT_EN - Interrupt is routed to either the INT1 or INT2
#define FXLS8974_INT_EN_ORIENT_EN_DIS 				((uint8_t)0x00) // INT_EN - Interrupt is disabled
#define FXLS8974_INT_EN_ORIENT_EN_EN 				((uint8_t)0x08) // INT_EN - Interrupt is enabled and signaled on either the INT1 or INT2
#define FXLS8974_INT_EN_ASLP_EN_DIS 				((uint8_t)0x00) // INT_EN - Interrupt is disabled
#define FXLS8974_INT_EN_ASLP_EN_EN 					((uint8_t)0x04) // INT_EN - Interrupt is enabled and signaled on either the INT1 or INT2
#define FXLS8974_INT_EN_BOOT_DIS_EN 				((uint8_t)0x00) // INT_EN - Boot interrupt is enabled and routed to either the INT1 or INT2
#define FXLS8974_INT_EN_BOOT_DIS_DIS 				((uint8_t)0x02) // INT_EN - Interrupt is disabled and not routed to the INTx output pins
#define FXLS8974_INT_EN_WAKE_OUT_EN_DIS 			((uint8_t)0x00) // INT_EN - The device does not signal the WAKE operating mode on the INTx output pin
#define FXLS8974_INT_EN_WAKE_OUT_EN_EN 				((uint8_t)0x01) // INT_EN - The device signals that it is currently in WAKE mode via the INT1 or INT2 pin

#define FXLS8974_INT_PIN_SEL_DRDY_INT2_DIS 			((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_DRDY_INT2_EN 			((uint8_t)0x80) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_BUF_INT2_DIS 			((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_BUF_INT2_EN 			((uint8_t)0x40) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_SDCD_OT_INT2_DIS 		((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_SDCD_OT_INT2_EN 		((uint8_t)0x20) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_SDCD_WT_INT2_DIS 		((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_SDCD_WT_INT2_EN 		((uint8_t)0x10) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_ORIENT_INT2_DIS 		((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_ORIENT_INT2_EN 		((uint8_t)0x08) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_ASLP_INT2_DIS 			((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_ASLP_INT2_EN 			((uint8_t)0x04) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_BOOT_INT2_DIS 			((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_BOOT_INT2_EN 			((uint8_t)0x02) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_WK_OUT_INT2_DIS 		((uint8_t)0x00) // INT_PIN_SEL - Interrupt signal is routed to INT1 pin if it is enabled
#define FXLS8974_INT_PIN_SEL_WK_OUT_INT2_EN 		((uint8_t)0x01) // INT_PIN_SEL - Interrupt signal is routed to INT2 pin if it is enabled

#define FXLS8974_BUF_CONFIG1_BUF_TYPE_FIFO         	((uint8_t)0x00) // BUF_CONFIG1 - In FIFO mode
#define FXLS8974_BUF_CONFIG1_BUF_TYPE_FILO         	((uint8_t)0x80) // BUF_CONFIG1 - First In Last Out (FILO)
#define FXLS8974_BUF_CONFIG1_BUF_MODE_DIS          	((uint8_t)0x00) // BUF_CONFIG1 - Buffer is disabled
#define FXLS8974_BUF_CONFIG1_BUF_MODE_STREAM_MODE  	((uint8_t)0x20) // BUF_CONFIG1 - Stream Mode
#define FXLS8974_BUF_CONFIG1_BUF_MODE_STOP_MODE    	((uint8_t)0x40) // BUF_CONFIG1 - Stop mode
#define FXLS8974_BUF_CONFIG1_BUF_MODE_TRIGGER_MODE 	((uint8_t)0x60) // BUF_CONFIG1 - Trigger Mode
#define FXLS8974_BUF_CONFIG1_BUF_GATE_BY_PASSED    	((uint8_t)0x00) // BUF_CONFIG1 - Buffer gate is bypassed
#define FXLS8974_BUF_CONFIG1_BUF_GATE_ENABLED      	((uint8_t)0x10) // BUF_CONFIG1 - The Buffer gate input is enabled
#define FXLS8974_BUF_CONFIG1_TRG_SDCD_WT_DIS       	((uint8_t)0x00) // BUF_CONFIG1 - Trigger source is disabled
#define FXLS8974_BUF_CONFIG1_TRG_SDCD_WT_EN        	((uint8_t)0x08) // BUF_CONFIG1 - Trigger source is enabled
#define FXLS8974_BUF_CONFIG1_TRG_SDCD_OT_DIS       	((uint8_t)0x00) // BUF_CONFIG1 - Trigger source is disabled
#define FXLS8974_BUF_CONFIG1_TRG_SDCD_OT_EN        	((uint8_t)0x04) // BUF_CONFIG1 - Trigger source is enabled
#define FXLS8974_BUF_CONFIG1_TRG_ORIENT_DIS        	((uint8_t)0x00) // BUF_CONFIG1 - Trigger source is disabled
#define FXLS8974_BUF_CONFIG1_TRG_ORIENT_EN         	((uint8_t)0x01) // BUF_CONFIG1 - Trigger source is enabled

#define FXLS8974_BUF_CONFIG2_BUF_FLUSH_COMPLETED   	((uint8_t)0x00) // BUF_CONFIG2 - Buffer flush operation not pending/completed
#define FXLS8974_BUF_CONFIG2_BUF_FLUSH_EN          	((uint8_t)0x80) // BUF_CONFIG2 - Buffer flush enable
#define FXLS8974_BUF_CONFIG2_WAKE_SRC_BUF_IGNORED  	((uint8_t)0x00) // BUF_CONFIG2 - BUF_WMRK and BUF_OVF and event flags are ignored by the auto-WAKE/SLEEP function
#define FXLS8974_BUF_CONFIG2_WAKE_SRC_BUF_EN       	((uint8_t)0x40) // BUF_CONFIG2 - BUF_WMRK and BUF_OVF event flags are used by the auto-WAKE/SLEEP function

#define FXLS8974_ORIENT_STATUS_NEW_ORIENT_NO_CHANGE ((uint8_t)0x00) // ORIENT_STATUS - No change in orientation detected
#define FXLS8974_ORIENT_STATUS_NEW_ORIENT_CHANGED  	((uint8_t)0x80) // ORIENT_STATUS - BAFRO and/or LAPO and/or Z-tilt lockout value has changed
#define FXLS8974_ORIENT_STATUS_LO_NOT_DETECTED 	   	((uint8_t)0x00) // ORIENT_STATUS - Lockout condition has not been detected
#define FXLS8974_ORIENT_STATUS_LO_DETECTED 		   	((uint8_t)0x40) // ORIENT_STATUS - Z-tilt lockout trip angle has been exceeded. Lockout condition has been detected
#define FXLS8974_ORIENT_STATUS_LAPO_UP 			   	((uint8_t)0x00) // ORIENT_STATUS - Portrait up
#define FXLS8974_ORIENT_STATUS_LAPO_DOWN 		   	((uint8_t)0x02) // ORIENT_STATUS - Portrait down
#define FXLS8974_ORIENT_STATUS_LAPO_RIGHT 		   	((uint8_t)0x04) // ORIENT_STATUS - Landscape right
#define FXLS8974_ORIENT_STATUS_LAPO_LEFT 		   	((uint8_t)0x06) // ORIENT_STATUS - Landscape left
#define FXLS8974_ORIENT_STATUS_BAFRO_FRONT 		   	((uint8_t)0x00) // ORIENT_STATUS - The device is in the front-facing orientation
#define FXLS8974_ORIENT_STATUS_BAFRO_BACK 		   	((uint8_t)0x01)	// ORIENT_STATUS - The device is in the back-facing orientation

#define FXLS8974_ORIENT_CONFIG_ORIENT_DBCNTM_DEC   	((uint8_t)0x00) // ORIENT_CONFIG - Orientation debounce counter is decremented whenever the current orientation is different thanthe previous one
#define FXLS8974_ORIENT_CONFIG_ORIENT_DBCNTM_CLR   	((uint8_t)0x80) // ORIENT_CONFIG - Orientation debounce counter is cleared whenever the current orientation is different than the previous one
#define FXLS8974_ORIENT_CONFIG_ORIENT_ENABLE_DIS 	((uint8_t)0x00) // ORIENT_CONFIG - Orientation detection function is disabled
#define FXLS8974_ORIENT_CONFIG_ORIENT_ENABLE_EN 	((uint8_t)0x40) // ORIENT_CONFIG - Orientation detection function is enabled

#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_BKFR_BF_80_280_FB_100_260 ((uint8_t)0x00) // ORIENT_BF_ZCOMP - Back to front Z < 80° or Z > 280° and Front to back Z > 100° and Z < 260°
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_BKFR_BF_75_285_FB_105_255 ((uint8_t)0x40) // ORIENT_BF_ZCOMP - Back to front Z < 75° or Z > 285° and Front to back Z > 105° and Z < 255°
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_BKFR_BF_70_290_FB_110_250 ((uint8_t)0x80) // ORIENT_BF_ZCOMP - Back to front Z < 70° or Z > 290° and Front to back Z > 110° and Z < 250°
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_BKFR_BF_65_295_FB_115_245 ((uint8_t)0xc0) // ORIENT_BF_ZCOMP - Back to front Z < 65° or Z > 295° and Front to back Z > 115° and Z < 250°
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_13_6 	((uint8_t)0x00) // ORIENT_BF_ZCOMP - Resultant angle 13.6
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_17_1 	((uint8_t)0x01) // ORIENT_BF_ZCOMP - Resultant angle 17.1
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_20_7 	((uint8_t)0x02) // ORIENT_BF_ZCOMP - Resultant angle 20.7
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_24_4 	((uint8_t)0x03) // ORIENT_BF_ZCOMP - Resultant angle 24.4
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_28_1 	((uint8_t)0x04) // ORIENT_BF_ZCOMP - Resultant angle 28.1
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_32_0 	((uint8_t)0x05) // ORIENT_BF_ZCOMP - Resultant angle 32.0
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_36_1 	((uint8_t)0x06) // ORIENT_BF_ZCOMP - Resultant angle 36.1
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_40_4 	((uint8_t)0x07) // ORIENT_BF_ZCOMP - Resultant angle 40.4

#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_0_0 		((uint8_t)0x00) // ORIENT_THS_REG - 0.0°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_1_8 		((uint8_t)0x08) // ORIENT_THS_REG - 1.8°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_3_8 		((uint8_t)0x10) // ORIENT_THS_REG -  3.8°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_5_9 		((uint8_t)0x18) // ORIENT_THS_REG - 5.9°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_8_1 		((uint8_t)0x20) // ORIENT_THS_REG - 8.1°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_10_5 	((uint8_t)0x28) // ORIENT_THS_REG - 10.5°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_13_0 	((uint8_t)0x30) // ORIENT_THS_REG - 13.0°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_15_6 	((uint8_t)0x38) // ORIENT_THS_REG - 15.6°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_18_4 	((uint8_t)0x40) // ORIENT_THS_REG - 18.4°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_21_4 	((uint8_t)0x48) // ORIENT_THS_REG - 21.4°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_24_4 	((uint8_t)0x50) // ORIENT_THS_REG - 24.4°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_27_6 	((uint8_t)0x58) // ORIENT_THS_REG - 27.6°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_31_0 	((uint8_t)0x60) // ORIENT_THS_REG - 31.0°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_34_4 	((uint8_t)0x68) // ORIENT_THS_REG - 34.4°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_37_9 	((uint8_t)0x70) // ORIENT_THS_REG - 37.9°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_41_4 	((uint8_t)0x78) // ORIENT_THS_REG - 41.4°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_45_0 	((uint8_t)0x80) // ORIENT_THS_REG - 45.0°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_48_6 	((uint8_t)0x88) // ORIENT_THS_REG - 48.6°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_52_1 	((uint8_t)0x90) // ORIENT_THS_REG - 52.1°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_55_6 	((uint8_t)0x98) // ORIENT_THS_REG - 55.6°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_59_0 	((uint8_t)0xa0) // ORIENT_THS_REG - 59.0°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_62_4 	((uint8_t)0xa8) // ORIENT_THS_REG - 62.4°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_65_6 	((uint8_t)0xb0) // ORIENT_THS_REG - 65.6°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_68_6 	((uint8_t)0xb8) // ORIENT_THS_REG - 68.6°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_71_6 	((uint8_t)0xc0) // ORIENT_THS_REG - 71.6°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_74_4 	((uint8_t)0xc8) // ORIENT_THS_REG - 74.4°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_77_0 	((uint8_t)0xd0) // ORIENT_THS_REG - 77.0°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_79_5 	((uint8_t)0xd8) // ORIENT_THS_REG - 79.5°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_81_9 	((uint8_t)0xe0) // ORIENT_THS_REG - 81.9°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_84_1 	((uint8_t)0xe8) // ORIENT_THS_REG - 84.1°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_86_2 	((uint8_t)0xf0) // ORIENT_THS_REG - 86.2°
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_88_2 	((uint8_t)0xf8) // ORIENT_THS_REG - 88.2°
#define FXLS8974_ORIENT_THS_REG_HYS_45_45 			((uint8_t)0x00) // ORIENT_THS_REG - L-to-P 45° P-to-L 45°
#define FXLS8974_ORIENT_THS_REG_HYS_49_41 			((uint8_t)0x01) // ORIENT_THS_REG - L-to-P 49° P-to-L 41°
#define FXLS8974_ORIENT_THS_REG_HYS_52_38 			((uint8_t)0x02) // ORIENT_THS_REG - L-to-P 52° P-to-L 38°
#define FXLS8974_ORIENT_THS_REG_HYS_56_34 			((uint8_t)0x03) // ORIENT_THS_REG - L-to-P 56° P-to-L 34°
#define FXLS8974_ORIENT_THS_REG_HYS_59_31 			((uint8_t)0x04) // ORIENT_THS_REG - L-to-P 59° P-to-L 31°
#define FXLS8974_ORIENT_THS_REG_HYS_62_28 			((uint8_t)0x05) // ORIENT_THS_REG - L-to-P 62° P-to-L 28°
#define FXLS8974_ORIENT_THS_REG_HYS_66_24 			((uint8_t)0x06) // ORIENT_THS_REG - L-to-P 66° P-to-L 24°
#define FXLS8974_ORIENT_THS_REG_HYS_69_21 			((uint8_t)0x07) // ORIENT_THS_REG - L-to-P 69° P-to-L 21°

#define FXLS8974_SDCD_INT_SRC1_OT_EA_INSIDE 		((uint8_t)0x00) // SDCD_INT_SRC1 - Event flag has not been asserted
#define FXLS8974_SDCD_INT_SRC1_OT_EA_OUTSIDE 		((uint8_t)0x80) // SDCD_INT_SRC1 - Event flag has been asserted
#define FXLS8974_SDCD_INT_SRC1_X_OT_EF_EVENT_NO 	((uint8_t)0x00) // SDCD_INT_SRC1 - Event has not occured
#define FXLS8974_SDCD_INT_SRC1_X_OT_EF_EVENT_YES 	((uint8_t)0x20) // SDCD_INT_SRC1 - Event has occured
#define FXLS8974_SDCD_INT_SRC1_X_OT_POL_LT_THS 		((uint8_t)0x00) // SDCD_INT_SRC1 - Less than lower Threshold
#define FXLS8974_SDCD_INT_SRC1_X_OT_POL_GT_THS 		((uint8_t)0x10) // SDCD_INT_SRC1 - Greater than upper threshold
#define FXLS8974_SDCD_INT_SRC1_Y_OT_EF_EVENT_NO 	((uint8_t)0x00) // SDCD_INT_SRC1 - Event has not occured
#define FXLS8974_SDCD_INT_SRC1_Y_OT_EF_EVENT_YES 	((uint8_t)0x08) // SDCD_INT_SRC1 - Event has occured
#define FXLS8974_SDCD_INT_SRC1_Y_OT_POL_LT_THS 		((uint8_t)0x00) // SDCD_INT_SRC1 - Less than lower Threshold
#define FXLS8974_SDCD_INT_SRC1_Y_OT_POL_GT_THS 		((uint8_t)0x04) // SDCD_INT_SRC1 - Greater than upper threshold
#define FXLS8974_SDCD_INT_SRC1_Z_OT_EF_EVENT_NO 	((uint8_t)0x00) // SDCD_INT_SRC1 - Event has not occured
#define FXLS8974_SDCD_INT_SRC1_Z_OT_EF_EVENT_YES 	((uint8_t)0x02) // SDCD_INT_SRC1 - Event has occured
#define FXLS8974_SDCD_INT_SRC1_Z_OT_POL_LT_THS 		((uint8_t)0x00) // SDCD_INT_SRC1 - Less than lower Threshold
#define FXLS8974_SDCD_INT_SRC1_Z_OT_POL_GT_THS 		((uint8_t)0x01) // SDCD_INT_SRC1 - Greater than upper threshold

#define FXLS8974_SDCD_INT_SRC2_WT_EA_EVENT_NO 		((uint8_t)0x00) // SDCD_INT_SRC2 - Event has not occured
#define FXLS8974_SDCD_INT_SRC2_WT_EA_EVENT_YES 		((uint8_t)0x80) // SDCD_INT_SRC2 - Event has occured
#define FXLS8974_SDCD_INT_SRC2_X_WT_EF_IN_RANGE 	((uint8_t)0x00) // SDCD_INT_SRC2 - X-axis data or delta is >= SDCD_UTHS or =< SDCD_LTHS values
#define FXLS8974_SDCD_INT_SRC2_X_WT_EF_OUT_RANGE 	((uint8_t)0x20) // SDCD_INT_SRC2 - X-axis data or delta is < SDCD_UTHS and > SDCD_LTHS value
#define FXLS8974_SDCD_INT_SRC2_Y_WT_EF_IN_RANGE 	((uint8_t)0x00) // SDCD_INT_SRC2 - Y-axis data or delta is >= SDCD_UTHS or =< SDCD_LTHS values
#define FXLS8974_SDCD_INT_SRC2_Y_WT_EF_OUT_RANGE 	((uint8_t)0x08) // SDCD_INT_SRC2 - Y-axis data or delta is < SDCD_UTHS and > SDCD_LTHS value
#define FXLS8974_SDCD_INT_SRC2_Z_WT_EF_IN_RANGE 	((uint8_t)0x00) // SDCD_INT_SRC2 - Z-axis data or delta is >= SDCD_UTHS or =< SDCD_LTHS values
#define FXLS8974_SDCD_INT_SRC2_Z_WT_EF_OUT_RANGE 	((uint8_t)0x02) // SDCD_INT_SRC2 - Z-axis data or delta is < SDCD_UTHS and > SDCD_LTHS value

#define FXLS8974_SDCD_CONFIG1_OT_ELE_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - Outside of thresholds event flag latching is disabled
#define FXLS8974_SDCD_CONFIG1_OT_ELE_EN 			((uint8_t)0x80) // SDCD_CONFIG1 - Outside of thresholds event flag latching is enabled
#define FXLS8974_SDCD_CONFIG1_WT_ELE_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - Within thresholds event flag latching is disabled
#define FXLS8974_SDCD_CONFIG1_WT_ELE_EN 			((uint8_t)0x40) // SDCD_CONFIG1 - Within thresholds event flag latching is enabled
#define FXLS8974_SDCD_CONFIG1_X_OT_EN_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - X-axis data or delta is not used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_X_OT_EN_EN 			((uint8_t)0x20) // SDCD_CONFIG1 - X-axis data or delta is used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Y_OT_EN_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - Y-axis data or delta is not used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Y_OT_EN_EN 			((uint8_t)0x10) // SDCD_CONFIG1 - Y-axis data or delta is used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Z_OT_EN_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - Z-axis data or delta is not used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Z_OT_EN_EN 			((uint8_t)0x08) // SDCD_CONFIG1 - Z-axis data or delta is used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_X_WT_EN_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - X-axis data or delta is not used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_X_WT_EN_EN 			((uint8_t)0x04) // SDCD_CONFIG1 - X-axis data or delta is used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Y_WT_EN_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - Y-axis data or delta is not used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Y_WT_EN_EN 			((uint8_t)0x02) // SDCD_CONFIG1 - Y-axis data or delta is used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Z_WT_EN_DIS 			((uint8_t)0x00) // SDCD_CONFIG1 - Z-axis data or delta is not used in the outside of thresholds condition evaluation
#define FXLS8974_SDCD_CONFIG1_Z_WT_EN_EN 			((uint8_t)0x01) // SDCD_CONFIG1 - Z-axis data or delta is used in the outside of thresholds condition evaluation

#define FXLS8974_SDCD_CONFIG2_SDCD_EN_DIS 			((uint8_t)0x00) // SDCD_CONFIG2 - SDCD function is disabled
#define FXLS8974_SDCD_CONFIG2_SDCD_EN_EN 			((uint8_t)0x80) // SDCD_CONFIG2 - SDCD function is Enabled
#define FXLS8974_SDCD_CONFIG2_REF_UPDM_12_BIT 		((uint8_t)0x00) // SDCD_CONFIG2 - The function stores the first 12-bit X/Y/Z decimated and trimmed input data
#define FXLS8974_SDCD_CONFIG2_REF_UPDM_FIRST 		((uint8_t)0x20) // SDCD_CONFIG2 - The function stores the first decimated and trimmed X/Y/Z acceleration input data
#define FXLS8974_SDCD_CONFIG2_REF_UPDM_SDCD_REF 	((uint8_t)0x40) // SDCD_CONFIG2 - The function updates the SDCD_REF_X/Y/Z values with the current decimated and trimmed X/Y/Z acceleration input data after the function evaluation
#define FXLS8974_SDCD_CONFIG2_REF_UPDM_FIXED_VAL 	((uint8_t)0x60) // SDCD_CONFIG2 - The function uses a fixed value of 0 for each of the SDCD_REF_X/Y/Z registers
#define FXLS8974_SDCD_CONFIG2_OT_DBCTM_DECREMENT 	((uint8_t)0x00) // SDCD_CONFIG2 - Debounce counter is decremented by 1 when the current outside of thresholds result for the enabled axes is false
#define FXLS8974_SDCD_CONFIG2_OT_DBCTM_CLEARED 		((uint8_t)0x10) // SDCD_CONFIG2 - Debounce counter is cleared whenever the current outside of thresholds result for the enabled axes is false
#define FXLS8974_SDCD_CONFIG2_WT_DBCTM_DECREMENT 	((uint8_t)0x00) // SDCD_CONFIG2 - Debounce counter is decremented by 1 when the current outside of thresholds result for the enabled axes is false
#define FXLS8974_SDCD_CONFIG2_WT_DBCTM_CLEARED 		((uint8_t)0x08) // SDCD_CONFIG2 - Debounce counter is cleared whenever the current outside of thresholds result for the enabled axes is false
#define FXLS8974_SDCD_CONFIG2_WT_LOG_SEL_AND 		((uint8_t)0x00) // SDCD_CONFIG2 - Function uses the logical AND of the enabled axes
#define FXLS8974_SDCD_CONFIG2_WT_LOG_SEL_OR 		((uint8_t)0x04) // SDCD_CONFIG2 - Function uses the logical OR of the enabled axes
#define FXLS8974_SDCD_CONFIG2_MODE_XYZ 				((uint8_t)0x00) // SDCD_CONFIG2 -  Function uses X, Y, Z acceleration data for the window comparison
#define FXLS8974_SDCD_CONFIG2_MODE_VECM 			((uint8_t)0x02) // SDCD_CONFIG2 - Function uses Vector magnitude data for the window comparison on the X-axis channel only
#define FXLS8974_SDCD_CONFIG2_REF_UPD_NO_PENDING    ((uint8_t)0x00) // SDCD_CONFIG2 - No reference update pending or reference update has completed
#define FXLS8974_SDCD_CONFIG2_REF_UPD_SYNC_UPDATE 	((uint8_t)0x01) // SDCD_CONFIG2 -  Triggers a synchronous update of the internal X/Y/Z reference registers

#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_1    		((uint8_t)0x00)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_2    		((uint8_t)0x01)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_4    		((uint8_t)0x02)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_8    		((uint8_t)0x03)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_16   		((uint8_t)0x04)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_32   		((uint8_t)0x05)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_64   		((uint8_t)0x06)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_128  		((uint8_t)0x07)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_256  		((uint8_t)0x08)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_512  		((uint8_t)0x09)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_1024 		((uint8_t)0x0a)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_2048 		((uint8_t)0x0b)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_4096 		((uint8_t)0x0c)

#define FXLS8974_TBOOT_MAX 							20              // Maximum safe value for TBOOT1/2 in ms (1ms, 17.7ms)=~20ms

// SYS_MODE - Bit field mask definitions

#define FXLS8974_SYS_MODE_BUF_GATE_ERROR_MASK 		((uint8_t)0x03)
#define FXLS8974_SYS_MODE_BUF_GATE_ERROR_SHIFT 		((uint8_t)0)

#define FXLS8974_SYS_MODE_BUF_GATE_CNT_MASK 		((uint8_t)0x7C)
#define FXLS8974_SYS_MODE_BUF_GATE_CNT_SHIFT 		((uint8_t)2)

#define FXLS8974_SYS_MODE_SYS_MODE_MASK 			((uint8_t)0x80)
#define FXLS8974_SYS_MODE_SYS_MODE_SHIFT 			((uint8_t)7)

// INT_STATUS - Bit field mask definitions

#define FXLS8974_INT_STATUS_SRC_BOOT_MASK 			((uint8_t)0x01)
#define FXLS8974_INT_STATUS_SRC_BOOT_SHIFT 			((uint8_t)0)

#define FXLS8974_INT_STATUS_SRC_ASLP_MASK 			((uint8_t)0x02)
#define FXLS8974_INT_STATUS_SRC_ASLP_SHIFT 			((uint8_t)1)

#define FXLS8974_INT_STATUS_SRC_ORIENT_MASK 		((uint8_t)0x04)
#define FXLS8974_INT_STATUS_SRC_ORIENT_SHIFT 		((uint8_t)2)

#define FXLS8974_INT_STATUS_SRC_SDCD_WT_MASK 		((uint8_t)0x08)
#define FXLS8974_INT_STATUS_SRC_SDCD_WT_SHIFT 		((uint8_t)3)

#define FXLS8974_INT_STATUS_SRC_SDCD_OT_MASK 		((uint8_t)0x10)
#define FXLS8974_INT_STATUS_SRC_SDCD_OT_SHIFT 		((uint8_t)4)

#define FXLS8974_INT_STATUS_SRC_BUF_MASK 			((uint8_t)0x20)
#define FXLS8974_INT_STATUS_SRC_BUF_SHIFT 			((uint8_t)5)

#define FXLS8974_INT_STATUS_SRC_OVF_MASK 			((uint8_t)0x40)
#define FXLS8974_INT_STATUS_SRC_OVF_SHIFT 			((uint8_t)6)

#define FXLS8974_INT_STATUS_SRC_DRDY_MASK 			((uint8_t)0x80)
#define FXLS8974_INT_STATUS_SRC_DRDY_SHIFT 			((uint8_t)7)

// SENS_CONFIG1 - Bit field mask definitions

#define FXLS8974_SENS_CONFIG1_ACTIVE_MASK 			((uint8_t)0x01)
#define FXLS8974_SENS_CONFIG1_ACTIVE_SHIFT 			((uint8_t)0)

#define FXLS8974_SENS_CONFIG1_FSR_MASK 				((uint8_t)0x06)
#define FXLS8974_SENS_CONFIG1_FSR_SHIFT 			((uint8_t)1)

#define FXLS8974_SENS_CONFIG1_SPI_M_MASK 			((uint8_t)0x08)
#define FXLS8974_SENS_CONFIG1_SPI_M_SHIFT 			((uint8_t)3)

#define FXLS8974_SENS_CONFIG1_ST_POL_MASK 			((uint8_t)0x10)
#define FXLS8974_SENS_CONFIG1_ST_POL_SHIFT 			((uint8_t)4)

#define FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK 		((uint8_t)0x60)
#define FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_SHIFT 	((uint8_t)5)

#define FXLS8974_SENS_CONFIG1_RST_MASK 				((uint8_t)0x80)
#define FXLS8974_SENS_CONFIG1_RST_SHIFT 			((uint8_t)7)

// SENS_CONFIG2 - Bit field mask definitions

#define FXLS8974_SENS_CONFIG2_F_READ_MASK 			((uint8_t)0x01)
#define FXLS8974_SENS_CONFIG2_F_READ_SHIFT 			((uint8_t)0)

#define FXLS8974_SENS_CONFIG2_ANIC_TEMP_MASK 		((uint8_t)0x02)
#define FXLS8974_SENS_CONFIG2_ANIC_TEMP_SHIFT 		((uint8_t)1)

#define FXLS8974_SENS_CONFIG2_LE_BE_MASK 			((uint8_t)0x08)
#define FXLS8974_SENS_CONFIG2_LE_BE_SHIFT 			((uint8_t)3)

#define FXLS8974_SENS_CONFIG2_SLEEP_PM_MASK 		((uint8_t)0x30)
#define FXLS8974_SENS_CONFIG2_SLEEP_PM_SHIFT 		((uint8_t)4)

#define FXLS8974_SENS_CONFIG2_WAKE_PM_MASK 			((uint8_t)0xC0)
#define FXLS8974_SENS_CONFIG2_WAKE_PM_SHIFT 		((uint8_t)6)

// SENS_CONFIG3 - Bit field mask definitions

#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_MASK 		((uint8_t)0x0F)
#define FXLS8974_SENS_CONFIG3_SLEEP_ODR_SHIFT 		((uint8_t)0)

#define FXLS8974_SENS_CONFIG3_WAKE_ODR_MASK 		((uint8_t)0xF0)
#define FXLS8974_SENS_CONFIG3_WAKE_ODR_SHIFT 		((uint8_t)4)

// SENS_CONFIG4 - Bit field mask definitions

#define FXLS8974_SENS_CONFIG4_INT_POL_MASK 			((uint8_t)0x01)
#define FXLS8974_SENS_CONFIG4_INT_POL_SHIFT 		((uint8_t)0)

#define FXLS8974_SENS_CONFIG4_INT_PP_OD_MASK 		((uint8_t)0x02)
#define FXLS8974_SENS_CONFIG4_INT_PP_OD_SHIFT 		((uint8_t)1)

#define FXLS8974_SENS_CONFIG4_INT2_FUNC_MASK 		((uint8_t)0x04)
#define FXLS8974_SENS_CONFIG4_INT2_FUNC_SHIFT 		((uint8_t)2)

#define FXLS8974_SENS_CONFIG4_DRDY_PUL_MASK 		((uint8_t)0x08)
#define FXLS8974_SENS_CONFIG4_DRDY_PUL_SHIFT 		((uint8_t)3)

#define FXLS8974_SENS_CONFIG4_WK_ORIENT_MASK 		((uint8_t)0x10)
#define FXLS8974_SENS_CONFIG4_WK_ORIENT_SHIFT 		((uint8_t)4)

#define FXLS8974_SENS_CONFIG4_WK_SDCD_OT_MASK 		((uint8_t)0x20)
#define FXLS8974_SENS_CONFIG4_WK_SDCD_OT_SHIFT 		((uint8_t)5)

#define FXLS8974_SENS_CONFIG4_WK_SDCD_WT_MASK 		((uint8_t)0x40)
#define FXLS8974_SENS_CONFIG4_WK_SDCD_WT_SHIFT 		((uint8_t)6)

#define FXLS8974_SENS_CONFIG4_EXT_TRIG_M_MASK 		((uint8_t)0x80)
#define FXLS8974_SENS_CONFIG4_EXT_TRIG_M_SHIFT 		((uint8_t)7)

// SENS_CONFIG5 - Bit field mask definitions

#define FXLS8974_SENS_CONFIG5_HIBERNATE_EN_MASK 	((uint8_t)0x01)
#define FXLS8974_SENS_CONFIG5_HIBERNATE_EN_SHIFT 	((uint8_t)0)

#define FXLS8974_SENS_CONFIG5_Z_DIS_MASK 			((uint8_t)0x02)
#define FXLS8974_SENS_CONFIG5_Z_DIS_SHIFT 			((uint8_t)1)

#define FXLS8974_SENS_CONFIG5_Y_DIS_MASK 			((uint8_t)0x04)
#define FXLS8974_SENS_CONFIG5_Y_DIS_SHIFT 			((uint8_t)2)

#define FXLS8974_SENS_CONFIG5_X_DIS_MASK 			((uint8_t)0x08)
#define FXLS8974_SENS_CONFIG5_X_DIS_SHIFT 			((uint8_t)3)

#define FXLS8974_SENS_CONFIG5_VECM_EN_MASK 			((uint8_t)0x10)
#define FXLS8974_SENS_CONFIG5_VECM_EN_SHIFT 		((uint8_t)4)

// INT_EN - Bit field mask definitions

#define FXLS8974_INT_EN_WAKE_OUT_EN_MASK 			((uint8_t)0x01)
#define FXLS8974_INT_EN_WAKE_OUT_EN_SHIFT 			((uint8_t)0)

#define FXLS8974_INT_EN_BOOT_DIS_MASK 				((uint8_t)0x02)
#define FXLS8974_INT_EN_BOOT_DIS_SHIFT 				((uint8_t)1)

#define FXLS8974_INT_EN_ASLP_EN_MASK 				((uint8_t)0x04)
#define FXLS8974_INT_EN_ASLP_EN_SHIFT 				((uint8_t)2)

#define FXLS8974_INT_EN_ORIENT_EN_MASK 				((uint8_t)0x08)
#define FXLS8974_INT_EN_ORIENT_EN_SHIFT 			((uint8_t)3)

#define FXLS8974_INT_EN_SDCD_WT_EN_MASK 			((uint8_t)0x10)
#define FXLS8974_INT_EN_SDCD_WT_EN_SHIFT 			((uint8_t)4)

#define FXLS8974_INT_EN_SDCD_OT_EN_MASK 			((uint8_t)0x20)
#define FXLS8974_INT_EN_SDCD_OT_EN_SHIFT 			((uint8_t)5)

#define FXLS8974_INT_EN_BUF_EN_MASK 				((uint8_t)0x40)
#define FXLS8974_INT_EN_BUF_EN_SHIFT 				((uint8_t)6)

#define FXLS8974_INT_EN_DRDY_EN_MASK 				((uint8_t)0x80)
#define FXLS8974_INT_EN_DRDY_EN_SHIFT 				((uint8_t)7)

// INT_PIN_SEL - Bit field mask definitions

#define FXLS8974_INT_PIN_SEL_WK_OUT_INT2_MASK 		((uint8_t)0x01)
#define FXLS8974_INT_PIN_SEL_WK_OUT_INT2_SHIFT 		((uint8_t)0)

#define FXLS8974_INT_PIN_SEL_BOOT_INT2_MASK 		((uint8_t)0x02)
#define FXLS8974_INT_PIN_SEL_BOOT_INT2_SHIFT 		((uint8_t)1)

#define FXLS8974_INT_PIN_SEL_ASLP_INT2_MASK 		((uint8_t)0x04)
#define FXLS8974_INT_PIN_SEL_ASLP_INT2_SHIFT 		((uint8_t)2)

#define FXLS8974_INT_PIN_SEL_ORIENT_INT2_MASK 		((uint8_t)0x08)
#define FXLS8974_INT_PIN_SEL_ORIENT_INT2_SHIFT 		((uint8_t)3)

#define FXLS8974_INT_PIN_SEL_SDCD_WT_INT2_MASK 		((uint8_t)0x10)
#define FXLS8974_INT_PIN_SEL_SDCD_WT_INT2_SHIFT 	((uint8_t)4)

#define FXLS8974_INT_PIN_SEL_SDCD_OT_INT2_MASK 		((uint8_t)0x20)
#define FXLS8974_INT_PIN_SEL_SDCD_OT_INT2_SHIFT 	((uint8_t)5)

#define FXLS8974_INT_PIN_SEL_BUF_INT2_MASK 			((uint8_t)0x40)
#define FXLS8974_INT_PIN_SEL_BUF_INT2_SHIFT 		((uint8_t)6)

#define FXLS8974_INT_PIN_SEL_DRDY_INT2_MASK 		((uint8_t)0x80)
#define FXLS8974_INT_PIN_SEL_DRDY_INT2_SHIFT 		((uint8_t)7)

// BUF_CONFIG1 - Bit field mask definitions

#define FXLS8974_BUF_CONFIG1_TRG_ORIENT_MASK    	((uint8_t)0x01)
#define FXLS8974_BUF_CONFIG1_TRG_ORIENT_SHIFT   	((uint8_t)0)

#define FXLS8974_BUF_CONFIG1_TRG_SDCD_OT_MASK   	((uint8_t)0x04)
#define FXLS8974_BUF_CONFIG1_TRG_SDCD_OT_SHIFT  	((uint8_t)2)

#define FXLS8974_BUF_CONFIG1_TRG_SDCD_WT_MASK   	((uint8_t)0x08)
#define FXLS8974_BUF_CONFIG1_TRG_SDCD_WT_SHIFT  	((uint8_t)3)

#define FXLS8974_BUF_CONFIG1_BUF_GATE_MASK      	((uint8_t)0x10)
#define FXLS8974_BUF_CONFIG1_BUF_GATE_SHIFT     	((uint8_t)4)

#define FXLS8974_BUF_CONFIG1_BUF_MODE_MASK      	((uint8_t)0x60)
#define FXLS8974_BUF_CONFIG1_BUF_MODE_SHIFT     	((uint8_t)5)

#define FXLS8974_BUF_CONFIG1_BUF_TYPE_MASK      	((uint8_t)0x80)
#define FXLS8974_BUF_CONFIG1_BUF_TYPE_SHIFT     	((uint8_t)7)

// BUF_CONFIG2 - Bit field mask definitions

#define FXLS8974_BUF_CONFIG2_BUF_WMRK_MASK       	((uint8_t)0x3F)
#define FXLS8974_BUF_CONFIG2_BUF_WMRK_SHIFT      	((uint8_t)0)

#define FXLS8974_BUF_CONFIG2_WAKE_SRC_BUF_MASK   	((uint8_t)0x40)
#define FXLS8974_BUF_CONFIG2_WAKE_SRC_BUF_SHIFT  	((uint8_t)6)

#define FXLS8974_BUF_CONFIG2_BUF_FLUSH_MASK      	((uint8_t)0x80)
#define FXLS8974_BUF_CONFIG2_BUF_FLUSH_SHIFT     	((uint8_t)7)

// ORIENT_STATUS - Bit field mask definitions

#define FXLS8974_ORIENT_STATUS_BAFRO_MASK 			((uint8_t)0x01)
#define FXLS8974_ORIENT_STATUS_BAFRO_SHIFT 			((uint8_t)0)

#define FXLS8974_ORIENT_STATUS_LAPO_MASK 			((uint8_t)0x06)
#define FXLS8974_ORIENT_STATUS_LAPO_SHIFT 			((uint8_t)1)

#define FXLS8974_ORIENT_STATUS_LO_MASK 				((uint8_t)0x40)
#define FXLS8974_ORIENT_STATUS_LO_SHIFT 			((uint8_t)6)

#define FXLS8974_ORIENT_STATUS_NEW_ORIENT_MASK 		((uint8_t)0x80)
#define FXLS8974_ORIENT_STATUS_NEW_ORIENT_SHIFT 	((uint8_t)7)

// ORIENT_CONFIG - Bit field mask definitions

#define FXLS8974_ORIENT_CONFIG_ORIENT_ENABLE_MASK 	((uint8_t)0x40)
#define FXLS8974_ORIENT_CONFIG_ORIENT_ENABLE_SHIFT 	((uint8_t)6)

#define FXLS8974_ORIENT_CONFIG_ORIENT_DBCNTM_MASK 	((uint8_t)0x80)
#define FXLS8974_ORIENT_CONFIG_ORIENT_DBCNTM_SHIFT 	((uint8_t)7)

// ORIENT_BF_ZCOMP - Bit field mask definitions

#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_MASK 	((uint8_t)0x07)
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_ZLOCK_SHIFT ((uint8_t)0)

#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_BKFR_MASK 	((uint8_t)0xC0)
#define FXLS8974_ORIENT_BF_ZCOMP_ORIENT_BKFR_SHIFT 	((uint8_t)6)

// ORIENT_THS_REG - Bit field mask definitions

#define FXLS8974_ORIENT_THS_REG_HYS_MASK 			((uint8_t)0x07)
#define FXLS8974_ORIENT_THS_REG_HYS_SHIFT 			((uint8_t)0)

#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_MASK 	((uint8_t)0xF8)
#define FXLS8974_ORIENT_THS_REG_ORIENT_THS_SHIFT 	((uint8_t)3)

// SDCD_INT_SRC1 - Bit field mask definitions

#define FXLS8974_SDCD_INT_SRC1_Z_OT_POL_MASK 		((uint8_t)0x01)
#define FXLS8974_SDCD_INT_SRC1_Z_OT_POL_SHIFT 		((uint8_t)0)

#define FXLS8974_SDCD_INT_SRC1_Z_OT_EF_MASK 		((uint8_t)0x02)
#define FXLS8974_SDCD_INT_SRC1_Z_OT_EF_SHIFT 		((uint8_t)1)

#define FXLS8974_SDCD_INT_SRC1_Y_OT_POL_MASK 		((uint8_t)0x04)
#define FXLS8974_SDCD_INT_SRC1_Y_OT_POL_SHIFT 		((uint8_t)2)

#define FXLS8974_SDCD_INT_SRC1_Y_OT_EF_MASK 		((uint8_t)0x08)
#define FXLS8974_SDCD_INT_SRC1_Y_OT_EF_SHIFT 		((uint8_t)3)

#define FXLS8974_SDCD_INT_SRC1_X_OT_POL_MASK 		((uint8_t)0x10)
#define FXLS8974_SDCD_INT_SRC1_X_OT_POL_SHIFT 		((uint8_t)4)

#define FXLS8974_SDCD_INT_SRC1_X_OT_EF_MASK 		((uint8_t)0x20)
#define FXLS8974_SDCD_INT_SRC1_X_OT_EF_SHIFT 		((uint8_t)5)

#define FXLS8974_SDCD_INT_SRC1_OT_EA_MASK 			((uint8_t)0x80)
#define FXLS8974_SDCD_INT_SRC1_OT_EA_SHIFT 			((uint8_t)7)

// SDCD_INT_SRC2 - Bit field mask definitions

#define FXLS8974_SDCD_INT_SRC2_Z_WT_EF_MASK 		((uint8_t)0x02)
#define FXLS8974_SDCD_INT_SRC2_Z_WT_EF_SHIFT 		((uint8_t)1)

#define FXLS8974_SDCD_INT_SRC2_Y_WT_EF_MASK 		((uint8_t)0x08)
#define FXLS8974_SDCD_INT_SRC2_Y_WT_EF_SHIFT 		((uint8_t)3)

#define FXLS8974_SDCD_INT_SRC2_X_WT_EF_MASK 		((uint8_t)0x20)
#define FXLS8974_SDCD_INT_SRC2_X_WT_EF_SHIFT 		((uint8_t)5)

#define FXLS8974_SDCD_INT_SRC2_WT_EA_MASK 			((uint8_t)0x80)
#define FXLS8974_SDCD_INT_SRC2_WT_EA_SHIFT 			((uint8_t)7)

// SDCD_CONFIG1 - Bit field mask definitions

#define FXLS8974_SDCD_CONFIG1_Z_WT_EN_MASK 			((uint8_t)0x01)
#define FXLS8974_SDCD_CONFIG1_Z_WT_EN_SHIFT 		((uint8_t)0)

#define FXLS8974_SDCD_CONFIG1_Y_WT_EN_MASK 			((uint8_t)0x02)
#define FXLS8974_SDCD_CONFIG1_Y_WT_EN_SHIFT 		((uint8_t)1)

#define FXLS8974_SDCD_CONFIG1_X_WT_EN_MASK 			((uint8_t)0x04)
#define FXLS8974_SDCD_CONFIG1_X_WT_EN_SHIFT 		((uint8_t)2)

#define FXLS8974_SDCD_CONFIG1_Z_OT_EN_MASK 			((uint8_t)0x08)
#define FXLS8974_SDCD_CONFIG1_Z_OT_EN_SHIFT 		((uint8_t)3)

#define FXLS8974_SDCD_CONFIG1_Y_OT_EN_MASK 			((uint8_t)0x10)
#define FXLS8974_SDCD_CONFIG1_Y_OT_EN_SHIFT 		((uint8_t)4)

#define FXLS8974_SDCD_CONFIG1_X_OT_EN_MASK 			((uint8_t)0x20)
#define FXLS8974_SDCD_CONFIG1_X_OT_EN_SHIFT 		((uint8_t)5)

#define FXLS8974_SDCD_CONFIG1_WT_ELE_MASK 			((uint8_t)0x40)
#define FXLS8974_SDCD_CONFIG1_WT_ELE_SHIFT 			((uint8_t)6)

#define FXLS8974_SDCD_CONFIG1_OT_ELE_MASK 			((uint8_t)0x80)
#define FXLS8974_SDCD_CONFIG1_OT_ELE_SHIFT 			((uint8_t)7)

// SDCD_CONFIG2 - Bit field mask definitions

#define FXLS8974_SDCD_CONFIG2_REF_UPD_MASK 			((uint8_t)0x01)
#define FXLS8974_SDCD_CONFIG2_REF_UPD_SHIFT 		((uint8_t)0)

#define FXLS8974_SDCD_CONFIG2_MODE_MASK 			((uint8_t)0x02)
#define FXLS8974_SDCD_CONFIG2_MODE_SHIFT 			((uint8_t)1)

#define FXLS8974_SDCD_CONFIG2_WT_LOG_SEL_MASK 		((uint8_t)0x04)
#define FXLS8974_SDCD_CONFIG2_WT_LOG_SEL_SHIFT 		((uint8_t)2)

#define FXLS8974_SDCD_CONFIG2_WT_DBCTM_MASK 		((uint8_t)0x08)
#define FXLS8974_SDCD_CONFIG2_WT_DBCTM_SHIFT 		((uint8_t)3)

#define FXLS8974_SDCD_CONFIG2_OT_DBCTM_MASK 		((uint8_t)0x10)
#define FXLS8974_SDCD_CONFIG2_OT_DBCTM_SHIFT 		((uint8_t)4)

#define FXLS8974_SDCD_CONFIG2_REF_UPDM_MASK 		((uint8_t)0x60)
#define FXLS8974_SDCD_CONFIG2_REF_UPDM_SHIFT 		((uint8_t)5)

#define FXLS8974_SDCD_CONFIG2_SDCD_EN_MASK 			((uint8_t)0x80)
#define FXLS8974_SDCD_CONFIG2_SDCD_EN_SHIFT 		((uint8_t)7)

// SELF_TEST_CONFIG1 - Bit field mask definitions

#define FXLS8974_SELF_TEST_CONFIG1_ST_IDLE_MASK 	((uint8_t)0x1f)
#define FXLS8974_SELF_TEST_CONFIG1_ST_IDLE_SHIFT 	((uint8_t)0)

// SELF_TEST_CONFIG2 - Bit field mask definitions

#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_MASK 		((uint8_t)0x0f)
#define FXLS8974_SELF_TEST_CONFIG2_ST_DEC_SHIFT 	((uint8_t)0)

// FXLS8974C registers map

enum
{

    FXLS8974_INT_STATUS = 0x00,
    FXLS8974_TEMP_OUT = 0x01,
    FXLS8974_VECM_LSB = 0x02,
    FXLS8974_VECM_MSB = 0x03,
    FXLS8974_OUT_X_LSB = 0x04,
    FXLS8974_OUT_X_MSB = 0x05,
    FXLS8974_OUT_Y_LSB = 0x06,
    FXLS8974_OUT_Y_MSB = 0x07,
    FXLS8974_OUT_Z_LSB = 0x08,
    FXLS8974_OUT_Z_MSB = 0x09,
    FXLS8974_BUF_STATUS = 0x0B,
    FXLS8974_BUF_X_LSB = 0x0C,
    FXLS8974_BUF_X_MSB = 0x0D,
    FXLS8974_BUF_Y_LSB = 0x0E,
    FXLS8974_BUF_Y_MSB = 0x0F,
    FXLS8974_BUF_Z_LSB = 0x10,
    FXLS8974_BUF_Z_MSB = 0x11,
    FXLS8974_PROD_REV = 0x12,
    FXLS8974_WHO_AM_I = 0x13,
    FXLS8974_SYS_MODE = 0x14,
    FXLS8974_SENS_CONFIG1 = 0x15,
    FXLS8974_SENS_CONFIG2 = 0x16,
    FXLS8974_SENS_CONFIG3 = 0x17,
    FXLS8974_SENS_CONFIG4 = 0x18,
    FXLS8974_SENS_CONFIG5 = 0x19,
    FXLS8974_WAKE_IDLE_LSB = 0x1A,
    FXLS8974_WAKE_IDLE_MSB = 0x1B,
    FXLS8974_SLEEP_IDLE_LSB = 0x1C,
    FXLS8974_SLEEP_IDLE_MSB = 0x1D,
    FXLS8974_ASLP_COUNT_LSB = 0x1E,
    FXLS8974_ASLP_COUNT_MSB = 0x1F,
    FXLS8974_INT_EN = 0x20,
    FXLS8974_INT_PIN_SEL = 0x21,
    FXLS8974_OFF_X = 0x22,
    FXLS8974_OFF_Y = 0x23,
    FXLS8974_OFF_Z = 0x24,
    FXLS8974_BUF_CONFIG1 = 0x26,
    FXLS8974_BUF_CONFIG2 = 0x27,
    FXLS8974_ORIENT_STATUS = 0x28,
    FXLS8974_ORIENT_CONFIG = 0x29,
    FXLS8974_ORIENT_DBCOUNT = 0x2A,
    FXLS8974_ORIENT_BF_ZCOMP = 0x2B,
    FXLS8974_ORIENT_THS_REG = 0x2C,
    FXLS8974_SDCD_INT_SRC1 = 0x2D,
    FXLS8974_SDCD_INT_SRC2 = 0x2E,
    FXLS8974_SDCD_CONFIG1 = 0x2F,
    FXLS8974_SDCD_CONFIG2 = 0x30,
    FXLS8974_SDCD_OT_DBCNT = 0x31,
    FXLS8974_SDCD_WT_DBCNT = 0x32,
    FXLS8974_SDCD_LTHS_LSB = 0x33,
    FXLS8974_SDCD_LTHS_MSB = 0x34,
    FXLS8974_SDCD_UTHS_LSB = 0x35,
    FXLS8974_SDCD_UTHS_MSB = 0x36,
    FXLS8974_SELF_TEST_CONFIG1 = 0x37,
    FXLS8974_SELF_TEST_CONFIG2 = 0x38,

};

// Interrupt & System status bit fields

typedef union
{

    struct
    {

        uint8_t src_boot : 1; 		// System boot complete event flag
        uint8_t src_aslp : 1; 		// Auto-Wake/Sleep event status flag
        uint8_t src_orient : 1; 	// Orientation change event flag
        uint8_t src_sdcd_wt : 1;	// SDCD within thresholds condition event flag
        uint8_t src_sdcd_ot : 1; 	// SDCD outside of threshold condition event flag
        uint8_t src_buf : 1;		// Output data buffer status event flag
        uint8_t src_ovf : 1; 		// Output data overflow event flag
        uint8_t src_drdy : 1; 		// Output data ready event flag

    }b;

    uint8_t w;

}FXLS8974_INT_STATUS_t;

// Sensor configuration reg1 bit fields

typedef union
{
    struct
    {

        uint8_t active : 1; 	    // Standby/Active mode selection
        uint8_t fsr : 2; 			// Full-scale measurement range (FSR) selection
        uint8_t spi_m : 1; 			// SPI interface mode selection; selects between 3- and 4-wire operating
                           	   	   	// modes for the SPI interface
        uint8_t st_pol : 1; 		// Self-Test Displacement Polarity
        uint8_t st_axis_sel : 2; 	// Self-Test Axis Selection
        uint8_t rst : 1;   			// The RST bit may be used to initiate a software reset

    }b;

    uint8_t w;

}FXLS8974_SENS_CONFIG1_t;

// Sensor configuration reg2 bit fields

typedef union
{

    struct
    {

        uint8_t f_read : 1; 		// Fast-read mode selection
        uint8_t anic_temp : 1; 		// Temperature output data auto-increment control
        uint8_t _reserved_ : 1;
        uint8_t le_be : 1; 			// Little/Big-endian output mode selection.
        uint8_t sleep_pm : 2; 		// SLEEP power mode selection
        uint8_t wake_pm : 2; 		// WAKE power mode selection

    }b;

    uint8_t w;

}FXLS8974_SENS_CONFIG2_t;

// Sensor configuration reg3 bit fields

typedef union
{

    struct
    {

        uint8_t sleep_odr : 4; 		// Sleep ODR
        uint8_t wake_odr : 4; 		//Wake ODR

    }b;

    uint8_t w;

}FXLS8974_SENS_CONFIG3_t;

// Sensor configuration reg4 bit fields

typedef union
{

    struct
    {

        uint8_t int_pol : 1; 		// Interrupt logic polarity on INT1 and INT2 pins
        uint8_t int_pp_od : 1; 		// INT1 and INT2 pins output driver selection
        uint8_t int2_func : 1; 		// INT2 output / EXT_TRIG input pin selection
        uint8_t drdy_pul : 1; 		// Pulse generation option for DRDY event
        uint8_t wk_orient : 1; 		// Orientation change event Auto-WAKE/SLEEP transition source enable
        uint8_t wk_sdcd_ot : 1; 	// SDCD outside of thresholds event Auto-WAKE/SLEEP transition source enable
        uint8_t wk_sdcd_wt : 1;    	// SDCD within thresholds event Auto-WAKE/SLEEP transition source enable
        uint8_t ext_trig_m : 1; 	// External trigger function acquisition mode

    }b;

    uint8_t w;

}FXLS8974_SENS_CONFIG4_t;

// Sensor configuration reg5 bit fields

typedef union
{

    struct
    {

        uint8_t hibernate_en : 1; 	// Hibernate mode enable
        uint8_t z_dis : 1; 			// Z-axis auto-increment disable
        uint8_t y_dis : 1; 			// Y-axis auto-increment disable
        uint8_t x_dis : 1; 			// X-axis auto-increment disable
        uint8_t vecm_en : 1; 		// Vector Magnitude calculation enable

    }b;

    uint8_t w;

}FXLS8974_SENS_CONFIG5_t;

// Interrupt enable register bit fields

typedef union
{

    struct
    {

        uint8_t wake_out_en : 1; 	//  WAKE power state output enable
        uint8_t boot_dis : 1; 		//  Boot interrupt output disable
        uint8_t aslp_en : 1; 		//  Auto-WAKE/SLEEP interrupt output enable
        uint8_t orient_en : 1; 		//  Orientation interrupt output enable
        uint8_t sdcd_wt_en : 1; 	//  SDCD within thresholds interrupt output enable
        uint8_t sdcd_ot_en : 1; 	// SDCD outside of thresholds interrupt output enable
        uint8_t buf_en : 1; 		// Output data buffer interrupt output enable
        uint8_t drdy_en : 1; 		//  Data Ready interrupt output enable

    }b;

    uint8_t w;

}FXLS8974_INT_EN_t;

// Interrupt pin select register bit fields

typedef union
{
    struct
    {

        uint8_t wk_out_int2 : 1; 	// WAKE power state interrupt routing
        uint8_t boot_int2 : 1; 		// BOOT event interrupt routing
        uint8_t aslp_int2 : 1; 		// Auto-WAKE/SLEEP event interrupt routing
        uint8_t orient_int2 : 1; 	// ORIENT event interrupt routing
        uint8_t sdcd_wt_int2 : 1; 	// SDCD within thresholds event interrupt routing
        uint8_t sdcd_ot_int2 : 1; 	// SDCD outside of thresholds event interrupt routing
        uint8_t buf_int2 : 1; 		// Output buffer interrupt routing
        uint8_t drdy_int2 : 1; 		// Data Ready interrupt routing

    }b;

    uint8_t w;

}FXLS8974_INT_PIN_SEL_t;

// Buffer configuration reg1 bit fields

typedef union
{

    struct
	{

        uint8_t trg_orient : 1; 	// Orientation change event trigger enable
        uint8_t _reserved_ : 1;
        uint8_t trg_sdcd_ot : 1; 	// SDCD outside-of-thresholds event buffer trigger enable
        uint8_t trg_sdcd_wt : 1; 	// SDCD within-thresholds event trigger enable
        uint8_t buf_gate : 1; 		// Output data buffer gate enable
        uint8_t buf_mode : 2; 		// Buffer data collection mode
        uint8_t buf_type : 1; 		// Buffer data read out order

    }b;

    uint8_t w;

}FXLS8974_BUF_CONFIG1_t;

// Buffer configuration reg2 bit fields

typedef union
{

    struct
	{

        uint8_t buf_wmrk : 6; 		// Buffer sample count watermark
        uint8_t wake_src_buf : 1; 	// Buffer WAKE-to-SLEEP transition source enable
        uint8_t buf_flush : 1; 		// Buffer flush enable

    }b;

    uint8_t w;

}FXLS8974_BUF_CONFIG2_t;

// Orientation status register bit fields

typedef union
{
    struct
    {

        uint8_t bafro : 1; 			// Back or front orientation
        uint8_t lapo : 2; 			// Landscape/Portrait orientation
        uint8_t _reserved_ : 3;
        uint8_t lo : 1; 			// Z-tilt angle lockout
        uint8_t new_orient : 1; 	// Orientation status change flag

    }b;

    uint8_t w;

}FXLS8974_ORIENT_STATUS_t;

// Orientation configuration register bit fields

typedef union
{

    struct
    {

        uint8_t _reserved_ : 6;
        uint8_t orient_enable : 1; 	// Orientation detection function enable
        uint8_t orient_dbcntm : 1; 	//  Orientation debounce counter mode selection

    }b;

    uint8_t w;

}FXLS8974_ORIENT_CONFIG_t;

// Orientation BF z component register bit fields

typedef union
{
    struct
    {

        uint8_t orient_zlock : 3; 	// Z-lock out angle threshold
        uint8_t _reserved_ : 3;
        uint8_t orient_bkfr : 2; 	// Back-Up / Front-Up trip angle threshold

    }b;

    uint8_t w;

}FXLS8974_ORIENT_BF_ZCOMP_t;

// Orientation threshold register bit fields

typedef union
{

    struct
    {

        uint8_t hys : 3; 			// ORIENT_HYS[2:0]
        uint8_t orient_ths : 5; 	// ORIENT_THS[4:0] value

    }b;

    uint8_t w;

}FXLS8974_ORIENT_THS_REG_t;

// Sensor data change detection function 1 register bit fields

typedef union
{

    struct
    {

        uint8_t z_ot_pol : 1; 		// Z-axis outside of thresholds polarity flag
        uint8_t z_ot_ef : 1; 		// Z-axis data or delta outside of upper and lower thresholds event flag
        uint8_t y_ot_pol : 1; 		// Y-axis outside of thresholds polarity flag
        uint8_t y_ot_ef : 1; 		// Y-axis data or delta outside of upper and lower thresholds event flag
        uint8_t x_ot_pol : 1; 		// X-axis outside of thresholds polarity flag
        uint8_t x_ot_ef : 1; 		// X-axis data or delta outside of upper and lower thresholds event flag
        uint8_t _reserved_ : 1;
        uint8_t ot_ea : 1; 			// SDCD outside of thresholds event active flag

    }b;

    uint8_t w;

}FXLS8974_SDCD_INT_SRC1_t;

// Sensor data change detection function 2 register bit fields

typedef union
{

    struct
    {

        uint8_t _reserved_ : 1;
        uint8_t z_wt_ef : 1; 		// Z-axis data or delta inside of upper and lower thresholds event flag
        uint8_t _reserved_1 : 1;
        uint8_t y_wt_ef : 1; 		// Y-axis data or delta inside of upper and lower thresholds event flag
        uint8_t _reserved_2 : 1;
        uint8_t x_wt_ef : 1; 		// X-axis data or delta inside of upper and lower thresholds event flag
        uint8_t _reserved_3 : 1;
        uint8_t wt_ea : 1; 			// SDCD within-thresholds event active flag

    }b;

    uint8_t w;

}FXLS8974_SDCD_INT_SRC2_t;

// Sensor data change detection function 1 register bit fields

typedef union
{

    struct
    {

        uint8_t z_wt_en : 1; 		// SDCD function Z-axis within thresholds condition enable
        uint8_t y_wt_en : 1; 		// SDCD function Y-axis within thresholds condition enable
        uint8_t x_wt_en : 1; 		// SDCD function X-axis within thresholds condition enable
        uint8_t z_ot_en : 1; 		// SDCD function Z-axis outside of thresholds condition enable
        uint8_t y_ot_en : 1; 		// SDCD function Y-axis outside of thresholds condition enable
        uint8_t x_ot_en : 1; 		// SDCD function X-axis outside of thresholds condition enable
        uint8_t wt_ele : 1; 		// SDCD within thresholds event latch enable
        uint8_t ot_ele : 1; 		// SDCD outside of thresholds event latch enable

    }b;

    uint8_t w;

}FXLS8974_SDCD_CONFIG1_t;

// Sensor data change detection function 2 register bit fields

typedef union
{

    struct
    {

        uint8_t ref_upd : 1; 		// SDCD synchronous X/Y/Z reference values update bit
        uint8_t mode : 1; 			// SDCD input data mode
        uint8_t wt_log_sel : 1; 	// SDCD within thresholds event logic selection
        uint8_t wt_dbctm : 1; 		// SDCD within thresholds event debounce counter behavior
        uint8_t ot_dbctm : 1; 		// SDCD outside of threshold event debounce counter behavior
        uint8_t ref_updm : 2; 		// SDCD internal reference values update mode
        uint8_t sdcd_en : 1; 		// SDCD function

    }b;

    uint8_t w;

}FXLS8974_SDCD_CONFIG2_t;

// Self Test Configuration function 1 register bit fields

typedef union
{
    struct
    {

        uint8_t st_idle : 5; 		// Self-Test Idle phase duration

    }b;

    uint8_t w;

}FXLS8974_SELF_TEST_CONFIG1_t;

// Self Test Configuration function 2 register bit fields

typedef union
{

    struct
    {

        uint8_t st_dec : 4; 		// Self-Test measurement phase decimation factor

    }b;

    uint8_t w;

}FXLS8974_SELF_TEST_CONFIG2_t;

// Axis acceleration data structure

typedef union
{

	struct
	{

		uint8_t lsb : 8;
		uint8_t msb : 4;
		uint8_t reserved : 4;

	}b;

	uint8_t arr[2];
	uint16_t w;

}axis_u;

typedef struct
{

	axis_u x;
	axis_u y;
	axis_u z;

}axis_accel;

// I2C communication data structure

typedef struct
{

	I2C_HandleTypeDef *pI2C_instance;
	uint16_t slaveAddress;
    uint8_t (*pI2C_data_Tx)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t timeOut);
    uint8_t (*pI2C_data_Rx)(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t timeOut);
    uint8_t data_reg;
    axis_accel axis_data;

}fxls8974_i2c_sensorhandle_t;

// Raw data structure

typedef struct
{

    uint32_t timestamp; 			// The time, this sample was recorded
    int16_t accel[3];   			// The accel data

}fxls8974_acceldata_t;

// Global function prototypes

int FXLS8974_I2C_Init(fxls8974_i2c_sensorhandle_t *pSensorHandle, void *instance, void *pI2C_funTx, void *pI2C_funRx, uint16_t sAddress, uint8_t *whoami);
int FXLS8974_I2C_Configure(fxls8974_i2c_sensorhandle_t *pSensorHandle);
int FXLS8974_I2C_ReadData(fxls8974_i2c_sensorhandle_t *pSensorHandle);
int FXLS8974_I2C_DeInit(fxls8974_i2c_sensorhandle_t *pSensorHandle);

#endif /* INC_FXLS8974C_H_ */
