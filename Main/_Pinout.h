/*
          esp32                                           MSE-DuinoV2
number    pins         description                        Brd Jumpers /Labels                                                                  User (Fill in chart with user PIN usage)
          1             3v3                               PWR 3V3                                                                              3V3
          2             gnd                               GND                                                                                  GND
15        3             GPIO15/AD2_3/T3/SD_CMD/           D15 (has connections in both 5V and 3V areas)                                        Servo
2         4             GPIO2/AD2_2/T2/SD_D0              D2(has connections in both 5V and 3V areas)  /INDICATORLED ( On ESP32 board )        Heartbeat LED
4         5             GPIO4/AD2_0/T0/SD_D1              D4(has connections in both 5V and 3V areas)                                          Left Motor, Channel A
16        6             GPIO16/RX2                        Slide Switch S1b                                                                     IR Receiver
17        7             GPIO17/TX2                        Slide Switch S2b                                                                     Left Encoder, Channel A
5         8             GPIO5                             D5 (has connections in both 5V and 3V areas)                                         Left Encoder, Channel B
18        9             GPIO18                            D18 (has connections in both 5V and 3V areas)                                        Left Motor, Channel B
19        10            GPIO19/CTS0                       D19 (has connections in both 5V and 3V areas)                                        Right Motor, Channel A
21        11            GPIO21                            D21/I2C_DA
3         12            GPIO3/RX0                         RX0
1         13            GPIO1//TX0                        TX0
22        14            GPIO22/RTS1                       D22/I2C_CLK                                                                       
23        15            GPIO23                            D23 (has connections in both 5V and 3V areas)                                        Ultrasound echo
          16            EN                                JP4 (Labeled - RST) for reseting ESP32
36        17            GPI36/VP/AD1_0                    AD0
39        18            GPI39/VN/AD1_3/                   AD3
34        19            GPI34/AD1_6/                      AD6
35        20            GPI35/AD1_7                       Potentiometer R2 / AD7
32        21            GPIO32/AD1_4/T9                   Potentiometer R1 / AD4                                                               Pot 1 (R1)
33        22            GPIO33/AD1_5/T8                   IMon/D33  monitor board current
25        23            GPIO25/AD2_8/DAC1                 SK6812 Smart LEDs / D25                                                              Smart LEDs
26        24            GPIO26/A2_9/DAC2                  Push Button PB2                                                                      Limit switch
27        25            GPIO27/AD2_7/T7                   Push Button PB1                                                                      PB1
14        26            GPOP14/AD2_6/T6/SD_CLK            Slide Switch S2a                                                                     Right Encoder, Channel A
12        27            GPIO12/AD2_5/T5/SD_D2/            D12(has connections in both 5V and 3V areas)                                         Right Motor, Channel B
13        28            GPIO13/AD2_4/T4/SD_D3/            Slide Switch S1a                                                                     Right Encoder, Channel B
          29            GND                               GND                                                                                  GND
          30            VIN                               PWR 5V t 7V                                                                          PWR 5V to 7V
*/

#define pinUStrig      26  //grey lead
#define pinUSecho      23  //white lead
#define pinIR          16
#define pinMotorRightA 19
#define pinMotorRightB 12
#define pinMotorLeftA  4
#define pinMotorLeftB  18
#define pinEncRightA   14
#define pinEncRightB   13
#define pinEncLeftA    17
#define pinEncLeftB    5
#define pinSonarServo  15
#define pinWinch       32
#define pinSmartLED    25
#define pinStatusLED   2
#define pinButton      27
#define pinLockServo   33
