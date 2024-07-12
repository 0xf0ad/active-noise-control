#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){
	ma_uint32 bytes_per_frame = ma_get_bytes_per_frame(pDevice->capture.format, pDevice->capture.channels);
	float* signal = malloc(frameCount * bytes_per_frame);
	memcpy(signal, pInput, frameCount * bytes_per_frame);
	for(ma_uint32 i = 0; i < (2 * frameCount); i++)
		signal[i] *= -1;
	memcpy(pOutput, signal, frameCount * bytes_per_frame);
}

int main(void){

	ma_device_config deviceConfig = ma_device_config_init(ma_device_type_duplex);
	deviceConfig.capture.pDeviceID  = NULL;
	deviceConfig.capture.format     = ma_format_f32;
	deviceConfig.capture.channels   = 2;
	deviceConfig.capture.shareMode  = ma_share_mode_shared;
	deviceConfig.playback.pDeviceID = NULL;
	deviceConfig.playback.format    = ma_format_f32;
	deviceConfig.playback.channels  = 2;
	deviceConfig.dataCallback       = data_callback;

	ma_device device;
	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
		return EXIT_FAILURE;

	ma_device_start(&device);

	printf("Press Enter to quit...\n");
	getchar();

	ma_device_uninit(&device);

	return EXIT_SUCCESS;
}

