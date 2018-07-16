#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 16 13:25:37 2018

@author: jean
"""

import time
import serial
import os

#1. Parameters
SERIAL_PORT='/dev/ttyS0' #Serial
BAUD_RATE='115200'       #Set Baud rates to 115200
TIMEOUT='1'              #Timeout after opening
PARITY='N'               # No parity
STOPBITS='1'             
BYTESIZE='8'
XONXOFF = False
RTSCTS = False


def header():
    print('/*************************************************************/\n');
    print('/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */\n');
    print('/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */\n');
    print('/*							     */\n');
    print('/*        DRIVER DO BRAÇO ROBÓTICO LYNX AL5D - v2.0 	     */\n');
    print('/*							     */\n');
    print('/*   DESENVOLVEDOR:					     */\n');
    print('/*	- ENG. M.SC. JEAN MÁRIO MOREIRA DE LIMA	     */\n');
    print('/*************************************************************/\n\n');

#2. Setup
def setup(self):
    os.system('sudo chmod 777 /dev/ttyS0')
    os.system('sudo rm /dev/ttyS0')  
    os.system('sudo ln -s /dev/ttyUSB0 /dev/ttyS0')      
    #configura porta
    #serial_port = serial.Serial('/dev/ttyS0',115200)
    self.serial_port = serial.Serial(SERIAL_PORT, 
int(BAUD_RATE), 
timeout=int(TIMEOUT), 
bytesize=int(BYTESIZE), 
stopbits=int(STOPBITS), 
parity=PARITY,
xonxoff = XONXOFF,
rtscts= RTSCTS)
    header()

#3. Open serial port    
def open_port(self):
    if not self.serial_port.is_open:
        self.serial_port.open()
        print('Porta serial /dev/ttyS0 aberta com sucesso!\n')

#4. Close Serial Port        
def close_port(self):
    self.serial_port.close() 
    del self.serial_port
    
#5 Write 
def write_port(self,cmd):
    n = self.serial_port.write(cmd)
    if n < 0:
        n = -1
        return n
    else:
        return n

#6. Simple test    
def test(self):
    print
    print ('\nObtendo informacoes sobre a comunicacao serial\n')
    time.sleep(1.8) # Entre 1.5s a 2s
    print ('\nStatus Porta: %s ' % (self.serial_port.isOpen()))
    print ('Device conectado: %s ' % (self.serial_port.name))
    print ('Dump da configuracao:\n %s ' % (self.serial_port))
    print('\n###############################################\n')
    print('HOME POSITION... \n')
    time.sleep(2) # Entre 1.5s a 2s
    self.serial_port.write('#0P1500#1P1500#2P1500#3P1500#4P1500T1500\r')
    time.sleep(2)
    write_port('#0P1000T200\r')
    
    
    