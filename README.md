# C++ PLC Template

This is a template for a PLC algorithm written in C++, with a Python interface.

You can use this template to create your own PLC algorithm. The template is
designed to be as simple as possible, while still providing a good starting
point for your own algorithm.

## Building

This project uses setuptools to build the Python interface. It also compiles the C++ code at the same time.

To build the project, run the following command:

```bash
cd cpp-plc-template
python -m pip install .
```

To use the PLC algorithm in Python, you can then run the following:

```python
from cpp_plc_template import BasePlcTemplate
```