'''
    ModernGL Errors
'''

# pylint: disable=using-constant-test

from ModernGL import ModernGL as mgl


if False:
    mgl.Error = Exception


Error = mgl.Error
