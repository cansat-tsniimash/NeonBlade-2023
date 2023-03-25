#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nRF24L01_PL/nrf24_upper_api.h"
#include "nRF24L01_PL/nrf24_lower_api_stm32.h"
#include "nRF24L01_PL/nrf24_lower_api.h"
#include "main.h"



extern SPI_HandleTypeDef hspi2;


#define DA1_NRF_ADDR (0xcfcfcfcfcf)
#define DA2_NRF_ADDR (DA1_NRF_ADDR + 1)
#define DA3_NRF_ADDR (DA1_NRF_ADDR + 2)

typedef enum//ОПИСЫВАЕМ ОБЩЕНИЕ ПО РАДИО
{

    STATE_BUILD_PACKET_MA_1_TO_GCS,
	STATE_BUILD_PACKET_MA_2_TO_GCS,
	STATE_BUILD_PACKET_TO_DA_1,
	STATE_SEND,
	STATE_WRITE_DA_PACKET_TO_GCS,
	STATE_BUILD_PACKET_TO_DA_2,
	STATE_BUILD_PACKET_TO_DA_3,
	STATE_CHILL
}nrf24_state_t;

typedef enum//ОПИСЫВАЕМ СОСТОЯНИЕ ПОЛЕТА
{
	STATE_INIT,
	STATE_ON_GROUND,
	STATE_WAIT,
	STATE_IN_RN,
	STATE_UNDIRECTED_FREE_FALL,
	STATE_DIRECTED_FREE_FALL,
	STATE_SKIRT_FOLDING,
	STATE_PARACHUTE_DESCENT,
	STATE_OPENING_OF_THE_SKIRT,
	STATE_MINOR_DEVICE_SEPARATION,
	STATE_LIFTING_THE_OPTICAL_MODULE,
    STATE_ENABLING_THE_SEARCH_ENGINE
}state_t;

#pragma pack(push,1)
typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;

	float BME280_pressure;
	float BME280_temperature;

	int16_t DS18B20_temperature;

    float latitude;
    float longitude;
    int16_t height;
    uint16_t cookie;
    uint8_t fix;

	uint16_t sum;

}packet_ma_type_1_t;

typedef struct
{
	uint8_t flag;
	uint16_t num;
	uint32_t time;


	int16_t acc_mg [3];

    int16_t gyro_mdps [3];

    int16_t LIS3MDL_magnetometer[3];

    float phortsistor;

    uint8_t state;

	uint16_t sum;
}packet_ma_type_2_t;




