import re

_cpp_format_regex = re.compile(' *\{[A-Z_]+\}')
def cpp_format(string, **kwargs):
   '''C++ friendly string formatting.
   Works like the str format method, but it 
   requires keywords to be ALL_CAPS. 
   It also takes care of applying the 
   correct indentation
   '''
   keys = set(_cpp_format_regex.findall(string))
   ret = string
   for key in keys:
      offset = '\n'+' '*key.count(' ')
      arg    = key.strip()[1:-1]
      if arg not in kwargs:
         raise ValueError(
            '%s not present in the'
            ' formatting arguments' % arg
            )
      to_sub = kwargs[arg].replace('\n', offset)
      ret = ret.replace(key.strip(), to_sub)
   return ret

