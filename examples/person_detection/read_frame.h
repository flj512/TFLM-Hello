/*
 * read_frame.h
 *
 *  Created on: Apr 6, 2025
 *      Author: flj
 */

#ifndef PERSON_DETECTION_READ_FRAME_H_
#define PERSON_DETECTION_READ_FRAME_H_

#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * detect frame header from UART
 */
void detect_frame_header();

/**
 * read a frame from UART
 */
int read_frame(int image_width, int image_height, int channels,
                      int8_t* image_data);

#ifdef __cplusplus
}
#endif

#endif /* PERSON_DETECTION_READ_FRAME_H_ */
