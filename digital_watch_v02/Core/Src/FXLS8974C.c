/*
 * FXLS8974C.c
 *
 *  Created on: Jan 11, 2025
 *      Author: Fato
 */

/* Includes ------------------------------------------------------------------*/

#include "FXLS8974C.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define MAX_ITERATIONS_NUM 1000000
#define REG_SET(val, shift) (val << shift)

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/** @brief I2C transmission complete flag */
volatile uint8_t i2c_tx_cplt = 0;
/** @brief I2C receive complete flag */
volatile uint8_t i2c_rx_cplt = 0;
/** @brief I2C repeated start flag */
volatile uint8_t i2c_repeated_start = 0;

/* Private function prototypes -----------------------------------------------*/

/** @brief i2c_register_set */
static int i2c_register_set(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t val, uint8_t mask, uint8_t shift);
/** @brief i2c_register_get */
static int i2c_register_get(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t *reg_data);

/* External functions --------------------------------------------------------*/

/**
 * @brief FXLS8974_I2C_Init
 *
 * @param pSensorHandle
 * @param instance
 * @param pI2C_funTx
 * @param pI2C_funRx
 * @param sAddress
 * @return int
 */
int FXLS8974_I2C_Init(fxls8974_i2c_sensorhandle_t *pSensorHandle, void *instance, void *pI2C_funTx, void *pI2C_funRx, uint16_t sAddress)
{
    int32_t status;
    uint8_t whoami;

    /* Check the input parameters */
    if ((pSensorHandle == NULL) || (instance == NULL) || (pI2C_funTx == NULL) || (pI2C_funRx == NULL))
        return 0;

    /* Assigne I2C interfaces */
    pSensorHandle->pI2C_instance = instance;
    pSensorHandle->pI2C_data_Tx = pI2C_funTx;
    pSensorHandle->pI2C_data_Rx = pI2C_funRx;
    pSensorHandle->slaveAddress = sAddress;

    /* Read and store the device's WHO_AM_I */
    status = i2c_register_get(pSensorHandle, FXLS8974_WHO_AM_I, &pSensorHandle->data_reg);
    if (1 != status)
        return 0;

    whoami = pSensorHandle->data_reg;
    if (FXLS8974_WHOAMI_VALUE != whoami)
        return 0;

    return 1;
}

/**
 * @brief FXLS8974_I2C_Configure
 *
 * @param pSensorHandle
 * @return int
 */
int FXLS8974_I2C_Configure(fxls8974_i2c_sensorhandle_t *pSensorHandle)
{
    int32_t status;

    /* Validate for the correct handle and register write list */
    if (pSensorHandle == NULL)
        return 0;

    /* Put the device into standby mode so that configuration can be applied */
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ACTIVE_STANDBY, FXLS8974_SENS_CONFIG1_ACTIVE_MASK, 0);
    if (1 != status)
        return 0;

    /* Set Wake ODR as 100Hz & Sleep Mode ODR as 100Hz */
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG3, (FXLS8974_SENS_CONFIG3_WAKE_ODR_100HZ | FXLS8974_SENS_CONFIG3_SLEEP_ODR_100HZ), (FXLS8974_SENS_CONFIG3_WAKE_ODR_MASK | FXLS8974_SENS_CONFIG3_SLEEP_ODR_MASK), 0);
    if (1 != status)
        return 0;

    /* Enable SDCD OT for only Y axis and outside-thresholds event latch disabled */
    status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_CONFIG1, FXLS8974_SDCD_CONFIG1_Y_OT_EN_EN, FXLS8974_SDCD_CONFIG1_Y_OT_EN_MASK, 0);
    if (1 != status)
        return 0;

    /* Enable SDCD function, Enable Absolute Reference Mode and set OT debounce counter to clear immediately when threshold criteria is false */
    status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_CONFIG2, (FXLS8974_SDCD_CONFIG2_SDCD_EN_EN | FXLS8974_SDCD_CONFIG2_REF_UPDM_FIXED_VAL | FXLS8974_SDCD_CONFIG2_OT_DBCTM_CLEARED), (FXLS8974_SDCD_CONFIG2_SDCD_EN_MASK | FXLS8974_SDCD_CONFIG2_REF_UPDM_MASK | FXLS8974_SDCD_CONFIG2_OT_DBCTM_MASK), 0);
    if (1 != status)
        return 0;

    /* Set the SDCD_OT debounce count to 6 */
    status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_OT_DBCNT, 0x06, 0xff, 0);
    if (1 != status)
        return 0;

    /* Set the SDCD lower and upper thresholds to +0.768g and +1.280g */
    status = i2c_register_set(pSensorHandle, FXLS8974_SDCD_LTHS_LSB, 0x00, 0xff, 0);
    status &= i2c_register_set(pSensorHandle, FXLS8974_SDCD_LTHS_MSB, 0x03, 0xff, 0);
    status &= i2c_register_set(pSensorHandle, FXLS8974_SDCD_UTHS_LSB, 0x00, 0xff, 0);
    status &= i2c_register_set(pSensorHandle, FXLS8974_SDCD_UTHS_MSB, 0x05, 0xff, 0);
    if (1 != status)
        return 0;

    /* Set the interrupt signal polarity */
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG4, (FXLS8974_SENS_CONFIG4_INT_POL_ACT_HIGH), (FXLS8974_SENS_CONFIG4_INT_POL_MASK), 0);
    if (1 != status)
        return 0;

    /* Set the ASLP count to 5sec */
    status = i2c_register_set(pSensorHandle, FXLS8974_ASLP_COUNT_LSB, 0x3f, 0xff, 0);
    status &= i2c_register_set(pSensorHandle, FXLS8974_ASLP_COUNT_MSB, 0x02, 0xff, 0);
    if (1 != status)
        return 0;

    /* Enable Interrupt for SDCD out-of-threshold event */
    status = i2c_register_set(pSensorHandle, FXLS8974_INT_EN, FXLS8974_INT_EN_SDCD_OT_EN_EN, FXLS8974_INT_EN_SDCD_OT_EN_MASK, 0);
    if (1 != status)
        return 0;

    /* Put the device into active mode and ready for reading data */
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ACTIVE_ACTIVE, FXLS8974_SENS_CONFIG1_ACTIVE_MASK, 0);
    if (1 != status)
        return 0;

    return 1;
}

