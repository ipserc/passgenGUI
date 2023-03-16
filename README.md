# passgen (GUI)
Application for generating customized passwords with GUI based on GTK

passgen allows you to generate passwords according to certain rules that are, a length, a set of characters and the number of each one.

The available character sets are uppercase letters, lowercase letters, digits 0 through 9, and a set of symbols. Different games can be selected, but at least one must be active.

You can indicate the minimum number of each type of characters that you want to use. For symbols this number is exact.

passgen has a rules checker that informs if the rules that have been defined are apt to generate passwords.

passgen can be executed in GUI mode and CCI also. It admits parameters to show different behaviour
	
  ## Usage 
  passgen [OPTION]... 
	
  ## Description
  
  passgen generates passwords of length given by the user.
  
  The passwords will follow some rules based in sets of characters.
	
  The sets of characters are Upper Case, Lower Case, Numbers and Symbols.
	
  The rules induces to use at least the numbre of characters given for
	Upper Case, Lower Case, Numbers. For Symbols the number of characters is
	exact as the number given.
	
  At least ONE set of characters must be active.

  ## Options
  
	Do not use any option to display the graphical interface.
		-g, --nogui	no GUI, Command Line Interface mode.
		-h, --help	shows this help.
		-c, --config	dumps the configuration on the screen.
		-V, --version	prints passgen version.

