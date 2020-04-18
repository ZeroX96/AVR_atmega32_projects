/****************************************************************************
 **             - iom128.h -
 **
 **     This file declares the internal register addresses for ATmega128.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright 2001 IAR Systems AB. All rights reserved.
 **
 **     File version: $Revision: 10510 $
 **
 ***************************************************************************/

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#include "iomacro.h"

#if TID_GUARD(3)
#error This file should only be compiled with iccavr or aavr with processor option -v3
#endif /* TID_GUARD(3) */

#ifndef __IOM128_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define    RESET_vect           (0x00)
#define    INT0_vect            (0x04)
#define    INT1_vect            (0x08)
#define    INT2_vect            (0x0C)
#define    INT3_vect            (0x10)
#define    INT4_vect            (0x14)
#define    INT5_vect            (0x18)
#define    INT6_vect            (0x1C)
#define    INT7_vect            (0x20)
#define    TIMER2_COMP_vect     (0x24)
#define    TIMER2_OVF_vect      (0x28)
#define    TIMER1_CAPT_vect     (0x2C)
#define    TIMER1_COMPA_vect    (0x30)
#define    TIMER1_COMPB_vect    (0x34)
#define    TIMER1_OVF_vect      (0x38)
#define    TIMER0_COMP_vect     (0x3C)
#define    TIMER0_OVF_vect      (0x40)
#define    SPI_STC_vect         (0x44)
#define    USART0_RXC_vect      (0x48)
#define    USART0_UDRE_vect     (0x4C)
#define    USART0_TXC_vect      (0x50)
#define    ADC_vect             (0x54)
#define    EE_RDY_vect          (0x58)
#define    ANA_COMP_vect        (0x5C)
#define    TIMER1_COMPC_vect    (0x60)
#define    TIMER3_CAPT_vect     (0x64)
#define    TIMER3_COMPA_vect    (0x68)
#define    TIMER3_COMPB_vect    (0x6C)
#define    TIMER3_COMPC_vect    (0x70)
#define    TIMER3_OVF_vect      (0x74)
#define    USART1_RXC_vect      (0x78)
#define    USART1_UDRE_vect     (0x7C)
#define    USART1_TXC_vect      (0x80)
#define    TWI_vect             (0x84)
#define    SPM_RDY_vect         (0x88)

#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#include "bitdefinitions/iom128.inc"
#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IOM128_H (define part) */


/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOM128_H) || defined(__IAR_SYSTEMS_ASM__)
#define __IOM128_H

