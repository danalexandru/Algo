# Algo
a bit of everything
  
  
### Making a wireless remote controller using Arduino w IR and a simple python script

I've used the following python packages: `serial` and `win32com`.  
And registered for specific buttons specific commands.  
Everytime Arduino send on serial a HEX value, python `reads it`, `parses it` and `applies the key combination` such that a specific action `like opening a tab occurs`.

