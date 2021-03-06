EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "XTerminal"
Date "2021-12-03"
Rev "v1.0"
Comp "LithiumStudio"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-PICO-D4 U?
U 1 1 61A72BC1
P 3900 3700
F 0 "U?" H 3900 2011 50  0000 C CNN
F 1 "ESP32-PICO-D4" H 3900 1920 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-48-1EP_7x7mm_P0.5mm_EP5.3x5.3mm" H 3900 2000 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf" H 4150 2700 50  0001 C CNN
	1    3900 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR?
U 1 1 61AA2E89
P 3700 1800
F 0 "#PWR?" H 3700 1650 50  0001 C CNN
F 1 "+3.3VA" H 3715 1973 50  0000 C CNN
F 2 "" H 3700 1800 50  0001 C CNN
F 3 "" H 3700 1800 50  0001 C CNN
	1    3700 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61AA4CCF
P 5350 1250
F 0 "#PWR?" H 5350 1100 50  0001 C CNN
F 1 "+3.3V" H 5365 1423 50  0000 C CNN
F 2 "" H 5350 1250 50  0001 C CNN
F 3 "" H 5350 1250 50  0001 C CNN
	1    5350 1250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR?
U 1 1 61AA6B01
P 5350 1550
F 0 "#PWR?" H 5350 1400 50  0001 C CNN
F 1 "+3.3VA" H 5365 1723 50  0000 C CNN
F 2 "" H 5350 1550 50  0001 C CNN
F 3 "" H 5350 1550 50  0001 C CNN
	1    5350 1550
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 61AA7129
P 5350 1400
F 0 "R?" H 5418 1446 50  0000 L CNN
F 1 "0R" H 5418 1355 50  0000 L CNN
F 2 "" H 5350 1400 50  0001 C CNN
F 3 "~" H 5350 1400 50  0001 C CNN
	1    5350 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1250 5350 1300
Wire Wire Line
	5350 1500 5350 1550
Wire Wire Line
	3700 1800 3700 2100
$Comp
L Device:Q_PMOS_GSD Q?
U 1 1 61ACF08E
P 8150 3800
F 0 "Q?" V 8492 3800 50  0000 C CNN
F 1 "Q_PMOS_GSD" V 8401 3800 50  0000 C CNN
F 2 "" H 8350 3900 50  0001 C CNN
F 3 "~" H 8150 3800 50  0001 C CNN
	1    8150 3800
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 61ACFF96
P 8050 4700
F 0 "Q?" H 8254 4746 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 8254 4655 50  0000 L CNN
F 2 "" H 8250 4800 50  0001 C CNN
F 3 "~" H 8050 4700 50  0001 C CNN
	1    8050 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61AD18BE
P 6400 1350
F 0 "C?" H 6492 1396 50  0000 L CNN
F 1 "C_Small" H 6492 1305 50  0000 L CNN
F 2 "" H 6400 1350 50  0001 C CNN
F 3 "~" H 6400 1350 50  0001 C CNN
	1    6400 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 61AD202B
P 7000 1350
F 0 "R?" H 7068 1396 50  0000 L CNN
F 1 "0R" H 7068 1305 50  0000 L CNN
F 2 "" H 7000 1350 50  0001 C CNN
F 3 "~" H 7000 1350 50  0001 C CNN
	1    7000 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61AD259E
P 7500 1450
F 0 "#PWR?" H 7500 1300 50  0001 C CNN
F 1 "+3.3V" H 7515 1623 50  0000 C CNN
F 2 "" H 7500 1450 50  0001 C CNN
F 3 "" H 7500 1450 50  0001 C CNN
	1    7500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR?
U 1 1 61AD289E
P 7950 1450
F 0 "#PWR?" H 7950 1300 50  0001 C CNN
F 1 "+3.3VA" H 7965 1623 50  0000 C CNN
F 2 "" H 7950 1450 50  0001 C CNN
F 3 "" H 7950 1450 50  0001 C CNN
	1    7950 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61AD326B
P 8750 1300
F 0 "#PWR?" H 8750 1050 50  0001 C CNN
F 1 "GND" H 8755 1127 50  0000 C CNN
F 2 "" H 8750 1300 50  0001 C CNN
F 3 "" H 8750 1300 50  0001 C CNN
	1    8750 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 61AD368A
