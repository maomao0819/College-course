# 作業2 報告

**<pre>學生 : 黃秉茂 	學號 : 0616098</pre>**
---
## scanner.l
	
把需要在parser用到的token回傳給parser，因此需要return，幾乎所有的標點符號跟key word都要return，還有回傳string、integer和real。要在header加上#include "y.tab.h"

## parser.y

用%token去接scannar return 的 token， 依據作業要求去完成Program Units、Data Types and Declarations、Statements的grammar和production rule

## Problems you met and solutions

parser完成後scanner突然接不到'\n'，只好全部重寫。而對type的部分也一直看不懂，後來看測資才知道是什麼意思。發生了conflict，一開始只是傻傻的自己想怎麼解決，後來去看parser.output debug方便很多。有些grammar明明能推出一些token list，但卻一直顯示錯誤訊息，後來才發現是自己改的scannar接錯東西了

## Summary

更了解parser和LALR(1)，也更能知道對於目標，要怎麼去完成它的grammar。有些錯誤並不是因為grammar寫錯，可能是因為scanner的token接錯了
