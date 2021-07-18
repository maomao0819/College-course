# 作業 3 報告

**<pre>學生 : 黃秉茂 	學號 : 0616098</pre>**
---
## Visitor Pattern

程式先建好node之後，dumpvisit會決定visit的順序，而每個node又會定義自己的子節點的accept，決定該怎麼visit子節點。也就是先寫好程式建好AST後，才慢慢以pre-order的方式visit每個node，而每個node也以pre-order的方式visit每個sub-node

## scanner.l
	
除了HW2要做的東西外，許多之後會用到的token都要加上"yylval.str = strdup(yytext);"，還有把一些IO資訊做修改

## parser.y

要決定何時要有甚麼動作，不論是何時要宣告、要把什麼資料丟進物件等，還會用到很多"$"，把grammer的各處靠著pointer連接起來

## ast.hpp/.cpp

把所有node都會用到的東西寫在裡面

## visitor.hpp

include所有node.hpp，然後先宣告好每個node的visit函式，用virtual。// virtual : 大致上共用，會依據不同情形有不同的細節處理。"= 0" : pure virtual function

## dumpvisitor.hpp/.cpp

讓程式走訪每一個node，並呼叫node的printNode();

## 各node.hpp/cpp

定義各個node要做的事，並用include xxnode.hpp的方式讓多個node可以連接已形成tree的結構。accept函式不僅要visit自己，也要visit自己接下去的node

## Problems you met and solutions

一開始真的完全不知道怎麼下手，幸好有助教的直播救援。照著祝叫做後才有了模糊的方向。一直出現segment error，等弄清parser的執行順序、pointer接好、scanner的token和parser型態確認好才解決。剛開始也很納悶為什麼node有接通卻沒print出來，後來才想到用node的accept去連接各個visit，一開始也有卡在output format上，後來定一個level在ast讓大家都有level來決定內外層的output format

## Summary

學習了Visitor Pattern的實作方法，更認識AST，更清楚parser的執行順序，還有更了解parser和scanner之間的互動，要多定義attribute。有些錯誤並不是因為parser寫錯，可能是因為scanner的token和parser型態沒有對好接。大概了解Visitor Pattern的內容，visit定義如何走訪，而各node只要確立自己該做的事和彼此連接就好
