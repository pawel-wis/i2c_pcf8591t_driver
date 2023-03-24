# PCF8591T Driver
This is a simple driver for PCF8591T AC/DC conventer. The usage of this device is minimalized to AIN1 for now. You can easly extend it for another pins but if you need only one analog you can use this module. After initialization the proc file is created in a /proc/pcf8591t location. The driver sends one byte response to i/o read function.

Please notice that value returned from I2C request has unsigned char type (0-255). So console tools for printing a file like cat or tail can return weird symbols. Real number value can be revelead by functions like python's ord().

## Build
Use make to compile the module.
``` bash
make build
```

## Installation
It is possible to build and insert module to kernel runtime using make. This command has a insmod under the pillow so sudo is propably needed to execute.
``` bash
make
# or
make install
```

## Removing
Make will remove all object files and also remove module from kernel runtime. Also sudo is needed propably.
``` bash
make uninstall
```

## Cleaning
Just for clean objects files.
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
