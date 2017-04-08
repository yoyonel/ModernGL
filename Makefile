ifeq ($(OS), Windows_NT)
	PYTHON = python
else
	PYTHON = python3
endif

all:
	$(PYTHON) setup.py install

docs:
	cd docs && $(MAKE)

wheel:
	$(PYTHON) setup.py bdist_wheel

test:
	$(PYTHON) -m pytest

.PHONY: all docs wheel test
