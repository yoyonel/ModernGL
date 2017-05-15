'''
    ModernGL Errors
'''

# from ModernGL import ModernGL as _mgl
import importlib; _mgl = importlib.import_module('ModernGL', 'ModernGL')

# pylint: disable=using-constant-test

if False:
    _mgl.Error = Exception


Error = _mgl.Error
