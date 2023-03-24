# PCF8591T Driver
This is a simple driver for PCF8591T AC/DC conventer. The usage of this device is minimalized to AIN1 for now. You can easly extend it for another pins but if you need only one analog you can use this module. After initialization the proc file is created in a /proc/pcf8591t location. The driver sends one byte response to I/O read function.

Please notice that value returned from I2C request has unsigned char type (0-255). So console tools for printing a file like cat or tail can return weird symbols. Real number value can be revelead by functions like python's ord().

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

## Build
You can also just build source code and then add module manually.
``` bash
make build
```
### What to do after build ?
Make build command generates object and kernel object files. We need to insert our module to kernel.
``` bash 
sudo insmod *.ko
```
Then we can check that our module is attached. We should see our module name after command execution.
``` bash
lsmod | grep pcf
```
Dmesg prints are additional checks. We should observe initialization print from our module.
``` bash
dmesg
```
The last thing you can do is check proc file exists.
``` bash
ls /proc | grep pcf
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