#pragma language=save
#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

 SFR_B_N(0x00,   PINF, PINF7, PINF6, PINF5, PINF4, PINF3, PINF2, PINF1, PINF0)     /* Input Pins, Port F */
 SFR_B_N(0x01,   PINE, PINE7, PINE6, PINE5, PINE4, PINE3, PINE2, PINE1, PINE0)     /* Input Pins, Port E */
 SFR_B_N(0x02,   DDRE, DDE7,  DDE6,  DDE5,  DDE4,  DDE3,  DDE2,  DDE1,  DDE0)      /* Data Direction Register, Port E */
 SFR_B_N(0x03,  PORTE, PORTE7, PORTE6, PORTE5, PORTE4, PORTE3, PORTE2, PORTE1, PORTE0) /* Data Register, Port E */
 SFR_W_R(0x04,    ADC)     /* ADC Data register */
 SFR_B2_N(0x06, ADCSR, ADCSRA, ADEN, ADSC, ADFR, ADIF, ADIE, ADPS2, ADPS1, ADPS0)  /* ADC Control and Status Register */
 SFR_B_N(0x07,  ADMUX, REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0)          /* ADC Multiplexer Selection Register */
 SFR_B_N(0x08,   ACSR, ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0)              /* Analog Comparator Control and Status Register */
 SFR_B_R(0x09, UBRR0L)     /* USART0 Baud Rate Register Low*/
 SFR_B_N(0x0A, UCSR0B, RXCIE0, TXCIE0, UDRIE0, RXEN0, TXEN0, UCSZ02, RXB80, TXB80) /* USART0 Control and Status Register B */
 SFR_B_N(0x0B, UCSR0A, RXC0, TXC0, UDRE0, FE0, DOR0, UPE0, U2X0, MPCM0)            /* USART0 Control and Status Register A */
 SFR_B_R(0x0C,   UDR0)     /* USART0 I/O Data Register */
 SFR_B_N(0x0D,   SPCR, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)              /* SPI Control Register */
 SFR_B_N(0x0E,   SPSR, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)  /* SPI Status Register */
 SFR_B_R(0x0F,   SPDR)     /* SPI I/O Data Register */
 SFR_B_N(0x10,   PIND, PIND7, PIND6, PIND5, PIND4, PIND3, PIND2, PIND1, PIND0)     /* Input Pins, Port D */
 SFR_B_N(0x11,   DDRD, DDD7, DDD6, DDD5, DDD4, DDD3, DDD2, DDD1, DDD0)             /* Data Direction Register, Port D */
 SFR_B_N(0x12,  PORTD, PORTD7, PORTD6, PORTD5, PORTD4, PORTD3, PORTD2, PORTD1, PORTD0) /* Data Register, Port D */
 SFR_B_N(0x13,   PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)     /* Input Pins, Port C */
 SFR_B_N(0x14,   DDRC, DDC7, DDC6, DDC5, DDC4, DDC3, DDC2, DDC1, DDC0)             /* Data Direction Register, Port C */
 SFR_B_N(0x15,  PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0) /* Data Register, Port C */
 SFR_B_N(0x16,   PINB, PINB7, PINB6, PINB5, PINB4, PINB3, PINB2, PINB1, PINB0)     /* Input Pins, Port B */
 SFR_B_N(0x17,   DDRB, DDB7, DDB6, DDB5, DDB4, DDB3, DDB2, DDB1, DDB0)             /* Data Direction Register, Port B */
 SFR_B_N(0x18,  PORTB, PORTB7, PORTB6, PORTB5, PORTB4, PORTB3, PORTB2, PORTB1, PORTB0) /* Data Register, Port B */
 SFR_B_N(0x19,   PINA, PINA7, PINA6, PINA5, PINA4, PINA3, PINA2, PINA1, PINA0)     /* Input Pins, Port A */
 SFR_B_N(0x1A,   DDRA, DDA7, DDA6, DDA5, DDA4, DDA3, DDA2, DDA1, DDA0)             /* Data Direction Register, Port A */
 SFR_B_N(0x1B,  PORTA, PORTA7, PORTA6, PORTA5, PORTA4, PORTA3, PORTA2, PORTA1, PORTA0) /* Data Register, Port A */
 SFR_B_N(0x1C,   EECR, Dummy7, Dummy6, Dummy5, Dummy4, EERIE, EEMWE, EEWE, EERE)   /* EEPROM Control Register */
 SFR_B_R(0x1D,   EEDR)     /* EEPROM Data Register */
 SFR_W_R(0x1E,   EEAR)     /* EEPROM Address Register */
 SFR_B_N(0x20,  SFIOR, TSM, Dummy6, Dummy5, Dummy4, ACME, PUD, PSR0, PSR321)       /* Special Function I/O Register */
 SFR_B_N(0x21,  WDTCR, Dummy7, Dummy6, Dummy5, WDCE, WDE, WDP2, WDP1, WDP0)        /* Watchdog Timer Control Register */
 SFR_B_N(0x22,   OCDR, OCDR7, OCDR6, OCDR5, OCDR4, OCDR3, OCDR2, OCDR1, OCDR0)     /* On-Chip Debug Register */
 SFR_B_R(0x23,   OCR2)     /* Timer/Counter 2 Output Compare Register */
 SFR_B_R(0x24,  TCNT2)     /* Timer/Counter 2 */
 SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)         /* Timer/Counter 2 Control Register */
 SFR_W_R(0x26,   ICR1)     /* Timer/Counter 1 Input Capture Register */
 SFR_W_R(0x28,  OCR1B)     /* Timer/Counter 1 Output Compare Register B */
 SFR_W_R(0x2A,  OCR1A)     /* Timer/Counter 1 Output Compare Register A */
 SFR_W_R(0x2C,  TCNT1)     /* Timer/Counter 1 Register */
 SFR_B_N(0x2E, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)       /* Timer/Counter 1 Control Register B */
 SFR_B_N(0x2F, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, COM1C1, COM1C0, WGM11, WGM10) /* Timer/Counter 1 Control Register A */
 SFR_B_N(0x30,   ASSR, Dummy7, Dummy6, Dummy5, Dummy4, AS0, TCN0UB, OCR0UB, TCR0UB) /* Asynchronous mode Status Register */
 SFR_B_R(0x31,   OCR0)     /* Timer/Counter 0 Output Compare Register */
 SFR_B_R(0x32,  TCNT0)     /* Timer/Counter 0 */
 SFR_B_N(0x33,  TCCR0, FOC0, WGM00, COM01, COM00, WGM01, CS02, CS01, CS00)         /* Timer/Counter 0 Control Register */
 SFR_B_N(0x34, MCUCSR, JTD, Dummy6, Dummy5, JTRF, WDRF, BORF, EXTRF, PORF)         /* MCU general Control and Status Register */
 SFR_B_N(0x35,  MCUCR, SRE, SRW10, SE, SM1, SM0, SM2, IVSEL, IVCE)                 /* MCU general Control Register */
 SFR_B_N(0x36,   TIFR, OCF2, TOV2, ICF1, OCF1A, OCF1B, TOV1, OCF0, TOV0)           /* Timer/Counter Interrupt Flag Register */
 SFR_B_N(0x37,  TIMSK, OCIE2, TOIE2, TICIE1, OCIE1A, OCIE1B, TOIE1, OCIE0, TOIE0)  /* Timer/Counter Interrupt Mask Register */
 SFR_B_N(0x38,   EIFR, INTF7, INTF6, INTF5, INTF4, INTF3, INTF2, INTF1, INTF0)     /* External Interrupt Flag Register */
 SFR_B_N(0x39,  EIMSK, INT7, INT6, INT5, INT4, INT3, INT2, INT1, INT0)             /* External Interrupt Mask Register */
 SFR_B_N(0x3A,  EICRB, ISC71, ISC70, ISC61, ISC60, ISC51, ISC50, ISC41, ISC40)     /* External Interrupt Control Register B */
 SFR_B_N(0x3B,  RAMPZ, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, RAMPZ0) /* RAM Page Z Select Register */
 SFR_B_N(0x3C,   XDIV, XDIVEN, XDIV6, XDIV5, XDIV4, XDIV3, XDIV2, XDIV1, XDIV0)    /* XTAL Divide Control Register */
 SFR_W_N(0x3D,     SP, SP15, SP14, SP13, SP12, SP11, SP10, SP9, SP8, SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)     /* Stack Pointer */
 SFR_B_N(0x3F,   SREG, I, T, H, S, V, N, Z, C)                                     /* Status Register */

