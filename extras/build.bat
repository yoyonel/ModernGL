@echo off

pushd %~dp0\..

call python setup.py sdist

call python3.5-32 setup.py bdist_wheel
call python3.6-32 setup.py bdist_wheel

call python3.5 setup.py bdist_wheel
call python3.6 setup.py bdist_wheel

git archive HEAD --format=tar | ssh -i %USERPROFILE%\.ssh\id_rsa root@linux32.builder "rm -rf build && mkdir build && cd build && tar -x && python3.5 setup.py bdist_wheel && python3.6 setup.py bdist_wheel"
scp -i %USERPROFILE%\.ssh\id_rsa root@linux32.builder:build/dist/*.whl dist/

git archive HEAD --format=tar | ssh -i %USERPROFILE%\.ssh\id_rsa root@linux64.builder "rm -rf build && mkdir build && cd build && tar -x && python3.5 setup.py bdist_wheel && python3.6 setup.py bdist_wheel"
scp -i %USERPROFILE%\.ssh\id_rsa root@linux64.builder:build/dist/*.whl dist/

git archive HEAD --format=tar | ssh -i %USERPROFILE%\.ssh\id_rsa root@mac64.builder "rm -rf build && mkdir build && cd build && tar -x && /usr/local/bin/python3.4 setup.py bdist_wheel && /usr/local/bin/python3.5 setup.py bdist_wheel && /usr/local/bin/python3.6 setup.py bdist_wheel"
scp -i %USERPROFILE%\.ssh\id_rsa root@mac64.builder:build/dist/*.whl dist/

python extras\rename_linux_wheels.py

popd
