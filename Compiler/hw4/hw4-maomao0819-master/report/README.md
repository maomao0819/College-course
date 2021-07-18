# 作業 4 報告

**<pre>學生 : 黃秉茂 	學號 : 0616098</pre>**
---
## SemanticAnalyzer.hpp/cpp

依據情況對symbol table做操作，隨著Visitor Pattern將子node慢慢push進symbol table，之後再從子節點往parent node pop 出 symbol table並做Semantic check，並且做出相對應的輸出給stderr

## Visitor Pattern

程式先建好node之後，dumpvisit會決定visit的順序，而每個node又會定義自己的子節點的accept，決定該怎麼visit子節點。也就是先寫好程式建好AST後，才慢慢以pre-order的方式visit每個node，而每個node也以pre-order的方式visit每個sub-node

## scanner.l
	
幾乎沒有動，要新增&D+以啟動 symbol table dumping 跟 &D- 關閉 symbol table dumping，還有把一些IO資訊做修改

## parser.y

要決定何時要有甚麼動作，不論是何時要宣告、要把什麼資料丟進物件等，還會用到很多"$"，把grammer的各處靠著pointer連接起來，要新增&D+以啟動 symbol table dumping 跟 &D- 關閉 symbol table dumping，還有把一些IO資訊做修改

## ast.hpp/.cpp

把所有node都會用到的東西寫在裡面

## visitor.hpp

include所有node.hpp，然後先宣告好每個node的visit函式，用virtual。

## dumpvisitor.hpp/.cpp

讓程式走訪每一個node，並呼叫node的print();

## 各node.hpp/cpp

定義各個node要做的事，並用include xxnode.hpp的方式讓多個node可以連接已形成tree的結構。accept函式不僅要visit自己，也要visit自己接下去的node

## Problems you met and solutions

還時沒有寫code的方向，雖然大概知道原理但實作卻是連第一步都走不出去
問題尚未解決

## Summary

學習了Visitor Pattern的實作方法，更認識AST，更清楚parser的執行順序，還有更了解attribute。有些錯誤並不是因為parser寫錯，可能是因為scanner的token和parser型態沒有對好接。更加了解Visitor Pattern的內容，visit定義如何走訪，而各node要確立自己該做的事和彼此連接就好，還有實作遠比理論想像的難
