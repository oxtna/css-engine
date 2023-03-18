# CSS_Engine

This is a CSS engine made as a univesity assingment. It handles syntacticly correct CSS but not malicious input.
It also recognizes special commands:

* `????` - beginning of command section
* `****` - end of command section
* `?` - print the number of CSS sections
* `i,S,?` - print the number of selectors in `i`-th section if it exists
* `i,A,?` - print the number of attributes in `i`-th section if it exists
* `i,S,j` - print `j`-th selector in `i`-th section if it exists
* `i,A,n` - print the value of attribute `n` in `i`-th section if it exists
* `n,A,?` - print the number of occurences of attribute `n` in all sections
* `z,S,?` - print the number of occurences of selector `z` in all sections
* `z,E,n` - print the value of attribute `n` for selector `z` if it exists
* `i,D,*` - delete `i`-th section and print `deleted` on success
* `i,D,n` - delete attribute `n` from `i`-th section and remove any empty sections, and print `deleted` on success
