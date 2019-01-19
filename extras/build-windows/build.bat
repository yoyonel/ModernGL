@echo off
call python35-32 setup.py bdist_wheel
call python36-32 setup.py bdist_wheel
call python37-32 setup.py bdist_wheel
call python35 setup.py bdist_wheel
call python36 setup.py bdist_wheel
call python37 setup.py bdist_wheel
