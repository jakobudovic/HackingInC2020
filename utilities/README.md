# Utilities for hacking

* `getenvaddr` gets the address of an environment variable in the context of an executable
* `getenvaddr-bytes` does the same, but prints the address in little-endian order.
* `reverseaddr` reverses an address supplied as first argument

## Compiling

```
make
```

## Installing

By default it will install to ``/usr/local``, but you may choose to install to somewhere else by setting ``PREFIX``

```sh
# will need root
make install

# alternatively, for example in /home/user/.local/bin (no root needed)
make install PREFIX=/home/user/.local
```
