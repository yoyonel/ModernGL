import os
import sys
import importlib

old_path = sys.path.copy()
sys.path.insert(0, os.path.normpath(os.path.abspath(os.path.join(__file__, '../..'))))

if 'window' in sys.modules:
    del sys.modules['window']

import sys, moderngl.experimental; sys.modules['moderngl'] = sys.modules['moderngl.experimental']
_impl = importlib.import_module('window')

Example = _impl.Example
run_example = _impl.run_example
sys.path = old_path
