# StableGrid

![Hardware](https://github.com/franzpl/StableGrid/blob/master/doc_pictures/hardware_schmitt_trigger.jpg)

# Introduction

The mains frequency is the nominal frequency of the electric energy supply through AC voltage. Europe, Asia, Australia and many parts of Africa and South America use a mains frequency of 50 Hz, although in North America it is 60 Hz (see world map below). It is barely possible to store energy in an integrated grid system. In consequence, the produced power has to be the same as the power consumption at each point in time. Therefore, in practise, the exact frequency of an electric power grid fluctuates around the nominal frequency. It decreases if the grid is heavily loaded and increases if ligthly loaded. Usually, the mains frequency varies between 200 mHz in West European. The aim of power control in interconncted systems is to compensate the temporal fluctuations and to maintain the mains frequency at a constant nominal value. 

![World Map Mains Frequencies](https://github.com/franzpl/StableGrid/blob/master/doc_pictures/worldmap_mains_frequencies_and_voltages.jpg)
(Source: https://www.quantumbalancing.com/worldelectricity/electricityif.htm)

# Project Description

This repository deals on the one hand with hardware design and on the other hand with software development to measure the mains frequency exactly. The frequency measurement has to be correct to three decimal places. The following circuits base on the idea of the Arduino UNO Board [ArduinoUNO](https://www.arduino.cc/en/Main/arduinoBoardUno). It is a microcontroller board which uses the ATmega328P ![datasheet](http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf). In consequence of bad accuracy and a strongly dependency on temperature of the ceramic resonator built on Arduino it was required to rebuilt the board with a better clock generator ![crystal_vs_resonator](https://forum.arduino.cc/index.php?topic=60662.0). In addition, to use the AC/AC supply as the power supply for the Atmega328P the rebuilt board contains a rectifier circuit. To measure the frequency the AC signal is converted into a square wave. Afterwards, the rising edges are counted by the interrupt pin of the ATmega328P. Two approaches were implemented to convert the sine signal into a square wave signal: 

* 1.) Schmitt Trigger
* 2.) Optocoupler

Both approaches have advantages and disadvantages. On the one hand, the Schmitt Trigger provides two different threshold voltage levels which is really useful because of adjusting the position of rising and falling edge. However, the position of rising and falling edge of the optocoupler circuit depends on the forward voltage of the LED.  On the other hand, the external circuitry of the Schmitt Trigger with many resistors increases the noise level and requires lot of space, whereas the optocoupler needs just 2 resistors. For these reasons, both approaches were implemented. These approaches are shown in the pictures below. 

## Schmitt Trigger Approach


[!Schmitt Trigger](https://github.com/franzpl/StableGrid/blob/master/doc_pictures/stable_grid_schmitt_trigger.jpg)

## Optocoupler Approach


[!Optocoupler](https://github.com/franzpl/StableGrid/blob/master/doc_pictures/stable_grid_optocoupler.jpg)

