python Clean.py
SET OPATH=%PATH%
rem SET PATH=D:\PythonVersions\Python33-32bit;%OPATH%
rem call python33-32 setup.py install --record files.txt
rem call python33-32 setup.py bdist_wheel upload
SET CUSTOM_GCC=1
SET PATH=D:\PythonVersions\Python33-32bit;%OPATH%
call python33-32 setup.py install --record files.txt
call python33-64 setup.py bdist_wheel upload
rem SET PATH=D:\PythonVersions\Python34-32bit;%OPATH%
rem call python34-32 setup.py install --record files.txt
rem call python34-32 setup.py bdist_wheel upload
SET PATH=D:\PythonVersions\Python34-64bit;%OPATH%
call python34-64 setup.py install --record files.txt
call python34-64 setup.py bdist_wheel upload
