/*
 * FXLS8974C.c
 *
 *  Created on: Jan 11, 2025
 *      Author: Fato
 */

#include "FXLS8974C.h"

// Definitions

#define REG_SET(val, shift)				( val << shift )

// Global Variables

// Private Function prototypes

static int i2c_register_set(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t val, uint8_t mask, uint8_t shift);
static int i2c_register_get(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t *reg_data);

// Global Functions

int FXLS8974_I2C_Init(fxls8974_i2c_sensorhandle_t *pSensorHandle, void *instance, void *pI2C_funTx, void *pI2C_funRx, uint16_t sAddress, uint8_t *whoami)
{

    int32_t status;


    /*! Check the input parameters. */
    if(( pSensorHandle == NULL ) || ( instance == NULL ) || ( pI2C_funTx == NULL ) || ( pI2C_funRx == NULL ))
        return 0;

    pSensorHandle->pI2C_instance = instance;
    pSensorHandle->pI2C_data_Tx = pI2C_funTx;
    pSensorHandle->pI2C_data_Rx = pI2C_funRx;
    pSensorHandle->slaveAddress = sAddress;

    // Read and store the device's WHO_AM_I
    status = i2c_register_get(pSensorHandle, FXLS8974_WHO_AM_I, &pSensorHandle->data_reg);
    if(HAL_OK != status)
        return 0;

    (*whoami) = pSensorHandle->data_reg;

    if(FXLS8974_WHOAMI_VALUE != pSensorHandle->data_reg)
    	return 0;

    return 1;

}

int FXLS8974_I2C_Configure(fxls8974_i2c_sensorhandle_t *pSensorHandle)
{

    int32_t status;


    // Validate for the correct handle and register write list
    if(pSensorHandle == NULL)
        return 0;

    // Put the device into standby mode so that configuration can be applied
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ACTIVE_STANDBY, FXLS8974_SENS_CONFIG1_ACTIVE_MASK, 0);
    if(1 != status)
        return 0;

    // Set Full-scale range as 4G
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_4G, FXLS8974_SENS_CONFIG1_FSR_MASK, 0);
    if(1 != status)
        return 0;

    // Set Wake ODR as 100Hz & Sleep Mode ODR as 100Hz
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG3, ( FXLS8974_SENS_CONFIG3_WAKE_ODR_100HZ | FXLS8974_SENS_CONFIG3_SLEEP_ODR_100HZ ), ( FXLS8974_SENS_CONFIG3_WAKE_ODR_MASK | FXLS8974_SENS_CONFIG3_SLEEP_ODR_MASK ), 0);
    if(1 != status)
        return 0;

    // Enable SDCD OT for only X axis and outside-thresholds event latch disabled
	status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_CONFIG1, FXLS8974_SDCD_CONFIG1_X_OT_EN_EN, FXLS8974_SDCD_CONFIG1_X_OT_EN_MASK, 0);
	if(1 != status)
		return 0;

	// Enable SDCD function, Enable Absolute Reference Mode and set OT debounce counter to clear immediately when threshold criteria is false
	status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_CONFIG2, ( FXLS8974_SDCD_CONFIG2_SDCD_EN_EN | FXLS8974_SDCD_CONFIG2_REF_UPDM_FIXED_VAL | FXLS8974_SDCD_CONFIG2_OT_DBCTM_CLEARED ), ( FXLS8974_SDCD_CONFIG2_SDCD_EN_MASK | FXLS8974_SDCD_CONFIG2_REF_UPDM_MASK | FXLS8974_SDCD_CONFIG2_OT_DBCTM_MASK ), 0);
	if(1 != status)
		return 0;

	// Set the SDCD_OT debounce count to 6
	status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_OT_DBCNT, 0x06, 0xff, 0);
	if(1 != status)
		return 0;

	// Set the SDCD lower and upper thresholds to +/-2.5g
	status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_LTHS_LSB, 0xfe, 0xff, 0);
	status &= i2c_register_set(pSensorHandle, FXLS8974_SDCD_LTHS_MSB, 0xfa, 0xff, 0);
	status &= i2c_register_set(pSensorHandle, FXLS8974_SDCD_UTHS_LSB, 0x02, 0xff, 0);
	status &= i2c_register_set(pSensorHandle, FXLS8974_SDCD_UTHS_MSB, 0x05, 0xff, 0);
	if(1 != status)
		return 0;

	// Enable SDCD outside of thresholds event Auto-WAKE/SLEEP transition source enable
	status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG4, ( FXLS8974_SENS_CONFIG4_WK_SDCD_OT_EN | FXLS8974_SENS_CONFIG4_INT_POL_ACT_HIGH ), ( FXLS8974_SENS_CONFIG4_WK_SDCD_WT_MASK | FXLS8974_SENS_CONFIG4_INT_POL_MASK ), 0);
	if(1 != status)
		return 0;

	// Set the ASLP count to 5sec
	status = i2c_register_set(pSensorHandle, FXLS8974_ASLP_COUNT_LSB, 0x3f, 0xff, 0);
	status &= i2c_register_set(pSensorHandle, FXLS8974_ASLP_COUNT_MSB, 0x02, 0xff, 0);
	if(1 != status)
		return 0;

    // Enable Interrupts for WAKE mode
	status = i2c_register_set(pSensorHandle, FXLS8974_INT_EN, FXLS8974_INT_EN_WAKE_OUT_EN_EN, FXLS8974_INT_EN_WAKE_OUT_EN_MASK, 0);
	status &= i2c_register_set(pSensorHandle, FXLS8974_INT_PIN_SEL, FXLS8974_INT_PIN_SEL_WK_OUT_INT2_DIS, FXLS8974_INT_PIN_SEL_WK_OUT_INT2_MASK, 0);
	if(1 != status)
		return 0;

    // Put the device into active mode and ready for reading data
	status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ACTIVE_ACTIVE, FXLS8974_SENS_CONFIG1_ACTIVE_MASK, 0);
	if(1 != status)
		return 0;

    return 1;

}

