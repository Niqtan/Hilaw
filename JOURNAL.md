---
title: "Hilaw"
author: "Niq Suguitan"
description: "Holy shit I hate running out of storage ~ probably me" 
created_at: "2025-07-08"
---

| Date started: July 7, 2025

Total hours spent: 41 hours

# Entry #0 - 07-07-25

Research on the components

So for this entry, I've been mainly just going around scouting components
in digikey.

Here are some obsidian notes:

Project Making - Building your own Instax Camera - 07-05-25

Project Name: Hilaw

Features:
- OLED screen preview (Hybrid between digital and analog)
	- Allow users to choose when to print it
- Press a button -> take a pictures
- Adjust settings
- Storage (SD Card)
- Processing on a thermal printer
- Power
	- Latching circuit
	- USB-C w SD CARD

Parts needed:
- ArduCAM
- TFT LCD
- Thermal Printer
- MCU (ESP BOARD SERIES)
	- ESP-32-S3
- Power system


Components - Camera Module - 07-07-25

Characteristics
- Megapixels
	- Megapixels are usually a metric for cropping
	- Basically, if you crop something, it will still retain its quality 

What makes a better image quality?
- Attributed to lower noise
- Better colours
- Dynamic Range


Great camera modules:
- ESP32-CAM

The good thing about ESP32-CAM:
- Cost-effective
- Doesn't take too much dev time
- Fits right perfectly
- Option to be coded with the ESP board series

Cons of ESP32-CAM:
- Video streaming wasnt the best
	- The resolution wasnt the best

Comparing this with the Raspberry Pi Cam V2
- RP
	- Image quality - much better due to SONY sensor
	- 8 MP

Why is the ESP32-CAM stitll much better?
- Its compact and wireless
- Not that complex for this project

For this project, I would pick a camera that is:
- Plug and play, fast *development*
- Has the bare minimum
- Doesn't have to have manual image control


Ends there

Total hours spent: 5 hours

# Entry #1 - 07-19-25 - Researching more components

You guessed it! More research!

What is thermal printing?
- Imagine the receipts, thermal printing is used to print those

By using the same principle of thermal printers, we can:
- Print instantly using heat


Cons of thermal printing
- They start to fade away
- Depends on paper

Thermal Printer vs Inkjet
- Inkjet
	- Paper jam
- Thermal Printers
	- Embedded Thermal Printer V2.0

Components - LCD vs OLED Screen - 07-07-25

Feature focused on: Preview of the camera's printed image

What is OLED?
- Display technology that exhibits amazing contrast since the pixels turn off to display black
- Composed of organic material that emits light when an electric current is applied


LCD
- Utilizes a backlight that shines through liquid crystals to create an image
- Control the amount of light that passes through, dictating the color and brightness of pixels


Benchmarks

Contrast ratio and black levels
- OLED technology outshiens LCD when it comes to this
- Each pixel on the OLED screen is independently lit,

LCD
- On the other hand, LCDs, regardless of backlight technology used, always emit some level of light even when trying to display black, leading a lower contrast ratio

Lifespan and Burn-in
- LCD displays are not susceptible to these issues
- OLED
	- The organic materials in OLED dipslays can degrade over time
	- Moreover, if static images are displayed for extended periosd, OLED screens can suffer from burn-in
		- Where ghost images are permanently imprinted in the screens

Energy Efficiency
- Another area where LCDs tend to excel
	- Generally consume less power than OLEDs when displaying bright or white backgrounds
	- However, the same cannot be said when dark or black images are on the screen as OLEDs consume less power 

Conclusion: 
- We're gonna use a TFT LCD
	- Difference between a TFT LCD and a normal one is that its much more robust (TFT LCD) due to new technology

Total hours spent: 5 hours

# Entry #2 - 07-22-25 - Researching Power Electronics & Doing the Schematic

