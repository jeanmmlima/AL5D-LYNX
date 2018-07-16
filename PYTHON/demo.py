#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 16 16:22:48 2018

@author: jean
"""

from ufrn_al5d import RoboticArmAL5D

#BRACO INICIALIZADO
braco = RoboticArmAL5D()

#CONFIGURACAO DA PORTA

if(braco.setup() == -1):
    print ('Erro abrindo a porta serial /dev/ttyS0\nAbortando o programa...\n')
else:
    print ('Porta serial /dev/ttyS0 aberta com sucesso\n')
    # INICIO DO PROGRAMA DEMO 
    print('PROGRAMA DEMONSTRACAO INICIADO\n\n');

