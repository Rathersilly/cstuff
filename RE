Vim Args



3. The argument list				*argument-list* *arglist*

:ar[gs]			Print the argument list, with the current file in
			square brackets.

:ar[gs] [++opt] [+cmd] {arglist}			*:args_f*
			Define {arglist} as the new argument list and edit
			the first one.  This fails when changes have been made
			and Vim does not want to |abandon| the current buffer.
			Also see |++opt| and |+cmd|.

:[count]arge[dit][!] [++opt] [+cmd] {name} ..		*:arge* *:argedit*

:[count]arga[dd] {name} ..			*:arga* *:argadd* *E479*
