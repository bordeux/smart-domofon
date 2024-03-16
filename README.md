# smart-domofon

ESP32/8266/12E implementation of Unifon digital domfon

![hobby-desk](./.github/images/photo1.jpg)


### Is this project finished?
NO

### When this project will be finished?
> Witam, chyba nigdy  

I think never. It is hobby project. If i will finish it, i will be happy :) 


## Documentation
I will share here what i know

### General
* L+ is analog, 0-11V
* L- is GND

### IDLE
In IDLE mode, L+ is 0 state

### Dialling

In dialling mode L+ starting be UP.
And then we have 58ms to count all Edge falling. 
Count of edge falling is dialled number.

Example how it looks like when number 10 is called
![hobby-desk](./.github/images/photo2.png)

Example how it looks like when number 8 is called
![hobby-desk](./.github/images/photo3.png)



### Calling
After 58ms of dialling, the calling procedure is started.