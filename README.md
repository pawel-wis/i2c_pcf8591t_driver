# PCF8591T Driver
This is a simple sriver for PCF8591T AC/DC conventer. The uasge of this device is flatten to use only a photoresistor connected to AIN1. You can easly extend it for another pins but if you need only one analog you can use this module. After initialization the proc file is created in a /proc/pcf8591t location. The driver sends one byte response when you try to read a file.

## Installation
Use make command to build the driver. It also insert a module to kernel runtime so you propably will need sudo privigelents.
``` bash
make
```

## Removing
Make will remove all object files and also remove module from kernel runtime.
``` bash
make clean
```

## Usage example
Here is a simple reading example made in python.
``` python
with open('/proc/pcf8591t') as f:
	ain_value = ord(f.read(1))
	print(ain_value)
```

