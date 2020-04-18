/****************************************************************************
 **             - iom32.h -
 **
 **     This file declares the internal register addresses for ATmega32.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright 2017 IAR Systems AB. All rights reserved.
 **
 **     File version: $Revision$
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
#ifdef __HAS_RAMPZ__
#error This file should not have RAMPZ enabled, use --cpu or --64k_flash
#endif /* __HAS_RAMPZ__ */

#ifndef __IOM32_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define RESET_vect               (0x00) /* External Pin, Power-on Reset, Brown-out Reset  and Watchdog Reset */
#define INT0_vect                (0x04) /* External Interrupt Request 0 */
#define INT1_vect                (0x08) /* External Interrupt Request 1 */
#define INT2_vect                (0x0C) /* External Interrupt Request 2 */
#define TIMER2_COMP_vect         (0x10) /* Timer/Counter2 Compare Match */
#define TIMER2_OVF_vect          (0x14) /* Timer/Counter2 Overflow */
#define TIMER1_CAPT_vect         (0x18) /* Timer/Counter1 Capture Event */
#define TIMER1_COMPA_vect        (0x1C) /* Timer/Counter1 Compare Match A */
#define TIMER1_COMPB_vect        (0x20) /* Timer/Counter1 Compare Match B */
#define TIMER1_OVF_vect          (0x24) /* Timer/Counter1 Overflow */
#define TIMER0_COMP_vect         (0x28) /* Timer/Counter0 Compare Match */
#define TIMER0_OVF_vect          (0x2C) /* Timer/Counter0 Overflow */
#define SPI_STC_vect             (0x30) /* Serial Transfer Complete */
#define USART_RXC_vect           (0x34) /* USART, Rx Complete */
#define USART_UDRE_vect          (0x38) /* USART Data Register Empty */
#define USART_TXC_vect           (0x3C) /* USART, Tx Complete */
#define ADC_vect                 (0x40) /* ADC Conversion Complete */
#define EE_RDY_vect              (0x44) /* EEPROM Ready */
#define ANA_COMP_vect            (0x48) /* Analog Comparator */
#define TWI_vect                 (0x4C) /* 2-wire Serial Interface */
#define SPM_RDY_vect             (0x50) /* Store Program Memory Ready */


#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#include "bitdefinitions/iom32.inc"
#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IOM32_H (define part) */


