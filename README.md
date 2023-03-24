# PCF8591T Driver
This is a simple driver for PCF8591T AC/DC conventer. The usage of this device is minimalized to AIN1 for now. You can easly extend it for another pins but if you need only one analog you can use this module. After initialization the proc file is created in a /proc/pcf8591t location. The driver sends one byte response to i/o read function.

Please notice that value returned from I2C request has unsigned char type (0-255). So console tools for printing a file like cat or tail can return weird symbols. Real number value can be revelead by functions like python's ord().

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