/* Extended I/O space */
 SFR_B_N(0x61,   DDRF, DDF7, DDF6, DDF5, DDF4, DDF3, DDF2, DDF1, DDF0)             /* Data Direction Register, Port F */
 SFR_B_N(0x62,  PORTF, PORTF7, PORTF6, PORTF5, PORTF4, PORTF3, PORTF2, PORTF1, PORTF0) /* Data Register, Port F */
 SFR_B_N(0x63,   PING, Dummy7, Dummy6, Dummy5, PING4, PING3, PING2, PING1, PING0)  /* Input Pins, Port G */
 SFR_B_N(0x64,   DDRG, Dummy7, Dummy6, Dummy5, DDG4, DDG3, DDG2, DDG1, DDG0 )      /* Data Direction Register, Port G */
 SFR_B_N(0x65,  PORTG, Dummy7, Dummy6, Dummy5, PORTG4, PORTG3, PORTG2, PORTG1, PORTG0) /* Data Register, Port G */
 SFR_B_N(0x68, SPMCSR, SPMIE, RWWSB, Dummy5, RWWSRE, BLBSET, PGWRT, PGERS, SPMEN)  /* Store Program Memory Control and Status Register */
 SFR_B_N(0x6A,  EICRA, ISC31, ISC30, ISC21, ISC20, ISC11, ISC10, ISC01, ISC00)     /* External Interrupt Control Register A */
 SFR_B_N(0x6C,  XMCRB, XMBK, Dummy6, Dummy5, Dummy4, Dummy3, XMM2, XMM1, XMM0)     /* External Memory Control Register B */
 SFR_B_N(0x6D,  XMCRA, Dummy7, SRL2, SRL1, SRL0, SRW01, SRW00, SRW11, Dummy0)      /* External Memory Control Register A */
 SFR_B_R(0x6F, OSCCAL)     /* Oscillator Calibration Register */
 SFR_B_R(0x70,   TWBR)     /* TWI Bit Rate Register */
 SFR_B_N(0x71,   TWSR, TWS7, TWS6, TWS5, TWS4, TWS3, Dummy2, TWPS1, TWPS0)         /* TWI Status Register */
 SFR_B_N(0x72,   TWAR, TWA6, TWA5, TWA4, TWA3, TWA2, TWA1, TWA0, TWGCE)            /* TWI Address Register */
 SFR_B_R(0x73,   TWDR)     /* TWI Data Register */
 SFR_B_N(0x74,   TWCR, TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, Dummy1, TWIE)        /* TWI Control Register */
 SFR_W_R(0x78,  OCR1C)     /* Timer/Counter 1 Output Compare Register C Low */
 SFR_B_N(0x7A, TCCR1C, FOC1A, FOC1B, FOC1C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)/* Timer/Counter 1 Control Register C */
 SFR_B_N(0x7C,  ETIFR, Dummy7, Dummy6, ICF3, OCF3A, OCF3B, TOV3, OCF3C, OCF1C)     /* Extended Timer/Counter Interrupt Flag Register */
 SFR_B_N(0x7D, ETIMSK, Dummy7, Dummy6, TICIE3, OCIE3A, OCIE3B, TOIE3, OCIE3C, OCIE1C) /* Extended Timer/Counter Interrupt Mask Register */
 SFR_W_R(0x80,   ICR3)     /* Timer/Counter 3 Input Capture Register Low */
 SFR_W_R(0x82,  OCR3C)     /* Timer/Counter 3 Output Compare Register C Low */
 SFR_W_R(0x84,  OCR3B)     /* Timer/Counter 3 Output Compare Register B Low */
 SFR_W_R(0x86,  OCR3A)     /* Timer/Counter 3 Output Compare Register A Low */
 SFR_W_R(0x88, TCNT3)      /* Timer/Counter 3 Register Low */
 SFR_B_N(0x8A, TCCR3B, ICNC3, ICES3, Dummy5, WGM33, WGM32, CS32, CS31, CS30)       /* Timer/Counter 3 Control Register B */
 SFR_B_N(0x8B, TCCR3A, COM3A1, COM3A0, COM3B1, COM3B0, COM3C1, COM3C0, WGM31, WGM30) /* Timer/Counter 3 Control Register A */
 SFR_B_N(0x8C, TCCR3C, FOC3A, FOC3B, FOC3C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)/* Timer/Counter 3 Control Register C */

 SFR_B_R(0x90, UBRR0H)     /* USART0 Baud Rate Register High*/

 SFR_B_N(0x95, UCSR0C, Dummy7, UMSEL0, UPM01, UPM00, USBS0, UCSZ01, UCSZ00, UCPOL0)/* USART0 Control and Status Register C */
 SFR_B_R(0x98, UBRR1H)     /* USART1 Baud Rate Register High */
 SFR_B_R(0x99, UBRR1L)     /* USART1 Baud Rate Register Low */
 SFR_B_N(0x9A, UCSR1B, RXCIE1, TXCIE1, UDRIE1, RXEN1, TXEN1, UCSZ12, RXB81, TXB81) /* USART1 Control and Status Register B */
 SFR_B_N(0x9B, UCSR1A, RXC1, TXC1, UDRE1, FE1, DOR1, UPE1, U2X1, MPCM1)            /* USART1 Control and Status Register A */
 SFR_B_R(0x9C,   UDR1)     /* USART1 I/O Data Register */
 SFR_B_N(0x9D, UCSR1C, Dummy7, UMSEL1, UPM11, UPM10, USBS1, UCSZ11, UCSZ10, UCPOL1)/* USART1 Control and Status Register C */

#pragma language=restore

#ifndef __IAR_SYSTEMS_ASM__
#include "bitdefinitions/iom128.inc"
#endif

#endif /* __IOM128_H (SFR part) */
