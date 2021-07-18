
%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: 1
% Problem number: 5
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 4/18.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Write down your answer in the file, m01_5.m. 
%Change the file name to m01_5_yourID.m

%Assume that all the variables are defined properly.  
%Answer the questions in words. 
%Do not write down any formulas or equations. 
%Do not simply write down the values of the variables. 


What is the purpose of each of the following code fragment?

1) m(:, 2)
Answer: It returns an entire 2's column vector in matrix m.

2) find( z == 1 | z > 6)
Answer: if no value in z statisfy the condition "z == or z > 6", 
        returns an empty double vector
        else if there is at least a value in z statisfy the condition 
        "z == or z > 6", returns the index in z which statisfy the condition.

3) a( z < 0) = 11
Answer: keep the index that value in vector z that smaller than 0 and 
        change the value in a with that index to 11.

4) 10:2:10
Answer: a scalar 10.

5) max(m(1,:))
Answer: It returns max value in first row in matrix m.