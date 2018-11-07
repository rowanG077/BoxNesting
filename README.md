# BoxNesting

Given a set of boxes where each box has a height, length and depth between 0.5m and 1m this programs finds the most efficient way to stack them together so space consumption is optimized.

# Usage
```
usage: box_nesting [options]
  basic user options:
    -h --help   show this message
    -v --version        show version

when no options are specified program waits for input of boxes on stdin in the following format:

<n>
<length of first side of first box> <length of second side of first box> <length of third side of first box>
<length of first side of second box> <length of second side of second box> <length of third side of second box>
...
<length of first side of nth box> <length of second side of nth box> <length of third side of nth box>

where n is positive integer and the lengths are decimal numbers between 0.5 and 1

Example:
4
0.9 0.9 0.9
0.8 0.8 0.8
0.7 0.7 0.7
0.6 0.6 0.6

once specifications are given program will calculate the most efficient way to stack those boxes and write the amount of visible boxes to stdout as a single number
```

# Compilation