int FXLS8974_I2C_ReadData(fxls8974_i2c_sensorhandle_t *pSensorHandle)
{

    int32_t status;


    // Validate for the correct handle and register read list
    if(pSensorHandle == NULL)
        return 0;

    // Read the system mode register
    status = i2c_register_get(pSensorHandle, FXLS8974_SYS_MODE, &pSensorHandle->data_reg);
	if(1 != status)
		return 0;

    // Read X axis data
    status = i2c_register_get(pSensorHandle, FXLS8974_OUT_X_LSB, &pSensorHandle->axis_data.x.arr[0]);
    status &= i2c_register_get(pSensorHandle, FXLS8974_OUT_X_MSB, &pSensorHandle->axis_data.x.arr[1]);
	if(1 != status)
		return 0;

    // Read Y axis data
    status = i2c_register_get(pSensorHandle, FXLS8974_OUT_Y_LSB, &pSensorHandle->axis_data.y.arr[0]);
    status &= i2c_register_get(pSensorHandle, FXLS8974_OUT_Y_MSB, &pSensorHandle->axis_data.y.arr[1]);
	if(1 != status)
		return 0;

    // Read Z axis data
    status = i2c_register_get(pSensorHandle, FXLS8974_OUT_Z_LSB, &pSensorHandle->axis_data.z.arr[0]);
    status &= i2c_register_get(pSensorHandle, FXLS8974_OUT_Z_MSB, &pSensorHandle->axis_data.z.arr[1]);
	if(1 != status)
		return 0;

    return 1;

}

int FXLS8974_I2C_DeInit(fxls8974_i2c_sensorhandle_t *pSensorHandle)
{

    int32_t status;


    if (pSensorHandle == NULL)
        return 0;

    // Trigger sensor device reset
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_RST_RST, FXLS8974_SENS_CONFIG1_RST_MASK, 0);
    if (1 != status)
        return 0;

    // Wait for MAX of TBOOT ms after soft reset command,
    // to allow enough time for FXLS8974AF to complete its internal boot sequence and be ready for communication
    HAL_Delay(FXLS8974_TBOOT_MAX);

    return 1;

}

// Private Functions

static int i2c_register_set(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t val, uint8_t mask, uint8_t shift)
{

	uint8_t data_buff[2];
	uint8_t reg_data;
	uint8_t status;


	reg_data = ( REG_SET(val, shift) & mask );

	data_buff[0] = reg_addr;
	data_buff[1] = reg_data;

    status = pSensorHandle->pI2C_data_Tx(pSensorHandle->pI2C_instance, pSensorHandle->slaveAddress, data_buff, 2, HAL_MAX_DELAY);
    if(HAL_OK != status)
        return 0;

    return 1;

}

static int i2c_register_get(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t *reg_data)
{

	uint8_t status;


    status = pSensorHandle->pI2C_data_Tx(pSensorHandle->pI2C_instance, pSensorHandle->slaveAddress, &reg_addr, 1, HAL_MAX_DELAY);
    status &= pSensorHandle->pI2C_data_Rx(pSensorHandle->pI2C_instance, pSensorHandle->slaveAddress, reg_data, 1, HAL_MAX_DELAY);
    if(HAL_OK != status)
        return 0;

    return 1;

}
