#include "../FATFS/App/fatfs.h"



int super_smart_write(unsigned char *buf, unsigned short len, int8_t * state_sd_from_m)
{
	while(1)
	{
		static uint32_t start_time;
		static FATFS fileSystem; // переменная типа FATFS
		static FIL testFile; // хендлер файла
		static UINT bw;
		static FRESULT res;
		static int8_t state_sd = 0;
		const char * path = "testFile.bin"; // название файла

		if(state_sd == 0)
		{
			extern Disk_drvTypeDef  disk;
			disk.is_initialized[0] = 0;
			memset(&fileSystem, 0x00, sizeof(fileSystem));
			res = f_mount(&fileSystem, "0", 1);
			if(res == FR_OK){state_sd = 1; *state_sd_from_m = state_sd;}
			else
			{
				res = f_mount(0, "0", 1);
				return -1;
			}
		}
		if(state_sd == 1)
		{
			 *state_sd_from_m = state_sd;
			res = f_open(&testFile, path, FA_WRITE | FA_OPEN_APPEND);
			if(res == FR_OK) state_sd = 2;
			else
			{
				state_sd = 0;
				res = f_mount(0, "0", 1);
			}
		}
		if (state_sd == 2)
		{
			 *state_sd_from_m = state_sd;
            res = f_write (&testFile,  (uint8_t *)buf, len, &bw);
            if (HAL_GetTick() - start_time >= 10)
            {
            	res = f_sync(&testFile);
                start_time  = HAL_GetTick();
            }
	        if (res == FR_OK) return 0;
            if (res != FR_OK)
            {
    			res = f_close(&testFile);
            	state_sd = 1;
            }
		}
	}
}








int app_main()
{
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
	packet_ma_type_1_t packet_ma_type_1 = {0};
	static int8_t state_sd = 0;
	super_smart_write((uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), &state_sd);

}