For this entry, I've started doing the schematic. I only focused on making this a power only PCB, and I focused the most on getting the power part to work so I can work with the PCB straight away.

Here is another peek of my obisdian note for power calculations:


ESP32-WROOM-32 Power Characteristics:
- Power supply voltage -> -0.3V - 3.6V (absolute max)
- Minimum power supply current -> >= 500mAh
- Probably 800mAh to accomodate for the other components

ILI9341 LCD Characteristics (TFT LCD)
- Supply voltage (Logic): 3.3V (Absolute maximum characteristic)
- Around 100mA

ARDUCAM (Camera sensor)
- Supply voltage: 3.3V to 5V
- Peak current (Working): 154mA


Thermal Printer (DF Robot Embedded printer)
- Working voltage: 9V
- Working current: 1.5A - 2A when printing

What to do:
- Since the thermal printer requires a lot more power than the other components, the power system's  requirements would have to be:
	- Battery capacity: 2Ah with discharge rate of 2C 
		  discharge rate is important because it dictates the rate of which it delivers electrical energy
		  That basically means the speed of which it discharges the current we need
		  So lets say we had a 1Ah battery but the charge is only 0.5C, well that would only deliver 500mA


Basic principle of boost converter:
- Boost converters do not boost current, they boost voltage at the expense of current
- Basic principle:
	- V in  * I in = V out * Iout

![alt text](Screenshots/2.png)

Total hours spent: 6 hours

# Entry #4 - 07-24-25 - Finishing up the schematic for power management

In this journal, I mainly polished up the schematic. I've been reading a lot of datasheets and been scrolling thru a lot of them, just to make sure I don't  get anything wrong.

Here's the final schematic (Power management only since this PCB is for that)

![alt text](Screenshots/1.png)

Also, I've gotten a jumpstart at the PCB. Its been in the making currently. Didn't get any pictures sadly, forgot em.

Total hours spent: 6 hours

# Entry #5 - 07-25-25 - Finishing the PCB Layout for power management

In this entry, I have finished up the PCB layout. Here is how it looks:

![alt text](Screenshots/3.png)

Also, I've gotten a jumptart of the CAD. I've been mainly thinking about how to fit all of these components. For example, how would I fit the PCB, thermal printer, and Arducam inside it?

![alt text](Screenshots/4.png)

Also, I've been brainstorming what the hell do I do with the buttons. I heard its great to have a square on top of the tactile switch with 0.5mm clearance. so I did that on top of the circular model of the button. I did that for both buttons! Power and shutter, which have self-explanatory usages for cameras.

![alt text](Screenshots/7.png)

Total hours spent: 8 hours

# Entry #6 - 07-26-25 - Finishing up the CAD 

I've been experimenting with how to mount the PCB so that it is stable throughout the usage of the PCB. I decided to go for screws with the standoffs so it doesnt fall on the ceiling of the CAD.

![alt text](Screenshots/6.png)

Aaaandd... here is what the final CAD looks like! I decided to make this super simple. I didn't want it to be that designy, since I just wanted to use this

Here is what it looks like:
![alt text](Screenshots/5.png)


total hours spent: 6 hours

# Entry 7 - 07-29-25 - Ordering PCB & Other Stuff

For this entry, I've ordered most of what I need to assemble this!

- ✔️ PCB
- ✔️ Thermal Printer
- ✔️ Camera (albeit, differnet one since budget didn't reach)

See pictures:
![alt text](Screenshots/8.png)
![alt text](Screenshots/9.jpg)


Total hours spent: 1 hour

# Entry 8 -  07-31-25 - Working with the firmware 

For this entry, I've decided to get a jumpstart on the firmware. 

I mainly got to the initialization part of all components working. For instance, making the camera's initial process work, and the TFT display's display screen to be able to display something.

Besides that, I've also been doing a ton of research on how to make this work, and I think I've got an idea on how to.

![alt text](Screenshots/10.png)
Total hours spent: 3 hours