# TFLM-Hello
This repo run the Tensorflow Lite Micro([TFLM](https://github.com/tensorflow/tflite-micro/tree/main)) with CMSIS_NN acceleration on the STM32F429IGT6.  
The core is Cortex-M4 and the max frequency is 180Mhz.  
The device is running as an inference server and the user can send raw gray image bytes to the UART.  
The inference server will print the inference result and time info to the UART.  
# Performance
Running the default person detection model in TFLM repo in release mode  
|Input Image Size |96x96x1|
|----------|-------------|
|Inference Time@180Mhz | 235 ms|
|Model Size| 300KB|
|Text | 365KB|
|BSS|142KB|
# Board Config
Config UART/GPIO and prepare development environment.  
## UART
the UART Tx/Rx is connect to:  
TX: PA9  
RX: PA10  
## GPIO
This device use GPIO `PD12` to drive LED to indicate if the program is running.
## Frequence
The core frequency is 180Mhz.
## Dev tool
IDE: STM32CubeIDE  
Use OpenOCD to debug and program, prepare a CMSIS_DAP debugger with SWD.  
If you are using ST-link to debug, please change the debug and run configuration in STM32CubeIDE.  
# Build
Build the project and download it to the device's ROM (The debug mode is 3x slower than release mode).  
The device will light the LED on first and start waiting for user's input from the UART.  
Here is an example demonstrates how to send image to the UART in Python.
```
import cv2
import matplotlib.pyplot as plt

# Open serial port
SERIAL_PORT = '/dev/ttyUSB0' 
BAUD_RATE = 115200   
port = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

FRAME_HEADER = b'\x5A\xB3\x6D\xFF'
WIDTH = 96
HEIGHT = 96

def send_image(image_path, show_image=True):
    # Read the image file
    image = cv2.imread(image_path)
    if image is None:
        raise ValueError(f"Could not read image: {image_path}")
    
    # Resize the image to the desired dimensions
    grey = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    grey = cv2.resize(grey, (WIDTH, HEIGHT))
    image_data = grey.tobytes()

    # Send the frame over serial
    n = port.write(FRAME_HEADER + image_data)
    print(f"Sent {n} bytes to serial port, header size = {len(FRAME_HEADER)}, frame size = {len(image_data)}.")

    # show this image
    if show_image:
        image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        plt.imshow(image_rgb)
        plt.axis('off')
        plt.show()
```
The device will print the results to UART after receiving image:
```
[10:43:32.559] Please send grey image bytes to the UART with frame header: 5AB36DFF
[10:43:42.624] Read a frame, size = 9216 bytes, time = 799 ms
[10:43:42.860] Inference time: 235 ms
[10:43:42.863] person score:-100 no person score 100
[10:43:42.869] Person detect done, total time: 1044 ms
```
# Person Detection Model Graph
![person detection graph](https://github.com/flj512/TFLM-Hello/blob/master/person_detect.tflite.png)