/**
 * @brief FXLS8974_I2C_ReadData
 *
 * @param pSensorHandle
 * @return int
 */
int FXLS8974_I2C_ReadData(fxls8974_i2c_sensorhandle_t *pSensorHandle)
{
    int32_t status;

    /* Validate for the correct handle and register read list */
    if (pSensorHandle == NULL)
        return 0;

    /* Read the system mode register */
    status = i2c_register_get(pSensorHandle, FXLS8974_SYS_MODE, &pSensorHandle->data_reg);
    if (1 != status)
        return 0;

    /* Read X axis data */
    status = i2c_register_get(pSensorHandle, FXLS8974_OUT_X_LSB, &pSensorHandle->axis_data.x.arr[0]);
    status &= i2c_register_get(pSensorHandle, FXLS8974_OUT_X_MSB, &pSensorHandle->axis_data.x.arr[1]);
    if (1 != status)
        return 0;

    /* Read Y axis data */
    status = i2c_register_get(pSensorHandle, FXLS8974_OUT_Y_LSB, &pSensorHandle->axis_data.y.arr[0]);
    status &= i2c_register_get(pSensorHandle, FXLS8974_OUT_Y_MSB, &pSensorHandle->axis_data.y.arr[1]);
    if (1 != status)
        return 0;

    /* Read Z axis data */
    status = i2c_register_get(pSensorHandle, FXLS8974_OUT_Z_LSB, &pSensorHandle->axis_data.z.arr[0]);
    status &= i2c_register_get(pSensorHandle, FXLS8974_OUT_Z_MSB, &pSensorHandle->axis_data.z.arr[1]);
    if (1 != status)
        return 0;

    return 1;
}

/**
 * @brief FXLS8974_I2C_Read_Int_status
 *
 * @param pSensorHandle
 */
void FXLS8974_I2C_Read_Int_status(fxls8974_i2c_sensorhandle_t *pSensorHandle)
{
    i2c_register_get(pSensorHandle, FXLS8974_SDCD_INT_SRC1, &pSensorHandle->data_reg);
}

/**
 * @brief FXLS8974_I2C_DeInit
 *
 * @param pSensorHandle
 * @return int
 */
int FXLS8974_I2C_DeInit(fxls8974_i2c_sensorhandle_t *pSensorHandle)
{
    int32_t status;

    if (pSensorHandle == NULL)
        return 0;

    /* Trigger sensor device reset */
    status = i2c_register_set(pSensorHandle, FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_RST_RST, FXLS8974_SENS_CONFIG1_RST_MASK, 0);
    if (1 != status)
        return 0;

    /* Wait for MAX of TBOOT ms after soft reset command,
     * to allow enough time for FXLS8974AF to complete its internal boot sequence and be ready for communication
     */
    HAL_Delay(FXLS8974_TBOOT_MAX);

    return 1;
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief i2c_register_set
 *
 * @param pSensorHandle
 * @param reg_addr
 * @param val
 * @param mask
 * @param shift
 * @return int
 */
static int i2c_register_set(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t val, uint8_t mask, uint8_t shift)
{
    uint8_t data_buff[2];
    uint8_t reg_data;
    uint8_t status;

    reg_data = (REG_SET(val, shift) & mask);

    data_buff[0] = reg_addr;
    data_buff[1] = reg_data;

    status = pSensorHandle->pI2C_data_Tx(pSensorHandle->pI2C_instance, pSensorHandle->slaveAddress, data_buff, 2, I2C_LAST_FRAME);
    if (HAL_OK != status)
        return 0;

    i2c_tx_cplt = 0;

    HAL_Delay(100);

    return 1;
}

/**
 * @brief i2c_register_get
 *
 * @param pSensorHandle
 * @param reg_addr
 * @param reg_data
 * @return int
 */
static int i2c_register_get(fxls8974_i2c_sensorhandle_t *pSensorHandle, uint8_t reg_addr, uint8_t *reg_data)
{
    uint8_t status;
    uint32_t count_iter = 0;

    i2c_repeated_start = 1;
    status = pSensorHandle->pI2C_data_Tx(pSensorHandle->pI2C_instance, pSensorHandle->slaveAddress, &reg_addr, 1, I2C_FIRST_FRAME);
    if (HAL_OK != status)
        return 0;

    while (i2c_repeated_start)
    {

        count_iter++;
        if (count_iter > MAX_ITERATIONS_NUM)
            return 0;
    }

    status = pSensorHandle->pI2C_data_Rx(pSensorHandle->pI2C_instance, pSensorHandle->slaveAddress, reg_data, 1, I2C_LAST_FRAME);
    if (HAL_OK != status)
        return 0;

    i2c_rx_cplt = 0;

    HAL_Delay(100);

    return 1;
}

/* CallBack functions --------------------------------------------------------*/

/**
 * @brief HAL_I2C_MasterTxCpltCallback
 *
 * @param hi2c
 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    i2c_tx_cplt = 1;

    if (i2c_repeated_start == 1)
        i2c_repeated_start = 0;
}

/**
 * @brief HAL_I2C_MasterRxCpltCallback
 *
 * @param hi2c
 */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    i2c_rx_cplt = 1;
}
