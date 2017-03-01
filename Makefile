all:
	python setup.py install

wheel:
	python setup.py bdist_wheel

Run:
	python -m pytest
