/*
 * read_frame.c
 *
 *  Created on: Apr 6, 2025
 *      Author: flj
 */
#include<stdio.h>
#include<stm32f4xx_hal.h>

extern UART_HandleTypeDef huart1;
/**
 * detect frame header from UART
 */

static const uint8_t header_tag[] = {0x5a, 0xb3, 0x6d, 0xff};
void detect_frame_header()
{
	int index = 0;
	uint8_t val;
	while(1){
		if(HAL_UART_Receive(&huart1, &val, 1 ,30000)!=HAL_OK){
			printf("Waiting new frame...\n");
			index = 0;
			continue;
		}
		index = (header_tag[index] == val ? index + 1: 0);
		if(index == sizeof(header_tag)){
			printf("Detect new frame!\n");
			break;
		}
	}
}

/**
 * read a frame from UART
 */
int read_frame(int image_width, int image_height, int channels,
                      int8_t* image_data)
{
	int frame_size = image_width*image_height*channels;
	uint32_t start_tick = HAL_GetTick();

	if(HAL_UART_Receive(&huart1, (uint8_t*)image_data,frame_size,10000) != HAL_OK){
		return -1;
	}

	printf("Frame size %d, time = %lu ms\n",frame_size, HAL_GetTick()-start_tick);

	return 0;
}
