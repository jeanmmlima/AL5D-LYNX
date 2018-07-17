#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 16 16:22:48 2018

@author: jean mario m lima
"""

from ufrn_al5d import RoboticArmAL5D
import time

#POSICAO INICIAL PARA TODOS OS SERVOS
HOME_POS = '#0P1500#1P1500#2P1500#3P1500#4P1500T1500\r'

#BRACO INICIALIZADO
braco = RoboticArmAL5D()

#CONFIGURACAO DA PORTA
if(braco.setup() == -1):
    print ('Erro abrindo a porta serial /dev/ttyS0\nAbortando o programa...\n')
else:
    # INICIO DO PROGRAMA DEMO 
    print('PROGRAMA DEMONSTRACAO INICIADO\n\n');
    print ('Porta serial /dev/ttyS0 aberta com sucesso\n')
    
    #############################
    ##### PRIMEIRO COMANDO ######
    #############################
    
    print('\nPRIMEIRO COMANDO - POSICAL INICIAL\n');
    try:
        braco.write(HOME_POS)
        print('Envio de comando com teste de envio: %s \n' % (HOME_POS))
    except:
        print('Problema no envio do comando\nAbortando o programa...')
        
    input("Pressione ENTER para continuar...")
    
    #############################
    ##### SEGUNDO COMANDO #######
    #############################
    
    print('\nSEGUNDO COMANDO - MOVER O PUNHO\n');
    print('Espere 5 segundos...\n');
    time.sleep(5)
    try:
        braco.write('#2P1500T1500\r')
        print('Envio de comando com teste de envio: %s \n' % ('#0P1000T1500\r'))
    except:
        print('Problema no envio do comando\nAbortando o programa...')
        
    input("Pressione ENTER para continuar...")
    
    #############################
    ##### TERCEIRO COMANDO ######
    #############################
    
    print('\nTERCEIRO COMANDO - MOVER A GARRA\n');
    print('Espere 5 segundos...\n');
    time.sleep(5)
    try:
        braco.write('#%dP%dT%d\r' % (4,2500,1500))
        print('Envio de comando com teste de envio: %s \n' % ('#4P2500T1500\r'))
    except:
        print('Problema no envio do comando\nAbortando o programa...')
        
    ##FIM DO PROGRAMA DEMO##
    braco.close_port()
    print('\nAcesso a porta serial /dev/ttyS0 finalizado\n');
    
print('\nPROGRAMA DEMONSTRACAO FINALIZADO\n\n');
    
    
    
    

