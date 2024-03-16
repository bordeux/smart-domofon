# smart-domofon

ESP32/8266/12E implementation of Unifon digital domfon/intercom

![hobby-desk](./.github/images/photo1.jpg)


### Is this project finished?
NO

### When this project will be finished?
> Witam, chyba nigdy  

I think never. It is hobby project :) 


## Documentation
I'll share my learnings here.

### General
* L+ is analog, 0-11V
* L- is GND
* digital domofon - it is only the name. It is still analog in practice.

### IDLE
In IDLE mode, L+ is 0 state

### Dialling

In dialling mode L+ starting be UP.
And then we have 58ms to count all Edge falling. 
Count of edge falling is dialled number.

Example how it looks like when number 10 is called
![dialling 10](./.github/images/photo2.png)

Example how it looks like when number 8 is called
![dialling 8](./.github/images/photo3.png)

Here full view of dialling procedure. It takes 58ms
![dialling procedure](./.github/images/photo4.png)

### Calling
After 58ms of dialling, the calling procedure is started.

It changes the state in 0.5s interval
![calling](./.github/images/photo5.png)
![calling](./.github/images/photo6.png)

