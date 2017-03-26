ifeq ($(OS), Windows_NT)
	PYTHON = python
else
	PYTHON = python3
endif

all:
	$(PYTHON) setup.py install

wheel:
	$(PYTHON) setup.py bdist_wheel

Run:
	$(PYTHON) -m pytest