P 8300 1450
F 0 "#PWR?" H 8300 1300 50  0001 C CNN
F 1 "+5V" H 8315 1623 50  0000 C CNN
F 2 "" H 8300 1450 50  0001 C CNN
F 3 "" H 8300 1450 50  0001 C CNN
	1    8300 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 61AD3CDA
P 9050 1350
F 0 "#PWR?" H 9050 1100 50  0001 C CNN
F 1 "GNDA" H 9055 1177 50  0000 C CNN
F 2 "" H 9050 1350 50  0001 C CNN
F 3 "" H 9050 1350 50  0001 C CNN
	1    9050 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 61AD53F7
P 7700 3850
F 0 "R?" H 7768 3896 50  0000 L CNN
F 1 "20K" H 7768 3805 50  0000 L CNN
F 2 "" H 7700 3850 50  0001 C CNN
F 3 "~" H 7700 3850 50  0001 C CNN
	1    7700 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 61AD6276
P 8800 3800
F 0 "R?" H 8868 3846 50  0000 L CNN
F 1 "100K" H 8868 3755 50  0000 L CNN
F 2 "" H 8800 3800 50  0001 C CNN
F 3 "~" H 8800 3800 50  0001 C CNN
	1    8800 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 61AD6845
P 8800 4150
F 0 "R?" H 8868 4196 50  0000 L CNN
F 1 "100K" H 8868 4105 50  0000 L CNN
F 2 "" H 8800 4150 50  0001 C CNN
F 3 "~" H 8800 4150 50  0001 C CNN
	1    8800 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61AD6E82
P 8800 4400
F 0 "#PWR?" H 8800 4150 50  0001 C CNN
F 1 "GND" H 8805 4227 50  0000 C CNN
F 2 "" H 8800 4400 50  0001 C CNN
F 3 "" H 8800 4400 50  0001 C CNN
	1    8800 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 61AD84C9
P 7200 5700
F 0 "R?" H 7268 5746 50  0000 L CNN
F 1 "20K" H 7268 5655 50  0000 L CNN
F 2 "" H 7200 5700 50  0001 C CNN
F 3 "~" H 7200 5700 50  0001 C CNN
	1    7200 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61AD8947
P 7200 5900
F 0 "#PWR?" H 7200 5650 50  0001 C CNN
F 1 "GND" H 7205 5727 50  0000 C CNN
F 2 "" H 7200 5900 50  0001 C CNN
F 3 "" H 7200 5900 50  0001 C CNN
	1    7200 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D?
U 1 1 61AD92EF
P 6000 1350
F 0 "D?" H 6000 1557 50  0000 C CNN
F 1 "D_Small" H 6000 1466 50  0000 C CNN
F 2 "" V 6000 1350 50  0001 C CNN
F 3 "~" V 6000 1350 50  0001 C CNN
	1    6000 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D?
U 1 1 61AD9A4B
P 7650 5400
F 0 "D?" H 7650 5607 50  0000 C CNN
F 1 "D_Small" H 7650 5516 50  0000 C CNN
F 2 "" V 7650 5400 50  0001 C CNN
F 3 "~" V 7650 5400 50  0001 C CNN
	1    7650 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D?
U 1 1 61ADA565
P 9550 4850
F 0 "D?" H 9550 5057 50  0000 C CNN
F 1 "D_Small" H 9550 4966 50  0000 C CNN
F 2 "" V 9550 4850 50  0001 C CNN
F 3 "~" V 9550 4850 50  0001 C CNN
	1    9550 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D?
U 1 1 61ADB2A5
P 9150 4850
F 0 "D?" H 9150 4643 50  0000 C CNN
F 1 "D_Small" H 9150 4734 50  0000 C CNN
F 2 "" V 9150 4850 50  0001 C CNN
F 3 "~" V 9150 4850 50  0001 C CNN
	1    9150 4850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61ADBB88
P 8150 5000
F 0 "#PWR?" H 8150 4750 50  0001 C CNN
F 1 "GND" H 8155 4827 50  0000 C CNN
F 2 "" H 8150 5000 50  0001 C CNN
F 3 "" H 8150 5000 50  0001 C CNN
	1    8150 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 5000 8150 4900
Wire Wire Line
	8150 4500 8150 4100
Wire Wire Line
	7700 3950 7700 4100
Wire Wire Line
	7700 4100 8150 4100
