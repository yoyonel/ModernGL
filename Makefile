all:
	python setup.py install
#	cd docs && make

wheel:
	python setup.py bdist_wheel

Run:
	python -m pytest
