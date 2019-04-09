#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 9 16:22:48 2019

@author: jean mario m lima
"""

from ufrn_al5d import RoboticArmAL5D
import time


###################################
######    CANAIS DOS SERVOS  ###### 
###### E LIMITES DE OPERAÇÃO ######
###################################
#0. BASE
BAS_SERVO = 0
#LIMITES
BAS_MIN = 500
BAS_MAX = 2400

#1. SHOULDER
SHL_SERVO = 1
#LIMITES
SHL_MIN = 1200
SHL_MAX = 2000

#2. ELBOW
ELB_SERVO = 2
#LIMITES
ELB_MIN = 1100
ELB_MAX = 2000

#3. WRIST
WRI_SERVO = 3
#LIMITES
WRI_MIN = 500
WRI_MAX = 2500

#4. GRIPPER
GRI_SERVO = 4
#LIMITES
GRI_MIN = 1300
GRI_MAX = 2400

#PROPRIEDADES DO BRAÇO: SERVOS E LIMITES DE OPERACAO
properties = [BAS_SERVO, BAS_MIN, BAS_MAX,
              SHL_SERVO, SHL_MIN, SHL_MAX,
              ELB_SERVO, ELB_MIN, ELB_MAX,
              WRI_SERVO, WRI_MIN, WRI_MAX,
              GRI_SERVO, GRI_MIN, GRI_MAX]
##################################

##################################
#######    PROGRAMA DEMO   #######
##################################

#POSICAO INICIAL PARA TODOS OS SERVOS
HOME_POS = '#0P1500#1P1500#2P1500#3P1500#4P1500T1500'

#INICIALIZACAO DO BRACO PASSANDO AS PROPRIEDADES COMO PARAMETRO
braco = RoboticArmAL5D(properties)

#CONFIGURACAO DA PORTA
braco.setup()

#ABRINDO A PORTA
braco.abre_porta()

braco.envia_comando(HOME_POS)

    
    
    
    

