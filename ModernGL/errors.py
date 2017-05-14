'''
    ModernGL Errors
'''

from ModernGL import ModernGL as _mgl

# pylint: disable=using-constant-test

if False:
    _mgl.Error = object


Error = _mgl.Error
