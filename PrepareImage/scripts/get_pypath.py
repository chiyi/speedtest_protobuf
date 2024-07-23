#!/bin/python
import sys

out = filter(lambda x: 'python' in x or '/root/lib' in x, sys.path)
out = ':'.join(out)
print(out)
