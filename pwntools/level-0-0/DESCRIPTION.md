This level is a tutorial and fairly straightforward. You could just run `/challenge/pwntools-tutorials-level0.0` in the terminal and enter a specific string (which you can find by reading the `bypass_me` function), but that’s not the main goal here.

This level is designed to teach you how to use pwntools to complete the challenge. Your task is to use the `process`, `send`, `recv`, and other pwntools APIs to write an exploit script, send the right input to bypass the check, and retrieve the flag. Check out the example pwntools code below (hint: don’t forget to replace `FIXME` with the specific string mentioned earlier):

```
from pwn import *

# Set architecture, os and log level
context(arch="amd64", os="linux", log_level="info")

# Load the ELF file and execute it as a new process.
challenge_path = "/challenge/pwntools-tutorials-level0.0"
p = process(challenge_path)

payload = b'FIXME'
# Send the payload after the string "pwn me :)\n" is found.
p.sendafter("pwn me :)\n", payload)

# Receive flag from the process
flag = p.recvline()
print(f"flag is: {flag}")
```