int app_main()
{

	packet_ma_type_1_t packet_ma_type_1 = {1};
//	packet_ma_type_2_t packet_ma_type_2 = {0};
/*
	struct bme280_dev bme = {0};	//инициализируем настройки бме280
	struct bme_spi_intf spi_intf;
	spi_intf.GPIO_Port = GPIOC;
	spi_intf.GPIO_Pin = GPIO_PIN_13;
	spi_intf.spi = &hspi2;
	bme_init_default(&bme, &spi_intf);
	float pressure_on_ground;


	struct bme280_data comp_data = {0};
	float height_on_BME280;

	comp_data = bme_read_data(&bme);
    pressure_on_ground = (float)comp_data.pressure;
    for(int i = 0; pressure_on_ground < 90000; i++)
    {
    	comp_data = bme_read_data(&bme);
        pressure_on_ground = (float)comp_data.pressure;
    }
*/

    /*
	//заполнение структуры на фоторезистор
	photorezistor_t photoresistor;
	//сопротивление (R)
	photoresistor.resist = 2000;
	//hadc1 - дискриптор с начтройками АЦП
	photoresistor.hadc = &hadc1;

	float temp_lis;
	float mag[3];
	stmdev_ctx_t ctx = {0};
    struct lis_spi_intf lis_spi;
	lis_spi.GPIO_Port = GPIOC;
	lis_spi.GPIO_Pin = GPIO_PIN_14;
	lis_spi.spi = &hspi2;

	lisset(&ctx, &lis_spi);

	float temperature_celsius_gyro;
	float acc_g[3];
	float gyro_dps[3];

	stmdev_ctx_t ctx = {0};
	struct lsm_spi_intf lsm_spi;
	lsm_spi.GPIO_Port = GPIOC;
	lsm_spi.GPIO_Pin = GPIO_PIN_15;
	lsm_spi.spi = &hspi2;

	lsmset(&ctx, &lsm_spi);*/

	//Создаем и настраиваем дескриптор радиомодуля nRF24L01
	nrf24_spi_pins_t nrf24_spi_pins;
	nrf24_spi_pins.ce_pin = GPIO_PIN_9;
	nrf24_spi_pins.ce_port = GPIOB;
	nrf24_spi_pins.cs_pin = GPIO_PIN_8;
	nrf24_spi_pins.cs_port = GPIOB;
	nrf24_lower_api_config_t nrf24_api_config;
	nrf24_spi_init(&nrf24_api_config, &hspi2, &nrf24_spi_pins);

	//Перед настройкой регистров радио переводим его в standby mode
	nrf24_mode_standby(&nrf24_api_config);

	// Настраиваем параметры радиопередачи
	nrf24_rf_config_t nrf24_rf_config;
	nrf24_rf_config.data_rate = NRF24_DATARATE_2000_KBIT;
	nrf24_rf_config.rf_channel = 100;
	nrf24_rf_config.tx_power = NRF24_TXPOWER_MINUS_0_DBM;
	nrf24_setup_rf(&nrf24_api_config, &nrf24_rf_config);

	// Настраиваем протокол радиопередачи
	nrf24_protocol_config_t nrf24_protocol_config;
	nrf24_protocol_config.address_width = NRF24_ADDRES_WIDTH_5_BYTES;
	nrf24_protocol_config.auto_retransmit_count = 15;
	nrf24_protocol_config.auto_retransmit_delay = 15;
	nrf24_protocol_config.crc_size = NRF24_CRCSIZE_1BYTE;
	nrf24_protocol_config.en_ack_payload = true;
	nrf24_protocol_config.en_dyn_ack = false;
	nrf24_protocol_config.en_dyn_payload_size = false;
	nrf24_setup_protocol(&nrf24_api_config, &nrf24_protocol_config);


	//Настраиваем пайп 0 для приема
	nrf24_pipe_config_t pipe_config;
	pipe_config.enable_auto_ack = true;
	pipe_config.payload_size = 32;
	pipe_config.address = DA1_NRF_ADDR;
	nrf24_pipe_rx_start(&nrf24_api_config, 0, &pipe_config);



	int16_t er_rf_wr = 0;
	uint8_t status;

	uint8_t rx_buffer[32] = {0};
//	uint8_t tx_buffer[32] = {0};

	nrf24_fifo_status_t rx_status = 0;
    nrf24_fifo_status_t tx_status = 0;
    nrf24_irq_clear(&nrf24_api_config, NRF24_IRQ_TX_DR | NRF24_IRQ_RX_DR |NRF24_IRQ_MAX_RT);
    nrf24_fifo_flush_rx(&nrf24_api_config);
    nrf24_fifo_flush_tx(&nrf24_api_config);
    nrf24_mode_rx(&nrf24_api_config);

    //Переводим радио в режим передачи
	/*nrf24_mode_tx(&nrf24_api_config);

	nrf24_pipe_set_tx_addr(&nrf24_api_config, DA1_NRF_ADDR);
	er_rf_wr = nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), true);
	*/

	int IRQ_flags;
	uint8_t packet_size;
	uint8_t rx_pipe_no;
	bool tx_full;

	while(1)
	{
	    nrf24_fifo_flush_tx(&nrf24_api_config);
		nrf24_write_ack_payload(&nrf24_api_config, &packet_ma_type_1, sizeof(packet_ma_type_1), 0);
		nrf24_irq_get(&nrf24_api_config, &IRQ_flags);
		if((IRQ_flags & NRF24_IRQ_RX_DR) != 0)
		{
			HAL_GPIO_WritePin(GPIOC , GPIO_PIN_13, GPIO_PIN_SET);
			HAL_Delay(50);

			do
			{
				nrf24_fifo_read(&nrf24_api_config, rx_buffer, 32);
				nrf24_fifo_peek(&nrf24_api_config, &packet_size, &rx_pipe_no, &tx_full);
			} while (packet_size);
			nrf24_irq_clear(&nrf24_api_config, NRF24_IRQ_RX_DR);
		    nrf24_fifo_flush_rx(&nrf24_api_config);
		    nrf24_fifo_flush_tx(&nrf24_api_config);
		}

		HAL_GPIO_WritePin(GPIOC , GPIO_PIN_13, GPIO_PIN_RESET);
		nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
		/*if(tx_status == NRF24_FIFO_EMPTY)
		{
			HAL_GPIO_WritePin(GPIOC , GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_Delay(100);
			nrf24_fifo_flush_rx(&nrf24_api_config);
			er_rf_wr = nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), true);
		}*/
		/*if(rx_status != NRF24_FIFO_EMPTY)
		{
			nrf24_fifo_read(&nrf24_api_config, rx_buffer, 32);
			if (rx_status == NRF24_FIFO_FULL)
			{
				nrf24_fifo_flush_rx(&nrf24_api_config);
			}

			nrf24_fifo_flush_tx(&nrf24_api_config);
			nrf24_pipe_set_tx_addr(&nrf24_api_config, 0xafafafaf01);
			nrf24_mode_tx(&nrf24_api_config);
			er_rf_wr = nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), false);
			if (er_rf_wr <= 0) er_rf_wr = 0;
		}*/


/*
	lsmread(&ctx, &temperature_celsius_gyro, &acc_g, &gyro_dps);

	for (int i= 0; i < 3 ; i++)
	{
		packet_ma_type_2.acc_mg[i] = (int16_t)(acc_g[i]*1000);
	}

	for (int i = 0; i < 3 ; i++)
	{
		packet_ma_type_2.gyro_mdps[i] = (int16_t)(gyro_dps[i]*1000);
	}



	lisread(&ctx, &temp_lis, &mag);

	for (int i = 0; i < 3 ;i++)
	{
		packet_ma_type_2.LIS3MDL_magnetometer[i] = mag[i]*1000;
	}*/

	/*
	comp_data = bme_read_data(&bme);
	packet_ma_type_1.BME280_pressure = (float)comp_data.pressure;
	packet_ma_type_1.BME280_temperature = (float)comp_data.temperature;


	height_on_BME280 = 44330.0*(1.0 - pow((float)packet_ma_type_1.BME280_pressure/pressure_on_ground, 1.0/5.255));

	packet_ma_type_2.phortsistor = photorezistor_get_lux(photoresistor);*/





/*
	ina219_t ina219_gen;
	ina219_init(&ina219_gen, &hi2c1, INA219_I2CADDR_A1_GND_A0_GND, 5000);
	ina219_cfg_t ina_config_gen;
	ina_config_gen.bus_range = INA219_BUS_RANGE_16V;
	ina_config_gen.bus_res = INA219_ADC_RES_12_BIT_OVS_128;
	ina_config_gen.current_lsb = 1;
	ina_config_gen.shunt_r = 0.01;
	ina_config_gen.shunt_range = INA219_SHUNT_RANGE_160MV;
	ina_config_gen.shunt_res = INA219_ADC_RES_12_BIT_OVS_128;

	ina219_secondary_data_t ina219_secondary_data_gen;

	ina219_set_cal(&ina219_gen, 1.0, 0.1);
	ina219_set_cfg(&ina219_gen, &ina_config_gen);
	ina219_set_mode(&ina219_gen, INA219_MODE_SHUNT_AND_BUS_CONT);
	ina219_read_secondary(&ina219_gen, &ina219_secondary_data_gen);



	ina219_t ina219_akb;
	ina219_init(&ina219_akb, &hi2c1, INA219_I2CADDR_A1_GND_A0_VSP, 5000);
	ina219_cfg_t ina_config_akb;
	ina_config_akb.bus_range = INA219_BUS_RANGE_16V;
	ina_config_akb.bus_res = INA219_ADC_RES_12_BIT_OVS_128;
	ina_config_akb.current_lsb = 1;
	ina_config_akb.shunt_r = 0.01;
	ina_config_akb.shunt_range = INA219_SHUNT_RANGE_160MV;
	ina_config_akb.shunt_res = INA219_ADC_RES_12_BIT_OVS_128;

	ina219_secondary_data_t ina219_secondary_data_akb;

	ina219_set_cal(&ina219_akb, 1.0, 0.1);
	ina219_set_cfg(&ina219_akb, &ina_config_akb);
	ina219_set_mode(&ina219_akb, INA219_MODE_SHUNT_AND_BUS_CONT);
	ina219_read_secondary(&ina219_akb, &ina219_secondary_data_akb);
*/
	}
	return 0;
}