/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOM32_H) || defined(__IAR_SYSTEMS_ASM__)
#define __IOM32_H

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

 SFR_B_N(0x3F, SREG, I, T, H, S, V, N, Z, C)
 SFR_W_N(0x3D, SP, Dummy15, Dummy14, Dummy13, Dummy12, SP11, SP10, SP9, SP8, SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)
 SFR_B_N(0x3C, OCR0, OCR07, OCR06, OCR05, OCR04, OCR03, OCR02, OCR01, OCR00)
 SFR_B_N(0x3B, GICR, INT1, INT0, INT2, Dummy4, Dummy3, Dummy2, IVSEL, IVCE)
 SFR_B_N(0x3A, GIFR, INTF1, INTF0, INTF2, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
 SFR_B_N(0x39, TIMSK, OCIE2, TOIE2, TICIE1, OCIE1A, OCIE1B, TOIE1, OCIE0, TOIE0)
 SFR_B_N(0x38, TIFR, OCF2, TOV2, ICF1, OCF1A, OCF1B, TOV1, OCF0, TOV0)
 SFR_B_N(0x37, SPMCR, SPMIE, RWWSB, Dummy5, RWWSRE, BLBSET, PGWRT, PGERS, SPMEN)
 SFR_B_N(0x36, TWCR, TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, Dummy1, TWIE)
 SFR_B_N(0x35, MCUCR, SE, SM2, SM1, SM0, ISC11, ISC10, ISC01, ISC00)
 SFR_B_N(0x34, MCUCSR, JTD, ISC2, Dummy5, JTRF, WDRF, BORF, EXTRF, PORF)
 SFR_B_N(0x33, TCCR0, FOC0, WGM00, COM01, COM00, WGM01, CS02, CS01, CS00)
 SFR_B_N(0x32, TCNT0, TCNT07, TCNT06, TCNT05, TCNT04, TCNT03, TCNT02, TCNT01, TCNT00)
 SFR_B2_BITS_N2(OSCCAL, OCDR, 0x31, CAL7, CAL6, CAL5, CAL4, CAL3, CAL2, CAL1, CAL0, OCDR7, OCDR6, OCDR5, OCDR4, OCDR3, OCDR2, OCDR1, OCDR0)
 SFR_B_N(0x30, SFIOR, ADTS2, ADTS1, ADTS0, Dummy4, ACME, PUD, PSR2, PSR10)
 SFR_B_N(0x2F, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, FOC1A, FOC1B, WGM11, WGM10)
 SFR_B_N(0x2E, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)
 SFR_W_N(0x2C, TCNT1, TCNT115, TCNT114, TCNT113, TCNT112, TCNT111, TCNT110, TCNT19, TCNT18, TCNT17, TCNT16, TCNT15, TCNT14, TCNT13, TCNT12, TCNT11, TCNT10)
 SFR_W_N(0x2A, OCR1A, OCR1A15, OCR1A14, OCR1A13, OCR1A12, OCR1A11, OCR1A10, OCR1A9, OCR1A8, OCR1A7, OCR1A6, OCR1A5, OCR1A4, OCR1A3, OCR1A2, OCR1A1, OCR1A0)
 SFR_W_N(0x28, OCR1B, OCR1B15, OCR1B14, OCR1B13, OCR1B12, OCR1B11, OCR1B10, OCR1B9, OCR1B8, OCR1B7, OCR1B6, OCR1B5, OCR1B4, OCR1B3, OCR1B2, OCR1B1, OCR1B0)
 SFR_W_N(0x26, ICR1, ICR115, ICR114, ICR113, ICR112, ICR111, ICR110, ICR19, ICR18, ICR17, ICR16, ICR15, ICR14, ICR13, ICR12, ICR11, ICR10)
 SFR_B_N(0x25, TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 SFR_B_N(0x24, TCNT2, TCNT27, TCNT26, TCNT25, TCNT24, TCNT23, TCNT22, TCNT21, TCNT20)
 SFR_B_N(0x23, OCR2, OCR27, OCR26, OCR25, OCR24, OCR23, OCR22, OCR21, OCR20)
 SFR_B_N(0x22, ASSR, Dummy7, Dummy6, Dummy5, Dummy4, AS2, TCN2UB, OCR2UB, TCR2UB)
 SFR_B_N(0x21, WDTCR, Dummy7, Dummy6, Dummy5, WDTOE, WDE, WDP2, WDP1, WDP0)
 SFR_B2_N(0x20, UCSRC, UBRRH, URSEL, UMSEL, UPM1, UPM0, USBS, UCSZ1, UCSZ0, UCPOL)
 SFR_W_N(0x1E, EEAR, Dummy15, Dummy14, Dummy13, Dummy12, Dummy11, Dummy10, EEAR9, EEAR8, EEAR7, EEAR6, EEAR5, EEAR4, EEAR3, EEAR2, EEAR1, EEAR0)
 SFR_B_N(0x1D, EEDR, EEDR7, EEDR6, EEDR5, EEDR4, EEDR3, EEDR2, EEDR1, EEDR0)
 SFR_B_N(0x1C, EECR, Dummy7, Dummy6, Dummy5, Dummy4, EERIE, EEMWE, EEWE, EERE)
 SFR_B_N(0x1B, PORTA, PORTA7, PORTA6, PORTA5, PORTA4, PORTA3, PORTA2, PORTA1, PORTA0)
 SFR_B_N(0x1A, DDRA, DDA7, DDA6, DDA5, DDA4, DDA3, DDA2, DDA1, DDA0)
 SFR_B_N(0x19, PINA, PINA7, PINA6, PINA5, PINA4, PINA3, PINA2, PINA1, PINA0)
 SFR_B_N(0x18, PORTB, PORTB7, PORTB6, PORTB5, PORTB4, PORTB3, PORTB2, PORTB1, PORTB0)
 SFR_B_N(0x17, DDRB, DDB7, DDB6, DDB5, DDB4, DDB3, DDB2, DDB1, DDB0)
 SFR_B_N(0x16, PINB, PINB7, PINB6, PINB5, PINB4, PINB3, PINB2, PINB1, PINB0)
 SFR_B_N(0x15, PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0)
 SFR_B_N(0x14, DDRC, DDC7, DDC6, DDC5, DDC4, DDC3, DDC2, DDC1, DDC0)
 SFR_B_N(0x13, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
 SFR_B_N(0x12, PORTD, PORTD7, PORTD6, PORTD5, PORTD4, PORTD3, PORTD2, PORTD1, PORTD0)
 SFR_B_N(0x11, DDRD, DDD7, DDD6, DDD5, DDD4, DDD3, DDD2, DDD1, DDD0)
 SFR_B_N(0x10, PIND, PIND7, PIND6, PIND5, PIND4, PIND3, PIND2, PIND1, PIND0)
 SFR_B_N(0x0F, SPDR, SPDR7, SPDR6, SPDR5, SPDR4, SPDR3, SPDR2, SPDR1, SPDR0)
 SFR_B_N(0x0E, SPSR, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)
 SFR_B_N(0x0D, SPCR, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)
 SFR_B_N(0x0C, UDR, UDR7, UDR6, UDR5, UDR4, UDR3, UDR2, UDR1, UDR0)
 SFR_B_N(0x0B, UCSRA, RXC, TXC, UDRE, FE, DOR, PE, U2X, MPCM)
 SFR_B_N(0x0A, UCSRB, RXCIE, TXCIE, UDRIE, RXEN, TXEN, UCSZ2, RXB8, TXB8)
 SFR_B_N(0x09, UBRRL, UBRRL7, UBRRL6, UBRRL5, UBRRL4, UBRRL3, UBRRL2, UBRRL1, UBRRL0)
 SFR_B_N(0x08, ACSR, ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0)
 SFR_B_N(0x07, ADMUX, REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0)
 SFR_B_N(0x06, ADCSRA, ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0)
 SFR_W_N(0x04, ADC, ADC15, ADC14, ADC13, ADC12, ADC11, ADC10, ADC9, ADC8, ADC7, ADC6, ADC5, ADC4, ADC3, ADC2, ADC1, ADC0)
 SFR_B_N(0x03, TWDR, TWDR7, TWDR6, TWDR5, TWDR4, TWDR3, TWDR2, TWDR1, TWDR0)
 SFR_B_N(0x02, TWAR, TWA6, TWA5, TWA4, TWA3, TWA2, TWA1, TWA0, TWGCE)
 SFR_B_N(0x01, TWSR, TWS7, TWS6, TWS5, TWS4, TWS3, Dummy2, TWPS1, TWPS0)
 SFR_B_N(0x00, TWBR, TWBR7, TWBR6, TWBR5, TWBR4, TWBR3, TWBR2, TWBR1, TWBR0)

#pragma language=restore

#ifndef __IAR_SYSTEMS_ASM__
#include "bitdefinitions/iom32.inc"
#endif

#endif /* __IOM32_H (SFR part) */

