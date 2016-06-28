python Clean.py
SET CUSTOM_GCC=1
SET OPATH=%PATH%
SET PATH=D:\PythonVersions\Python33-32bit;%OPATH%
call python33-32 setup.py install --record files.txt
call python33-32 setup.py bdist_wheel upload
call python33-32 setup.py bdist_egg upload
call python33-32 setup.py bdist_wininst upload
SET PATH=D:\PythonVersions\Python33-64bit;%OPATH%
call python33-64 setup.py install --record files.txt
call python33-64 setup.py bdist_wheel upload
call python33-64 setup.py bdist_egg upload
call python33-64 setup.py bdist_wininst upload
SET PATH=D:\PythonVersions\Python34-32bit;%OPATH%
call python34-32 setup.py install --record files.txt
call python34-32 setup.py bdist_wheel upload
call python34-32 setup.py bdist_egg upload
call python34-32 setup.py bdist_wininst upload
SET PATH=D:\PythonVersions\Python34-64bit;%OPATH%
call python34-64 setup.py install --record files.txt
call python34-64 setup.py bdist_wheel upload
call python34-64 setup.py bdist_egg upload
call python34-64 setup.py bdist_wininst upload
