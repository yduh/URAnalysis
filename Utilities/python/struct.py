'''
python dict - to class
copyed from: http://stackoverflow.com/questions/1305532/convert-python-dict-to-object 
Author: Mauro Verzetti
'''
from copy import deepcopy

class Struct:
    def __init__(self, **entries): 
        self.__dict__.update(entries)

    def clone(self, **subs):
        newd = deepcopy(self.__dict__)
        newd.update(subs)
        return struct(**newd)

    def __hash__(self):
        return self.__dict__.__repr__().__hash__()

class RecursiveStruct:
    def __init__(self, **entries):
        class_dict = {}
        for key, value in entries.iteritems():
            if isinstance(value, dict):
                class_dict[key] = RecursiveStruct(**value)
            else:
                class_dict[key] = value
        self.__dict__.update(class_dict)
