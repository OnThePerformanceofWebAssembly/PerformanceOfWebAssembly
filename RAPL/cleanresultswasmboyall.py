#!/usr/local/bin/python3
#import pandas as pd
import re
import sys
import os
#import matplotlib.pyplot as plt
import os.path
from os import path
# importing the statistics module
from statistics import median
from statistics import mean
# Importing fractions module as fr
from fractions import Fraction as fr

def raplclean(url2):
    frapl = open(url2,"r")
    rapl = frapl.read()
    rapl = re.sub(r"\s,\s",",",rapl)
    rapl = re.sub(r'([-](?=\.\d|\d)(?:\d+)?(?:\.?\d*))(?:[eE]([+-]?\d+))?', "0.0", rapl)
    frapl.close()
    frapl = open(url2,"w")
    frapl.write(rapl)
    frapl.close()
    return frapl


def crp(url1,url2,txt,m1,nexecution,browser,language): #Processar dados e organizar
    energySpent = {}
    results = {}
    frapl = open(url2, "r")
    text = frapl.read()
    text = re.split(r'\n',text)
    vals = re.split(r',',text[0])
    #Adicionar os valores do RAPL aos resultados
    for i in vals:
        results[i] = []
        energySpent[i] = 0.0
    for line in text[1:]:
        aux = re.split(r',',line)
        if aux == [''] :
            continue
        j = 0
        for i in vals:
            if( j==0 and float(aux[j]) <= 0):
                continue
            results[i].append(float(aux[j]))
            energySpent[i] += float(aux[j])
            j = j+1
    frapl.close()
    #Adicionar os valores do time aos resultados
    if(path.exists(urltime)):
        ftime = open(url1, "r")
        text = ftime.read()
        text = re.split(r'\n',text)
        results[text[0]] = []
        energySpent[text[0]] = 0.0
        for line in text[1:]:
            results[text[0]].append(float(line))
            energySpent[text[0]]+=float(line)
        ftime.close()
    printSoma(energySpent,txt,urlrapl,m1,nexecution,browser,language)
          

## Resultados - Energia Gasta 
def printSoma(energySpent,text,urlrapl,m1,nexecution,browser,language):
    txt = browser + "," + language + "," + str(nexecution)+","
    #print("Somas de ",urlrapl," :")
    for i in energySpent.keys():
        if(i == "Time"):
            m1[i].append(energySpent[i])
            #print("Execution",i,":",energySpent[i],"S")
            txt = txt + str("{:.3f}".format(energySpent[i])) +"\n"

        elif(i == "GPU"):
            m1[i].append(energySpent[i])
            txt = txt + "0" + ","
        else:
            m1[i].append(energySpent[i])
            #print("Energy Spent on Rapl -",i,":",energySpent[i],"J")            
            txt = txt + str("{:.3f}".format(energySpent[i])) + ","
    finalfile = open(text+"all.csv", "a+") 
    finalfile.write(txt)
    finalfile.close()            

def printmediana(text,m1,browser,language):
    txt=browser+","+language+","
    for i in m1.keys():
        if(i == "Time"): # para dar \n
            t1 = tuple(m1[i])
            x = median(t1)
            #print("Median of Time Spent -",i,":",x,"S")            
            txt = txt + str("{:.3f}".format(x)) + "\n"
        elif(i == "GPU"):
            txt=txt
        else:
            t1 = tuple(m1[i])
            x = median(t1)
            #print("Median of Energy Spent on Rapl -",i,":",x,"J")            
            txt = txt + str("{:.3f}".format(x)) + ","
    finalfile = open(text+"all.csv", "a+") 
    finalfile.write(txt)
    finalfile.close()         

def printmedia(text,m1,browser,language):
    txt=browser+","+language+","+"Mean,"
    for i in m1.keys():
        if (i == "Time"):
            t1 = tuple(m1[i])
            x = mean(t1)
            #print("Mean of Time Spent -",i,":",x,"S")
            txt = txt + str("{:.3f}".format(x)) + "\n"
        else:
            t1 = tuple(m1[i])
            x = mean(t1)
            #print("Median of Energy Spent on Rapl -",i,":",x,"J")            
            txt = txt + str("{:.3f}".format(x)) + ","
    finalfile = open(text+"all.csv", "a+") 
    finalfile.write(txt)
    finalfile.close() 

##tratar dos resultados

text = sys.argv[1] # tobutobugirl
finalfile = open(text+"all.csv", "w") 
finalfile.write("Browser,Language,N,Package,CPU,GPU,DRAM,Time\n")
finalfile.close()

cwds= [os.getcwd(),os.getcwd()]
cwds[0]+= "/TS/Results/"
cwds[1]+= "/Wasm/Results/"
for cwd in cwds:
    for filename in os.listdir(cwd): # filename: GoogleChrome
        f = os.path.join(cwd, filename) # f: /home/diguest/Desktop/MSc/OnThePerformanceOfWebAssembly/WasmBoy/TobuTobuGirl/Wasm/Results/GoogleChrome
        if os.path.isdir(f):
            caminho = f.rsplit('/', 3)
            browser = caminho[3]
            language = caminho[1]
            for i in range(1,6):
                    urltime = f+"/"+text+str(i)+".time"
                    urlrapl = f+"/"+text+str(i)+".rapl"
                    if(path.exists(urlrapl)):
                        if(i==1):
                            m1 = {}
                            m1["Package"] = []
                            m1["CPU"] = []
                            m1["GPU"] = []
                            m1["DRAM"] = []
                            m1["Time"] = []
                            finalfile = open(text+"all.csv", "a+") 
                            #finalfile.write("Browser,Language,N,Package,CPU,GPU,DRAM,Time\n")
                            finalfile.close()
                        raplclean(urlrapl)
                        crp(urltime,urlrapl,text,m1,i,browser,language)
            #printmediana(text,m1,browser,language)
            #printmedia(text,m1,browser,language)

