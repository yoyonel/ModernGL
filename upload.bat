call python setup.py sdist upload

call python setup.py bdist_wheel upload
call python setup.py bdist_egg upload
call python setup.py bdist_wininst upload

call python64 setup.py bdist_wheel upload
call python64 setup.py bdist_egg upload
call python64 setup.py bdist_wininst upload
