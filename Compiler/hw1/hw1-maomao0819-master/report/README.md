# 作業1 報告

學生 : 黃秉茂
學號 : 0616098
Ability of the scanner:
	all simple tests are passed, so I guess basic abilities the homework needed are okay.

Finished part:
	Delimiters : use defined tokenChar(t).
	Arithmetic, Relational, and Logical Operators : use defined tokenChar(t) and token(t).
	Keywords : use token(t), commen format is token(KW...). 
	Identifiers : define digit and letter first, and then composit them. At the end, use tokenString(t, s).
	Integer Constants : 
		decimal : digits and first number can't be 0.
		octal : digits and first number must be 0.
	Floating-Point Constants : {dec_int}{dot}([0]|{digits}*[1-9]). use defined tokenFloat(t, f) which is like tokenString(t, s).
	Scientific Notations : ({float_num}|{int})[eE]{dec_int}. use defined tokenScientific(t, s) which is like tokenString(t, s).
	String Constants : [/"][any_char][/"]. when the string matches, use for-loop to record the char we need then output.
	Tokens That Will Be Discarded:
		Whitespace : LIST only.
		Comments:
			"//..." : LIST only.
			"/* ... */" : switch state to <comment> until "*/". 
				<comment> : LIST except "\n", "\n" do the same thing with original state.
	Pseudocomments : When the string matches, assign the related variable 0 or 1.

Problems you met and solutions:
	一開始有點難理解程式，就寫了個輸入檔測試
	octal_int很難用int的型態輸出(前面的0會消失)，最後乾脆用%s
	float_num很難用float的型態輸出(後面會多很多0)，最後乾脆用%s
	string一直不知道該如何處理，直到確認yytext的型態才想到用for-loop配合pointer處理
	"/* ... */"有點難定義它的RE，所以才用到BEGIN(狀態轉換)
	
Summary:
	能夠比較理解scanner的實作還有lex的語法，應用之前學的正規語言定義token的樣子，以及一些i/o處理
