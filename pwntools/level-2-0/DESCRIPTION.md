In this level, your task is to write an assembly code snippet that meets the following condition to bypass the check. You'll then use the `asm` API from pwntools to compile the assembly code and complete the challenge. The condition for this challenge is:

```
rax = 0xdeadbeef
```

Refer to the pwntools example code below to help you complete the script (Hint: make sure to replace the NOP instruction with the specific assembly instruction you need):

```
from pwn import *

# Set architecture, os and log level
context(arch="amd64", os="linux", log_level="info")

# Load the ELF file and execute it as a new process.
challenge_path = "/challenge/pwntools-tutorials-level2.0"

p = process(challenge_path)

# Send the payload after the string "(up to 0x1000 bytes): \n" is found.
p.sendafter("Please give me your assembly in bytes", asm("NOP"))

print_lines(p)
```