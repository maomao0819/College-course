# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import re
df = pd.read_csv('ScoreData.csv')
df.drop(['id'],axis=1,inplace=True)
df.drop(['Dep'],axis=1,inplace=True)
df.drop(['Grd'],axis=1,inplace=True)
df.drop(['Unnamed: 0'],axis=1,inplace=True)
lis=list(df)
array=np.zeros([98,1])
for i in lis:
    temp=np.zeros([98,1])
    count=0
    for j in df[i]:
        j=re.sub('[?!@#$abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]', '',str(j))
        temp[count]=j
        count+=1
    array=np.hstack((array,temp))
array=np.delete(array,0,1)

index=np.arange(98)
df=pd.DataFrame(array,index,lis)
total=df.sum(axis=1)
index2=[index for index in df]
df=df.T
index1=[x for x in range (98)]
tt=plt.plot(index1,total)
plt.xlabel('index')
plt.ylabel('point')
plt.title('total for each people')
plt.show(tt)

average=total/16
av=plt.scatter(index1,average,color='green',linestyle='--')
plt.xlabel('index')
plt.ylabel('point')
plt.title('average for each people')
plt.show(av)
total2=df.sum(axis=1)

'''tt2=plt.plot(index2,total2)
plt.xlabel('index')
plt.ylabel('total2')
plt.title('total2')
plt.show(tt2)'''

tt2=total2.plot(color='red')
plt.xlabel('index')
plt.ylabel('score')
plt.title('total for each object')
plt.show(tt2)

ttb=plt.boxplot([total])
plt.xlabel('index')
plt.ylabel('point')
plt.title('describe for points')
plt.show(ttb)

ttb2=plt.boxplot([total2])
plt.xlabel('index')
plt.ylabel('point')
plt.title('describe for object difficulty')
plt.show(ttb2)

counts=np.zeros([17])
for i in total:
    if i==1600:
        counts[16]+=1
    elif i<1600 and i>=1500:
        counts[15]+=1
    elif i<1500 and i>=1400:
        counts[14]+=1
    elif i<1400 and i>=1300:
        counts[13]+=1
    elif i<1300 and i>=1200:
        counts[12]+=1
    elif i<1200 and i>=1100:
        counts[11]+=1
    elif i<1100 and i>=1000:
        counts[10]+=1
    elif i<1000 and i>=900:
        counts[9]+=1
    elif i<900 and i>=800:
        counts[8]+=1
    elif i<800 and i>=700:
        counts[7]+=1
    elif i<700 and i>=600:
        counts[6]+=1
    elif i<600 and i>=500:
        counts[5]+=1
    elif i<500 and i>=400:
        counts[4]+=1
    elif i<400 and i>=300:
        counts[3]+=1
    elif i<300 and i>=200:
        counts[2]+=1
    elif i<200 and i>=100:
        counts[1]+=1   
    elif i<100 and i>0:
        counts[0]+=1      
coun=np.arange(17)
cmp=plt.bar(coun,counts,color='purple')
plt.xlabel('points(hundred)')
plt.ylabel('people')
plt.title('compare for people')
plt.show(cmp)

counts=np.zeros([9])
for i in total2:
    if i>=10000:
        counts[8]+=1
    elif i<10000 and i>=9500:
        counts[7]+=1
    elif i<9500 and i>=9000:
        counts[6]+=1
    elif i<9000 and i>=8500:
        counts[5]+=1
    elif i<8500 and i>=8000:
        counts[4]+=1
    elif i<8000 and i>=7500:
        counts[3]+=1
    elif i<7500 and i>=7000:
        counts[2]+=1
    elif i<7000 and i>=6500:
        counts[1]+=1
    elif i<6500:
        counts[0]+=1
coun=['65-',65,70,75,80,85,90,95,100]
cmp2=plt.hist(total2,color='yellow')
plt.xticks(range(6500,10000),100,coun)
plt.xlabel('points(hundred)')
plt.ylabel('object')
plt.title('compare for object')
plt.show(cmp2)

df2=df.T
desc=df2.describe()
desc=desc.T
desc.drop(['count','min','max'],axis=1,inplace=True)
desc.plot()
plt.ylabel('points')
plt.title('describe')

'''total.plot()
average.plot(linestyle='--')
total2.plot(color='red')
plt.xlabel('index')
plt.title('mix')'''

