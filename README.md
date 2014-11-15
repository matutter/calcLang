__Confer normal form?__  
```
	L --> E  
	E --> F G  
	F --> H I  
	G --> + F G  
	G --> - F G  
	G -->  
	H --> integer  
	H --> ( E )  
	I --> * H I  
	I --> / H I  
	I --> % H I  
	I -->   
```
__BNF__  
```
	lang    -->   expr  
	expr    -->   term {add-op term}        // {left associative}  
	term    -->   factor {mult-op factor}   // {left associative} repeat and reduce call stack  
	factor  -->   ( expr ) | number  
	add-op  -->   + | -  
	mult-op -->   * | / | %  
	number  -->   [0-9]  
```
	
The second grammar is the same, but looks like what I tried to describe in class.   
From: http://web.cse.ohio-state.edu/software/2231/web-sw2/extras/slides/27.Recursive-Descent-Parsing.pdf
