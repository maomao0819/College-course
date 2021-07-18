# 作業 5 報告

> 學生：黃秉茂
>
> 學號：0616098

## 作業 5 心得

### codegen.hpp/.cpp

應該要先建一個visitor，在visit的過程中對於該node產生相對應的組語，以及線將資料放進指定的站存器中，而產生組語時必須依照symbol table的資訊，像是variable name等。因為要輸出到檔案裡，需要include fstream，配合fstream將輸出寫入檔案而不是stdout

### SemanticAnalyzer.hpp/cpp

同hw4，依據情況對symbol table做操作，隨著Visitor Pattern將子node慢慢push進symbol table，之後再從子節點往parent node pop 出 symbol table並做Semantic check，並且做出相對應的輸出給stderr 或 strout

### Visitor Pattern

程式先建好node之後，dumpvisit會決定visit的順序，而每個node又會定義自己的子節點的accept，決定該怎麼visit子節點。也就是先寫好程式建好AST後，才慢慢以pre-order的方式visit每個node，而每個node也以pre-order的方式visit每個sub-node

### scanner.l
	
幾乎不用動，負責將檔案的text轉換成token

### parser.y

決定何時要有甚麼動作，不論是何時要宣告、要把什麼資料丟進物件等，還有把一些IO資訊做修改，然後要依據輸入決定輸入檔和輸出檔，所以要把main中./parser的地方當成模板改成./compiler，並且要抓取輸出位置

### ast.hpp/.cpp

把所有node都會用到的東西寫在裡面

### visitor.hpp

include所有node.hpp，然後先宣告好每個node的visit函式，用virtual。

### dumpvisitor.hpp/.cpp

讓程式走訪每一個node，並呼叫node的print();

### 各node.hpp/cpp

定義各個node要做的事，並用include xxnode.hpp的方式讓多個node可以連接已形成tree的結構。accept函式不僅要visit自己，也要visit自己接下去的node

### Problems you met and solutions

大概知道應該要怎麼寫，但是實作卻沒有一個方向，第一步都走不出去。後來不斷研究助教的code終於邁出第一步，但後來還是因為不太了解symbol table在code中的運作方式而找不出想要的資料，因此而卻步

### Summary

更認識AST，更清楚parser的執行順序以及負責做的事情。這次的作業主要就是codegen要再visit一次，在visit的過程中對於該node產生相對應的組語，以及線將資料放進指定的站存器中，而產生組語時必須依照symbol table的資訊，然後透過parser知道輸入及輸出檔位置，將要輸出的資料寫入輸出檔。但我的實作方式是直接在SemanticAnalyzer動手，還有個結論是實作遠比理論想像的難

## 整學期編譯器作業心得

我覺得編譯器其實是一門好課，可以讓我們在打code的時候能做一些優化，減少compiler跟底層機器的負擔。這門課讓我了解compiler的運作原理，不僅說明了正規語言的實際運用，也能讓我們更知曉程式是如何從高階語言轉換成低階語言或是組語的。
我認為hw1、hw2都還算是輕鬆，上網google很快就抓到方向了，hw1的code原本就有意點模板了，而且上面都幫你define好function了，真的很多是直接套用和小小的修改就完成了。而hw2就是只要了解正規語言還有parser的基本語法就能完成。hw3的難度和前兩次比難了不少，雖然很感謝助教有拍影片說明方向，並起了個小頭，但我剛開始還是沒甚麼方向。後來還是問了一些會寫的人才比較了解’$’ 和parser比較深入的運作方式，而且還要處利物件和link-list或使用vector，已經更偏向是打code用一些想法去解決問題，不過只要更了解大致的方向後並不會到太難，只是有點麻煩。hw4是我覺得最難的作業，因為不僅要建symbol table、push-pop、處理錯誤、還要先了解助教寫的hw3及Visitor Pattern的部分，因為hw3的部分跟自己寫的差很多所以慌了，而且握又不太擅長多個城市的連結，所以一直不能完全理解助教給的code和抓不到hw4實作的方向，所以我認為hw4是最難的。而hw5我認為比hw4簡單，應該不會和hw3的難度差太多，但因為hw4我沒有寫出來，所以symbol table的使用就變得很困難，也因此明明感覺不難的東西卻做不太出來。
