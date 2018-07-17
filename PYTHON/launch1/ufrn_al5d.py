#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 16 13:25:37 2018

@author: jean
"""

import time
import serial
import os
import sys


class RoboticArmAL5D:
    """Driver do Braco Robotico AL5D"""
    #1. Parameters
    def __init__(self,properties):
        self.SERIAL_PORT='/dev/ttyS0' #Serial
        self.BAUD_RATE='115200'       #Set Baud rates to 115200
        self.TIMEOUT='1'              #Timeout after opening
        self.PARITY='N'               # No parity
        self.STOPBITS='1'             
        self.BYTESIZE='8'
        self.XONXOFF = False
        self.RTSCTS = False
        
        #CANAIS DOS SERVOES E LIMITES DE OPERACAO
        self.BAS_SERVO = properties[0]
        self.BAS_MIN = properties[1]
        self.BAS_MAX = properties[2]
        self.SHL_SERVO = properties[3]
        self.SHL_MIN = properties[4]
        self.SHL_MAX = properties[5]
        self.ELB_SERVO = properties[6]
        self.ELB_MIN = properties[7]
        self.ELB_MAX = properties[8]
        self.WRI_SERVO = properties[9]
        self.WRI_MIN = properties[10]
        self.WRI_MAX = properties[11]
        self.GRI_SERVO = properties[12]
        self.GRI_MIN = properties[13]
        self.GRI_MAX = properties[14]


    def header(self):
        print('/*************************************************************/');
        print('/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */');
        print('/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */');
        print('/*							     */');
        print('/*        DRIVER DO BRAÇO ROBÓTICO LYNX AL5D - v2.0 	     */');
        print('/*							     */');
        print('/*   DESENVOLVEDOR:					     */');
        print('/*	- ENG. M.SC. JEAN MÁRIO MOREIRA DE LIMA	             */');
        print('/*************************************************************/\n');

    #2. Setup
    def setup(self):
        self.header()
        try:
            os.system('sudo chmod 777 /dev/ttyS0')
            os.system('sudo rm /dev/ttyS0')  
            os.system('sudo ln -s /dev/ttyUSB0 /dev/ttyS0')   
        except IOError as e:
            print ('SETUP - Erro de E/S({0}): {1}'.format(e.errno, e.strerror))
        except:
            print ('Erro inesperado. Verifique se o braço está ligado e conectado ao computador.', sys.exc_info()[0])
            
        #configura porta
        #serial_port = serial.Serial('/dev/ttyS0',115200)
    def abre_porta(self):
        try:
            self.serial_port = serial.Serial(self.SERIAL_PORT, 
int(self.BAUD_RATE), 
timeout=int(self.TIMEOUT), 
bytesize=int(self.BYTESIZE), 
stopbits=int(self.STOPBITS), 
parity=self.PARITY,
xonxoff = self.XONXOFF,
rtscts= self.RTSCTS)
            self.open_port()
            print ('Porta serial /dev/ttyS0 aberta com sucesso\n')
            return 1
        except IOError as e:
            print ('OPEN PORTA '+e.strerror)
            return -1
        except:
            print ('Erro abrindo a porta serial /dev/ttyS0\nAbortando o programa...\n')
            return -1

    #3. Open serial port    
    def open_port(self):
        if not self.serial_port.is_open:
            self.serial_port.open()
            #print('Porta serial /dev/ttyS0 aberta com sucesso!\n')

    #4. Close Serial Port        
    def fecha_porta(self):
        self.serial_port.close() 
        del self.serial_port
    
    #5 Write 
    def envia_comando(self,cmd):
        n = self.serial_port.write(cmd)
        if n < 0:
            n = -1
            return n
        else:
            return n
    
    def trava(self,channel,pos):
        #BAS_SERVO
        if channel == self.BAS_SERVO:
            if pos < self.BAS_MIN:
                return self.BAS_MIN
            elif pos > self.BAS_MAX:
                return self.BAS_MAX
            else:
                return pos
        #SHL_SERVO
        elif channel == self.SHL_SERVO:
            if pos < self.SHL_MIN:
                return self.SHL_MIN
            elif pos > self.SHL_MAX:
                return self.SHL_MAX
            else:
                return pos
        #ELB_SERVO
        elif channel == self.ELB_SERVO:
            if pos < self.ELB_MIN:
                return self.ELB_MIN
            elif pos > self.ELB_MAX:
                return self.ELB_MAX
            else:
                return pos
        #WRI_SERVO
        elif channel == self.WRI_SERVO:
            if pos < self.WRI_MIN:
                return self.WRI_MIN
            elif pos > self.WRI_MAX:
                return self.WRI_MAX
            else:
                return pos
        #GLI_SERVO
        elif channel == self.GRI_SERVO:
            if pos < self.GRI_MIN:
                return self.GRI_MIN
            elif pos > self.GRI_MAX:
                return self.GRI_MAX
            else:
                return pos
            
            
                

    #6. Simple test    
    def test(self):
        print
        print ('\nObtendo informacoes sobre a comunicacao serial\n')
        time.sleep(2) # Entre 1.5s a 2s
        print ('\nStatus Porta: %s ' % (self.serial_port.isOpen()))
        print ('Device conectado: %s ' % (self.serial_port.name))
        print ('Dump da configuracao:\n %s ' % (self.serial_port))
        print('\n###############################################\n')
        print('HOME POSITION... \n')
        time.sleep(2) # Entre 1.5s a 2s
        self.serial_port.write('#0P1500#1P1500#2P1500#3P1500#4P1500T1500\r')
        time.sleep(2)
        self.envia_comando('#0P2500T1500\r')
        
