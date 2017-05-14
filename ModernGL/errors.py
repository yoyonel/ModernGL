'''
    ModernGL Errors
'''

from ModernGL import ModernGL as _mgl

# pylint: disable=using-constant-test

if False:
    _mgl.Error = Exception


Error = _mgl.Error
