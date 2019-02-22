import os
import sys
import importlib

old_path = sys.path.copy()
sys.path.insert(0, os.path.normpath(os.path.abspath(os.path.join(__file__, '../..'))))
if 'window' in sys.modules:
    del sys.modules['window']
globals().update(importlib.import_module('window').__dict__)
sys.path = old_path