Connection ~ 8150 4100
Wire Wire Line
	8150 4100 8150 4000
Wire Wire Line
	7950 3700 7700 3700
Wire Wire Line
	7700 3700 7700 3750
$Comp
L power:VDD #PWR?
U 1 1 61ADD335
P 8500 1450
F 0 "#PWR?" H 8500 1300 50  0001 C CNN
F 1 "VDD" H 8515 1623 50  0000 C CNN
F 2 "" H 8500 1450 50  0001 C CNN
F 3 "" H 8500 1450 50  0001 C CNN
	1    8500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 61ADE120
P 7700 3350
F 0 "#PWR?" H 7700 3200 50  0001 C CNN
F 1 "VDD" H 7715 3523 50  0000 C CNN
F 2 "" H 7700 3350 50  0001 C CNN
F 3 "" H 7700 3350 50  0001 C CNN
	1    7700 3350
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 61ADF494
P 9350 1400
F 0 "#FLG?" H 9350 1475 50  0001 C CNN
F 1 "PWR_FLAG" H 9350 1573 50  0000 C CNN
F 2 "" H 9350 1400 50  0001 C CNN
F 3 "~" H 9350 1400 50  0001 C CNN
	1    9350 1400
	1    0    0    -1  
$EndComp
$Comp
L power:VEE #PWR?
U 1 1 61AE157F
P 8650 1450
F 0 "#PWR?" H 8650 1300 50  0001 C CNN
F 1 "VEE" H 8665 1623 50  0000 C CNN
F 2 "" H 8650 1450 50  0001 C CNN
F 3 "" H 8650 1450 50  0001 C CNN
	1    8650 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3350 7700 3700
Connection ~ 7700 3700
Wire Wire Line
	8350 3700 8800 3700
Wire Wire Line
	8800 4250 8800 4300
Wire Wire Line
	9200 4300 8800 4300
Text Label 9650 4000 2    50   ~ 0
BAT_DET
$Comp
L power:VEE #PWR?
U 1 1 61AE3A89
P 8800 3350
F 0 "#PWR?" H 8800 3200 50  0001 C CNN
F 1 "VEE" H 8815 3523 50  0000 C CNN
F 2 "" H 8800 3350 50  0001 C CNN
F 3 "" H 8800 3350 50  0001 C CNN
	1    8800 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 3350 8800 3700
Connection ~ 8800 3700
Wire Wire Line
	7850 4700 7200 4700
Wire Wire Line
	7200 4700 7200 5400
Wire Wire Line
	7200 5800 7200 5900
Wire Wire Line
	7550 5400 7200 5400
Connection ~ 7200 5400
Wire Wire Line
	7200 5400 7200 5600
Wire Wire Line
	7750 5400 8400 5400
Text Label 8400 5400 2    50   ~ 0
PWR_EN
Wire Wire Line
	9050 4850 8500 4850
Wire Wire Line
	8500 4850 8500 4100
Wire Wire Line
	8500 4100 8150 4100
Wire Wire Line
	9250 4850 9350 4850
Wire Wire Line
	9650 4850 10200 4850
Text Label 10200 4850 2    50   ~ 0
EC_KEY_DET
Text Label 9750 5150 2    50   ~ 0
EC_KEY
Wire Wire Line
	9750 5150 9350 5150
Wire Wire Line
	9350 5150 9350 4850
Connection ~ 9350 4850
Wire Wire Line
	9350 4850 9450 4850
Connection ~ 8800 4300
Wire Wire Line
	8800 4300 8800 4400
Wire Wire Line
	9200 4250 9200 4300
Wire Wire Line
	8800 3900 8800 4000
$Comp
L Device:C_Small C?
U 1 1 61AD74FA
P 9200 4150
F 0 "C?" H 9292 4196 50  0000 L CNN
F 1 "0.1uF" H 9292 4105 50  0000 L CNN
F 2 "" H 9200 4150 50  0001 C CNN
F 3 "~" H 9200 4150 50  0001 C CNN
	1    9200 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 4000 9200 4000
Wire Wire Line
	9200 4000 9200 4050
Wire Wire Line
	9200 4000 8800 4000
Connection ~ 9200 4000
Connection ~ 8800 4000
Wire Wire Line
	8800 4000 8800 4050
$EndSCHEMATC
