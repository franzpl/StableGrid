# StableGrid

![Hardware](https://github.com/franzpl/StableGrid/blob/master/doc_pictures/hardware_schmitt_trigger.jpg)

# Introduction

The mains frequency is the nominal frequency of the electric energy supply through AC voltage. Europe, Asia, Australia and many parts of Africa and South America use a mains frequency of 50 Hz, although in North America it is 60 Hz (see world map below). It is barely possible to store energy in an integrated grid system. In consequence, the produced power has to be the same as the power consumption at each point in time. Therefore, in practise, the exact frequency of an electric power grid fluctuates around the nominal frequency. It decreases if the grid is heavily loaded and increases if ligthly loaded. Usually, the mains frequency varies between 200 mHz in West European. The aim of power control in interconncted systems is to compensate the temporal fluctuations and to maintain the mains frequency at a constant nominal value. 

![World Map Mains Frequencies](https://github.com/franzpl/StableGrid/blob/master/doc_pictures/worldmap_mains_frequencies.jpg)
(Source: https://de.wikipedia.org/wiki/Netzfrequenz#/media/File:Weltkarte_der_Netzspannungen_und_Netzfrequenzen.svg)

# Project Description

This repository deals on the one hand with hardware design and on the other hand with software development to measure the mains frequency exactly. 
