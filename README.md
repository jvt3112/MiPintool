# MiPintool
This repository contains an Intel Pintool that is used to analyse float addition instructions in the x86 architecture.

How to build?
First download Intel Pin.
# Download the Repository
git clone https://github.com/jvt3112/MiPintool.git

# Copy the pintools folder inside Pin's tools folder
$PIN_HOME is set to the root directory of Intel Pin   
` cp -r MyPintools/pintools/ $(PIN_HOME)/source/tools/ `

# Build the pintools
` cd $(PIN_HOME)/source/tools/pintools `  
` make `

This would create a obj-intel64 or obj-ia32 folder with *.so files depending on your machine's architecture.
# How to use?
To use the pintool, use the command as follows: (this syntax is for a 64-bit system)

` $(PIN_HOME)/pin -t $(PIN_HOME)/source/tools/pintools/obj-intel64/<tool-name>.so -- <path_to_app> `  
After completion of execution, you can find the results in <tool-name>.out file in your current working directory.
