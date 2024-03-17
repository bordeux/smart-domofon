# smart-domofon

ESP32/8266/12E implementation of Unifon digital domfon/intercom

![hobby-desk](./.github/images/photo1.jpg)


## Is this project finished?
NO

## When this project will be finished?
> Witam, chyba nigdy  

I think never. It is hobby project :) 


# Documentation
I'll share my learnings here.

## General
* L+ is analog, 0-11V
* L- is GND
* digital domofon - it is only the name. It is still analog in practice.

## How to connect into ESP?
ESP works only on 3.3v. Intercom is working on 11v. Some resistors is needed.
My setup:

```mermaid
---
title: Connection diagram
---
flowchart TB
    eGND[GND]
    iGND[L-]
    iLP[L+]
    eD1[D1]
    R1[Resistor 10kΩ]
    R2[Resistor 3.5KΩ]
    
    eGND<-->iGND
    R1<-->iLP
    R1<-->eD1
    eGND<-->R2
    R2<-->eD1
    
    subgraph Intercom
        iGND
        iLP
    end
    
    subgraph Wires
        R1
        R2
    end
    
    subgraph ESP8266
        eGND
        eD1
    end
```

## IDLE
In IDLE mode, L+ is low state

## Dialling

In dialling mode L+ starting be UP.
And then we have 58ms to count all Edge falling. 
Count of edge falling is dialled number.

#### Example how it looks like when number 10 is called
![dialling 10](./.github/images/photo2.png)

#### Example how it looks like when number 8 is called
![dialling 8](./.github/images/photo3.png)

#### Here full view of dialling procedure. It takes 58ms
![dialling procedure](./.github/images/photo4.png)

## Detecting signal type
After 58ms of dialling, the event type need to be detected.

* ringing: 500uS interval
* wrong gate pin: 280uS interval, 530uS cycle
* correct gate pin: 218uS interval , 424uS cycle

Solution implemented: 
Wait after dialling for next pull-up, start counting pull-ups for 10ms.
* 10 ±1 = calling
* 5 ±1 = wrong gate ping
* 23 ±1 - correct pin


#### Example of calling - interval 500uS, 1ms cycle
![calling](./.github/images/photo5.png) ![calling](./.github/images/photo6.png)


#### Example of gate unlock - interval 220uS, 424uS cycle
![gate unlock](./.github/images/photo7.png) ![gate unlock](./.github/images/photo10.png)

#### Example of gate unlock wrong pin - interval 280uS, cycle around 530uS

![gate unlock - wrong pin](./.github/images/photo8.png) ![gate unlock - wrong pin](./.github/images/photo9.png)

## Cancelling calling
Cancelling signal (call & press (C) Key) looks like 10ms UP state, and then failing to 50% of signal.

#### Example of calling & right after pressing cancel key (C) 
![calling - cannceling](./.github/images/photo11.png)


## @ToDo

#### signals
* after pickup the intercom, detected signal how call is ended
* after pickup the intercom, detected opening the gate signal.
* detect how procedure of wrong pin & correct pin is ended. 
* detect how to pickup the call.

####  software
* implement two way voice communication
* find some ADC/DAC working with 10 voltage or any other solution