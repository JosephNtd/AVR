## A. What Is Timer?
**Concepts about Timer need to know**
- **BOTTOM:** Lowest value T/C can reach, T/C reach BOTTOM when it becomes 0x00
- **MAX:** Highest value T/C can reach, T/C reach MAX when it becomes 0xFF
- **TOP:** When T/C reach the TOP, it changes status. This value can adjust directly through some register

**Operation**

- The counting direction is **always up** (incrementing), and no counter clear is performed. The counter simply over
runs when it passes its maximum 8-bit value (MAX = 0xFF) and then restarts from the bottom (0x00). 

## B. Timer 0

### 1. TCCR0 – Timer/Counter Control Register:
    
![](doc/image.png)

- **Bit 2:0 – CS02:0** (Clock Select): These 3 bits used for select the clock source and prescaler.

  |CS02 | CS01 | CS00 | Description|
  |-----|------|------|------------|
  |0    | 0    |1     | clk/8      |
  |0    | 0    |1     | clk/64     |
  |0    | 0    |1     | clk/256    |
  |0    | 0    |1     | clk/1024   |
  |0    | 0    |1     | External Clock on T0 pin. Clock on falling edge                  |
  |0    | 0    |1     | External Clock on T0 pin. Clock on rising edge                   |

### 2. TCNT0 – Timer/Counter Register

![](doc/image-2.png)

  - You can set value for BOTTOM by this. If not, default will be 0.
    - TOIE0 = "Your value";

### 3. TIMSK – Timer/Counter Interrupt Mask Register

![](doc/image-3.png)

- **Bit 0 – TOIE0**(Timer/Counter0 Overflow Interrupt Enable): When set to one, the Timer/Counter0 Overflow interrupt is enabled. 

#### 4. TIFR – Timer/Counter Interrupt Flag Register

![](doc/image-4.png)


# C. Timer 1

## Register Description

### 1. TCCR1A – Timer/Counter 1 Control Register A

![](doc/image-5.png)

  - **Bit 7:6 – COM1A1:0** (Compare Output Mode for channel A)

  - **Bit 5:4 – COM1B1:0** (Compare Output Mode for channel B)

  - Compare Output Mode, **Fast PWM**

    | COM1A1/ COM1B1| COM1A0/ COM1B0| Description|
    |--------------|---------------|-------------|
    |1             |0              | Clear OC1A/B on Compare Match, set OC1A/B at BOTTOM          |
    |1             |0              | Set OC1A/B on Compare Match, clear OC1A/B at BOTTOM                                       |

  - **Bit 1:0 – WGM11:0** Waveform Generation Mode: Combined with the WGM13:2 bits found in the TCCR1B Register, these bits control the counting sequence of the counter, the source for maximum (TOP) counter value, and what type of waveform generation to be used

    | Mode| WGM13| WGM12| WGM111| WGM10| Mode of Operation |  TOP| Update of OCR1x| TOV1 Flag set on
    |-|-|-|-|-|-|-|-|-|
    0 |0|0|0|0|Normal  |0xFFFF|Immediate|MAX
    4 |0|1|0|0|CTC     |OCR1A |Immediate|MAX
    12|1|0|1|1|CTC     |ICR1  |Immediate|MAX
    14|1|1|1|0|Fast PWM|ICR1  |BOTTO    |TOP

 ### 2. TCCR1B – Timer/Counter 1 Control Register B

 ![](doc/image-8.png)

  - **Bit 4:3 – WGM13:2** Waveform Generation Mode

    See TCCR1A Register description.

  - **Bit 2:0 – CS12:0** Clock Select

    |CS02 | CS01 | CS00 | Description|
    |-----|------|------|------------|
    |0    | 0    |1     | clk/8      |
    |0    | 0    |1     | clk/64     |
    |0    | 0    |1     | clk/256    |
    |0    | 0    |1     | clk/1024   |
    |0    | 0    |1     | External Clock on T1 pin. Clock on falling edge                  |
    |0    | 0    |1     | External Clock on T1 pin. Clock on rising edge                   |

### 3. TCNT1H and TCNT1L – Timer/Counter 1

![](doc/image-10.png)

  - Set BOTTOM through this register
    - TCNT1 = "Your value";

### 4. OCR1AH and OCR1AL– Output Compare Register 1 A

![](doc/image-11.png)

### 5. OCR1BH and OCR1BL – Output Compare Register 1 B

![](doc/image-12.png)

  - In this register, it have TOP for you can adjust to compare to BOTTOM (TCNT1). Gradually increase until TOP = BOTTOM, one "Match" occur -> Interrupt execute on OC1A (or OC1B).

### 6.  ICR1H and ICR1L – Input Capture Register 1

![](doc/image-13.png)

   - The Input Capture is updated with the counter (TCNT1) value each time an event occurs on the ICP1 pin. The Input Capture can be used for defining the counter TOP value.

 ### 7. TIMSK – Timer/Counter Interrupt Mask Register

 ![](doc/image-14.png)

   - **Bit 5 – TICIE1** Input Capture Interrupt Enable

   - **Bit 4 – OCIE1A** Output Compare A Match Interrupt Enable

  - **Bit 3 – OCIE1B** Output Compare B Match Interrupt Enable

   - **Bit 2 – TOIE1** Overflow Interrupt Enable

 ### 8. TIFR – Timer/Counter Interrupt Flag Register

![](doc/image-15.png)

   - **Bit 5 – ICF1** Input Capture Flag:  This flag is set when a capture event occurs on the ICP1 pin. When the Input Capture Register (ICR1) is set by the WGM13:0 to be used as the TOP value, the ICF1 Flag is set when the counter reaches the TOP value.
 
  - **Bit 4 – OCF1A** Output Compare A Match Flag: This flag is set in the timer clock cycle after the counter (TCNT1) value matches the Output Compare Register A (OCR1A).

  - **Bit 3 – OCF1B** Output Compare B Match Flag: This flag is set in the timer clock cycle after the counter (TCNT1) value matches the Output Compare Register B (OCR1B).

  - **Bit 2 – TOV1** Overflow Flag: The setting of this flag is dependent of the WGM13:0 bits setting. In normal and CTC modes, the TOV1 Flag is set when the timer overflows.