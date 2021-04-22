STM32H7 Multicore FIR
======================
:star: Star me on GitHub — it helps!

STM32H7 Multicore FIR is a finite impulse response filter implementation for a family of multicore processors from STM32 - family H7. The algorithm runs in parallel on both cores and this helps users to achieve high sampling frequencies or higher FIR filter order.

## Table of content

- [Setup](#setup)
	- [Version](#version)
- [Specification](#specification)
	- [Microcontroller](#microcontroller)
	- [FIR Filter](#fir-filter)
- [On target tests](#on-target-tests)
	- [Test configuration](#test-configuration)
	- [Timing](#timing)
	- [Filter Tests](#Filter-tests)
	  	- [15 KHz Low Pass Filter](#15-KHz-Low-Pass-filter)
	  	- [5 KHz High Pass Filter](#5-KHz-High-Pass-filter)
	  	- [2KHz - 18KHz Band Pass filter](#2KHz-18KHz-Band-Pass-filter)
- [License](#license)
- [Links](#links)

## Setup

### Version

This document is for the latest  **[STM32H7_MulticoreFIR](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/releases/tag/v1.0.0)** **1.0.0 release and later**. 

Built with:

- STM32CubeIDE **Version: 1.5.1**
- Build: 9029_20201210_1234 (UTC)

### Import of the project

For successful import of the project in STM32CubeIDE is needed:
- In the main menu go to **File**
- Choose option **Open Projects from File System...**
- In option **Import Source** choose the cloned repository

> **Note:** For multicore debugging please read **[Multicore debugging](https://www.st.com/resource/en/application_note/dm00629855-getting-started-with-projects-based-on-dualcore-stm32h7-microcontrollers-in-stm32cubeide-stmicroelectronics.pdf)**

## Specification
### Microcontroller
#### Core M7:

- Running on frequency 480 MHz
- Uses ADC1, DAC1, TIM3 and L1 Cache

#### Core M4:

- Running on frequency 240 MHz
- Uses **-**

#### ADC1:
- Single Ended
- Clock Prescaler /4
- Sampling frequency is 192KHz
- Conversion is triggered with TIM3
- Resolution is 16Bit
- DMA stores data after conversion and trigger conversion complete ISR

#### DAC1:
- Mode - Connected to external pin only
- Output buffer enabled
- Sampling frequency is 192KHz
- Resolution is 12Bit

#### Context execution view:
![Go to the import view](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Docs/Images/contextExec.PNG?raw=true)
#### Pinout:

- **DAC1** output is mapped to pin **PA4**
- **ADC1** output is mapped to pin **PF11**

### FIR Filter
FIR Filter algorithm calculation is split between two cores. Inside **[settings header](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Common/Inc/settings.h)** you can easily change the splitter macro that defines how many samples are calculated on core M7 and core M4. On the UML diagram below you can see FIR filter execution flow. Delay of the FIR algorithm is equal to the sampling period.

![Go to the import view](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Docs/Images/UML.PNG?raw=true)
For the FIR filter design you can use **[Matlab filter designer](https://www.mathworks.com/help/signal/ug/introduction-to-filter-designer.html;jsessionid=420fe8cddcf95e47397263033764)**. The example below is from this package and coefficient from this design are currently used in the  **[settings source](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Common/Src/settings.c)**.

![Go to the import view](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Docs/Images/FilterDesign.PNG?raw=true)

> **Warning:** If you change the order of the filter, you have to change also macro **FILTER_ORDER** inside **[settings header](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Common/Inc/settings.h)**

## On target tests
### Test configuration
The measurement was made with **[STM32H7_MulticoreFIR release v1.0.0](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/releases/tag/v1.0.0)** and eval board **[NUCLEO-H755ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-h755zi-q.html)**
> Core M7: 480 MHz
> Core M4: 240 MHz
> Filter Order: 45
> Splitter : 35
> ADC1 resolution : 16 bit
> DAC1 resolution : 12 bit
> Sampling frequency: 192 KHz

### Timing
Measurement was made with a logic analyzer. On the picture below you can see FIR algorithm calculation time. 

- Number 1 is core M7. Logical high means that ADC1 conversion completed interrupt was already triggered and the prior result of FIR algorithm is written to DAC1. Core M7 then triggers the partial FIR calculation on core M4 with SEV interrupt. 
- Number 2 is core M4. Logical high means that SEV interrupt triggered by core M7 is executing. After finishing the FIR algorithm calculation the logic level goes back to low. Crucial is to tune core M4 to end with the calculation before the ADC1 conversion completed interrupt is triggered again on the core M7.

![Go to the import view](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Docs/Images/measurementOfFIRCalculation.PNG?raw=true)

### Filter Tests
Measurement was made with the soundcard (192KHz sampling frequency and 32-bit resolution). Despite that, the results are not so exact and it would be good to redo measurement with an oscilloscope.

Signal was generated with [JDS2800 Signal Generator Digital Control Dual-channel DDS Function Signal Generator](https://www.banggood.com/JDS2800-15MHZ-40MHZ-60MHZ-Signal-Generator-Digital-Control-Dual-channel-DDS-Function-Signal-Generato-p-1353873.html?cur_warehouse=CN&ID=556909). 

#### 15 KHz Low Pass filter
The measurement was made with **[STM32H7_MulticoreFIR release v1.0.0](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/releases/tag/v1.0.0)** and eval board **[NUCLEO-H755ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-h755zi-q.html)**
> Core M7: 480 MHz
> Core M4: 240 MHz
> Filter Order: 45
> Cutoff frequency: 15 KHz low pass filter
> Splitter : 35
> ADC1 resolution : 16 bit
> DAC1 resolution : 12 bit
> Sampling frequency: 192 KHz
> FIR – Taylor Window, Nbar 4, Sidelobe Level 30

The picture below shows captured **15 KHz** LP filter magnitude response simulated in Matlab and measured on real hardware with soundcard oscilloscope. 

![Go to the import view](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Docs/Images/15KhzCutoff.PNG?raw=true)

#### 5 KHz High Pass filter
The measurement was made with **[STM32H7_MulticoreFIR release v1.0.0](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/releases/tag/v1.0.0)** and eval board **[NUCLEO-H755ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-h755zi-q.html)**
> Core M7: 480 MHz
> Core M4: 240 MHz
> Filter Order: 45
> Cutoff frequency: 5 KHz high pass filter
> Splitter : 35
> ADC1 resolution : 16 bit
> DAC1 resolution : 12 bit
> Sampling frequency: 192 KHz
> FIR – Taylor Window, Nbar 4, Sidelobe Level 30

The picture below shows captured **5 KHz** HP filter magnitude response simulated in Matlab and measured on real hardware with soundcard oscilloscope. 

![Go to the import view](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Docs/Images/5KhzCutoff.png?raw=true)

#### 2KHz 18KHz Band Pass filter
The measurement was made with **[STM32H7_MulticoreFIR release v1.0.0](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/releases/tag/v1.0.0)** and eval board **[NUCLEO-H755ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-h755zi-q.html)**
> Core M7: 480 MHz
> Core M4: 240 MHz
> Filter Order: 45
> Cutoff frequency: 2KHz - 18KHz band pass filter
> Splitter : 35
> ADC1 resolution : 16 bit
> DAC1 resolution : 12 bit
> Sampling frequency: 192 KHz
> FIR – Taylor Window, Nbar 4, Sidelobe Level 30

The picture below shows captured **2KHz - 18KHz** BP filter magnitude response simulated in Matlab and measured on real hardware with soundcard oscilloscope. 

![Go to the import view](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/blob/main/Docs/Images/BandPass.PNG?raw=true)


## License

The STM32H7 Multicore FIR  is licensed under the terms of the DBAD
license and is available for free.

## Links
* [Source code](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR)
* [Wiki](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/wiki)
* [Issue tracker](https://github.com/PavolKostolansky/STM32H7_MulticoreFIR/issues)
