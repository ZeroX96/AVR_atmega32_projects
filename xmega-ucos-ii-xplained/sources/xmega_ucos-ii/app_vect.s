;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                                       ATmega128  Specific code
;                                           GNU AVR Compiler
;
;
; File     : VECTORS.S
; By       : Fabiano Kovalski
; 		   : [with modifications by Nick D'Ademo]
;********************************************************************************************************

;********************************************************************************************************
;                                         PUBLIC DECLARATIONS
;********************************************************************************************************

	.global __vector_1
    .global __vector_2
    .global __vector_3
    .global __vector_4
    .global __vector_5
    .global __vector_6
    .global __vector_7
    .global __vector_8
    .global __vector_9
    .global __vector_10
    .global __vector_11
    .global __vector_12
    .global __vector_13
    .global __vector_14
    .global __vector_15
    .global __vector_16
    .global __vector_17
    .global __vector_18
    .global __vector_19
    .global __vector_20
    .global __vector_21
    .global __vector_22
    .global __vector_23
    .global __vector_24
    .global __vector_25
    .global __vector_26
    .global __vector_27
    .global __vector_28
    .global __vector_29
    .global __vector_30
    .global __vector_31
    .global __vector_32
    .global __vector_33
    .global __vector_34
    .global __vector_35
    .global __vector_36
    .global __vector_37
    .global __vector_38
    .global __vector_39
    .global __vector_40
    .global __vector_41
    .global __vector_42
    .global __vector_43
    .global __vector_44
    .global __vector_45
    .global __vector_46
    .global __vector_47
    .global __vector_48
    .global __vector_49
    .global __vector_50
    .global __vector_51
    .global __vector_52
    .global __vector_53
    .global __vector_54
    .global __vector_55
    .global __vector_56
    .global __vector_57
    .global __vector_58
    .global __vector_59
    .global __vector_60
    .global __vector_61
    .global __vector_62
    .global __vector_63
    .global __vector_64
    .global __vector_65
    .global __vector_66
    .global __vector_67
    .global __vector_68
    .global __vector_69
    .global __vector_70
    .global __vector_71
    .global __vector_72
    .global __vector_73
    .global __vector_74
    .global __vector_75
    .global __vector_76
    .global __vector_77
    .global __vector_78
    .global __vector_79
    .global __vector_80
    .global __vector_81
    .global __vector_82
    .global __vector_83
    .global __vector_84
    .global __vector_85
    .global __vector_86
    .global __vector_87
    .global __vector_88
    .global __vector_89
    .global __vector_90
    .global __vector_91
    .global __vector_92
    .global __vector_93
    .global __vector_94
    .global __vector_95
    .global __vector_96
    .global __vector_97
    .global __vector_98
    .global __vector_99
    .global __vector_100
    .global __vector_101
    .global __vector_102
    .global __vector_103
    .global __vector_104
    .global __vector_105
    .global __vector_106
    .global __vector_107
    .global __vector_108
    .global __vector_109
    .global __vector_110
    .global __vector_111
    .global __vector_112
    .global __vector_113
    .global __vector_114
    .global __vector_115
    .global __vector_116
    .global __vector_117
    .global __vector_118
    .global __vector_119
    .global __vector_120
    .global __vector_121
    .global __vector_122
    .global __vector_123
    .global __vector_124
    

    .extern   TickISR
	.extern   usartc0_rx_isr
	.extern   usartf0_rx_isr
	.extern   pushbutton_timer_isr



;********************************************************************************************************
;                                        INTERRUPT VECTOR TABLE
;********************************************************************************************************

        .section .vectors, "ax"
                                                   ; Vector #   Address       Interrupt Definition
                                                   ; --------   -----------   ------------------------------------------
                                                   ;      0       0x0000       Reset
__vector_1:     JMP     __unhandled_interrupt      ;      1       0x0004       External Oscillator Failure (NMI)
__vector_2:     JMP     __unhandled_interrupt      ;      2       0x0008       Port C External Interrupt 0
__vector_3:     JMP     __unhandled_interrupt      ;      3       0x000C       Port C External Interrupt 1
__vector_4:     JMP     __unhandled_interrupt      ;      4       0x0010       Port R External Interrupt 0
__vector_5:     JMP     __unhandled_interrupt      ;      5       0x0014       Port R External Interrupt 1
__vector_6:     JMP     __unhandled_interrupt      ;      6       0x0018       DMA CH0
__vector_7:     JMP     __unhandled_interrupt      ;      7       0x001C       DMA CH1
__vector_8:     JMP     __unhandled_interrupt      ;      8       0x0020       DMA CH2
__vector_9:     JMP     __unhandled_interrupt      ;      9       0x0024       DMA CH3
__vector_10:    JMP     __unhandled_interrupt      ;     10       0x0028       RTC Overflow
__vector_11:    JMP     __unhandled_interrupt      ;     11       0x002C       RTC Compare
__vector_12:    JMP     __unhandled_interrupt      ;     12       0x0030       TWI C Slave Interrupt
__vector_13:    JMP     __unhandled_interrupt      ;     13       0x0034       TWI C Master Interrupt
__vector_14:    JMP     pushbutton_timer_isr       ;     14       0x0038       Timer C0 Overflow
__vector_15:    JMP     __unhandled_interrupt      ;     15       0x003C       Timer C0 Error
__vector_16:    JMP     __unhandled_interrupt      ;     16       0x0040       Timer C0 Compare or Capture A
__vector_17:    JMP     __unhandled_interrupt      ;     17       0x0044       Timer C0 Compare or Capture B
__vector_18:    JMP     __unhandled_interrupt      ;     18       0x0048       Timer C0 Compare or Capture C
__vector_19:    JMP     __unhandled_interrupt      ;     19       0x004C       Timer C0 Compare or Capture D
__vector_20:    JMP     TickISR 			       ;     20       0x0050       Timer C1 Overflow
__vector_21:    JMP     __unhandled_interrupt      ;     21       0x0054       Timer C1 Error
__vector_22:    JMP     __unhandled_interrupt      ;     22       0x0058       Timer C1 Compare or Capture A
__vector_23:    JMP     __unhandled_interrupt      ;     23       0x005C       Timer C1 Compare or Capture B
__vector_24:    JMP     __unhandled_interrupt      ;     24       0x0060       SPI C
__vector_25:    JMP     usartc0_rx_isr             ;     25       0x0064       USART C0 Rx Complete
__vector_26:    JMP     __unhandled_interrupt      ;     26       0x0068       USART C0 Data Register Empty
__vector_27:    JMP     __unhandled_interrupt      ;     27       0x006C       USART C0 Tx Complete
__vector_28:    JMP     __unhandled_interrupt      ;     28       0x0070       USART C1 Rx Complete
__vector_29:    JMP     __unhandled_interrupt      ;     29       0x0074       USART C1 Data Register Empty
__vector_30:    JMP     __unhandled_interrupt      ;     30       0x0078       USART C1 Tx Complete
__vector_31:    JMP     __unhandled_interrupt      ;     31       0x007C       AES interrupt vector
__vector_32:    JMP     __unhandled_interrupt      ;     32       0x0080       NVM EE
__vector_33:    JMP     __unhandled_interrupt      ;     33       0x0084       NVM SPM
__vector_34:    JMP     __unhandled_interrupt      ;     34       0x0088       Port B External Interrupt 0
__vector_35:    JMP     __unhandled_interrupt      ;     35       0x008C       Port B External  Interrupt 1
__vector_36:    JMP     __unhandled_interrupt      ;     36       0x008C       Analog Comparator B Window Mode
__vector_37:    JMP     __unhandled_interrupt      ;     37       0x0090       Analog Comparator B Comparator 1
__vector_38:    JMP     __unhandled_interrupt      ;     38       0x0094       Analog Comparator B Comparator 0
__vector_39:    JMP     __unhandled_interrupt      ;     39       0x0098       ADC B CH0
__vector_40:    JMP     __unhandled_interrupt      ;     40       0x009C       ADC B CH1
__vector_41:    JMP     __unhandled_interrupt      ;     41       0x00A0       ADC B CH2
__vector_42:    JMP     __unhandled_interrupt      ;     42       0x00A4       ADC B CH3
__vector_43:    JMP     __unhandled_interrupt      ;     43       0x00A8       Port E External Interrupt 0
__vector_44:    JMP     __unhandled_interrupt      ;     44       0x00AC       Port E External Interrupt 1
__vector_45:    JMP     __unhandled_interrupt      ;     45       0x00B0       TWI E Slave Interrupt
__vector_46:    JMP     __unhandled_interrupt      ;     46       0x00B4       TWI E Master Interrupt
__vector_47:    JMP     __unhandled_interrupt      ;     47       0x00B8       Timer  E0  Overflow
__vector_48:    JMP     __unhandled_interrupt      ;     48       0x00BC       Timer  E0  Error
__vector_49:    JMP     __unhandled_interrupt      ;     49       0x00C0       Timer  E0  Compare or Capture A
__vector_50:    JMP     __unhandled_interrupt      ;     50       0x00C4       Timer  E0  Compare or Capture B
__vector_51:    JMP     __unhandled_interrupt      ;     51       0x00C8       Timer  E0  Compare or Capture C
__vector_52:    JMP     __unhandled_interrupt      ;     52       0x00CC       Timer  E0  Compare or Capture D
__vector_53:    JMP     __unhandled_interrupt      ;     53       0x00D0       Timer  E1  Overflow
__vector_54:    JMP     __unhandled_interrupt      ;     54       0x00D4       Timer  E1  Error
__vector_55:    JMP     __unhandled_interrupt      ;     55       0x00D8       Timer  E1  Compare or Capture A
__vector_56:    JMP     __unhandled_interrupt      ;     56       0x00DC       Timer  E1  Compare or Capture B
__vector_57:    JMP     __unhandled_interrupt      ;     57       0x00E0       SPI    E
__vector_58:    JMP     __unhandled_interrupt      ;     58       0x00E4       USART E0 Rx Complete
__vector_59:    JMP     __unhandled_interrupt      ;     59       0x00E8       USART E0 Data Register Empty
__vector_60:    JMP     __unhandled_interrupt      ;     60       0x00EC       USART E0 Tx Complete
__vector_61:    JMP     __unhandled_interrupt      ;     61       0x00F0       USART E1 Rx Complete
__vector_62:    JMP     __unhandled_interrupt      ;     62       0x00F4       USART E1 Data Register Empty
__vector_63:    JMP     __unhandled_interrupt      ;     63       0x00F8       USART E1 Tx Complete
__vector_64:    JMP     __unhandled_interrupt      ;     64       0x00FC       Port  D External Interrupt 0
__vector_65:    JMP     __unhandled_interrupt      ;     65       0x0100       Port  D External Interrupt 1
__vector_66:    JMP     __unhandled_interrupt      ;     66       0x0104       Port  A External Interrupt 0
__vector_67:    JMP     __unhandled_interrupt      ;     67       0x0108       Port  A External Interrupt 1
__vector_68:    JMP     __unhandled_interrupt      ;     68       0x010C       Analog Comparator A Window Mode 
__vector_69:    JMP     __unhandled_interrupt      ;     69       0x0110       Analog Comparator A Comparator 1
__vector_70:    JMP     __unhandled_interrupt      ;     70       0x0114       Analog Comparator A Comparator 0
__vector_71:    JMP     __unhandled_interrupt      ;     71       0x0118       ADC A CH0
__vector_72:    JMP     __unhandled_interrupt      ;     72       0x011C       ADC A CH1
__vector_73:    JMP     __unhandled_interrupt      ;     73       0x0120       ADC A CH2
__vector_74:    JMP     __unhandled_interrupt      ;     74       0x0124       ADC A CH3
__vector_75:    JMP     __unhandled_interrupt      ;     75       0x0128       TWI D Slave Interrupt
__vector_76:    JMP     __unhandled_interrupt      ;     76       0x012C       TWI D Master Interrupt
__vector_77:    JMP     __unhandled_interrupt      ;     77       0x0130       Timer D0 Overflow
__vector_78:    JMP     __unhandled_interrupt      ;     78       0x0134       Timer D0 Error
__vector_79:    JMP     __unhandled_interrupt      ;     79       0x0138       Timer D0 Compare or Capture A
__vector_80:    JMP     __unhandled_interrupt      ;     80       0x013C       Timer D0 Compare or Capture B
__vector_81:    JMP     __unhandled_interrupt      ;     81       0x0140       Timer D0 Compare or Capture C
__vector_82:    JMP     __unhandled_interrupt      ;     82       0x0144       Timer D0 Compare or Capture D
__vector_83:    JMP     __unhandled_interrupt      ;     83       0x0148       Timer D1 Overflow
__vector_84:    JMP     __unhandled_interrupt      ;     84       0x014C       Timer D1 Error
__vector_85:    JMP     __unhandled_interrupt      ;     85       0x0150       Timer D1 Compare or Capture A
__vector_86:    JMP     __unhandled_interrupt      ;     86       0x0154       Timer D1 Compare or Capture B
__vector_87:    JMP     __unhandled_interrupt      ;     87       0x0158       SPI   D
__vector_88:    JMP     __unhandled_interrupt      ;     88       0x015C       USART D0 Rx Complete
__vector_89:    JMP     __unhandled_interrupt      ;     89       0x0160       USART D0 Data Register Empty
__vector_90:    JMP     __unhandled_interrupt      ;     90       0x0164       USART D0 Tx Complete
__vector_91:    JMP     __unhandled_interrupt      ;     91       0x0168       USART D1 RxComplete
__vector_92:    JMP     __unhandled_interrupt      ;     92       0x016C       USART D1 Data Register Empty 
__vector_93:    JMP     __unhandled_interrupt      ;     93       0x0170       USART D1 Tx Complete
__vector_94:    JMP     __unhandled_interrupt      ;     94       0x0174       PortQ External Interrupt 0 
__vector_95:    JMP     __unhandled_interrupt      ;     95       0x0178       PortQ External Interrupt 1.
__vector_96:    JMP     __unhandled_interrupt      ;     96       0x017C       PortH External Interrupt 0.
__vector_97:    JMP     __unhandled_interrupt      ;     97       0x0180       PortH External Interrupt 1.
__vector_98:    JMP     __unhandled_interrupt      ;     98       0x0184       PortJ External Interrupt 0.
__vector_99:    JMP     __unhandled_interrupt      ;     99       0x0188       PortJ External Interrupt 1.
__vector_100:   JMP     __unhandled_interrupt      ;    100       0x018C       PortK External Interrupt 0 
__vector_101:   JMP     __unhandled_interrupt      ;    101       0x0190       PortK External Interrupt 1 
__vector_102:   JMP     __unhandled_interrupt      ;    102       Reserved
__vector_103:   JMP     __unhandled_interrupt      ;    103       Reserved
__vector_104:   JMP     __unhandled_interrupt      ;    104       0x019C       Port F External Interrupt 0 
__vector_105:   JMP     __unhandled_interrupt      ;    105       0x01A0       Port F External Interrupt 1 
__vector_106:   JMP     __unhandled_interrupt      ;    106       0x01A4       TWI  F Slave    Interrupt
__vector_107:   JMP     __unhandled_interrupt      ;    107       0x01A8       TWI  F Master   Interrupt
__vector_108:   JMP     __unhandled_interrupt      ;    108       0x01AC       Timer F0 Overflow
__vector_109:   JMP     __unhandled_interrupt      ;    109       0x01B0       Timer F0 Error
__vector_110:   JMP     __unhandled_interrupt      ;    110       0x01B4       Timer F0 Compare or Capture A
__vector_111:   JMP     __unhandled_interrupt      ;    111       0x01B8       Timer F0 Compare or Capture B
__vector_112:   JMP     __unhandled_interrupt      ;    112       0x01BC       Timer F0 Compare or Capture C
__vector_113:   JMP     __unhandled_interrupt      ;    113       0x01C0       Timer F0 Compare or Capture D
__vector_114:   JMP     __unhandled_interrupt      ;    114       0x01C4       Timer F1 Overflow
__vector_115:   JMP     __unhandled_interrupt      ;    115       0x01C8       Timer F1 Error
__vector_116:   JMP     __unhandled_interrupt      ;    116       0x01CC       Timer F1 Compare or Capture A
__vector_117:   JMP     __unhandled_interrupt      ;    117       0x01D0       Timer F1 Compare or Capture B
__vector_118:   JMP     __unhandled_interrupt      ;    118       0x01D4       SPI F
__vector_119:   JMP     usartf0_rx_isr             ;    119       0x01D8       USART F0 Rx  Complete
__vector_120:   JMP     __unhandled_interrupt      ;    120       0x01DC       USART F0 Data Register Empty
__vector_121:   JMP     __unhandled_interrupt      ;    121       0x01E0       USART F0 Tx Complete
__vector_122:   JMP     __unhandled_interrupt      ;    122       0x01E4       USART F1 Rx Complete
__vector_123:   JMP     __unhandled_interrupt      ;    123       0x01E8       USART F1 Data Register Empty
__vector_124:   JMP     __unhandled_interrupt      ;    124       0x01EC       USART F1 Tx Complete

__unhandled_interrupt:	;JMP     __unhandled_interrupt
