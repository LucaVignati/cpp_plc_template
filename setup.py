import setuptools
from pybind11.setup_helpers import Pybind11Extension, build_ext

bindings = [
    Pybind11Extension("cpp_plc_template",
                      ["python-bindings/python_bindings.cpp"])
]

with open("README.md", "r") as fh:
    long_description = fh.read()

exec(open("__version__.py").read())

setuptools.setup(name='cpp-plc-template',
                 version=__version__,
                 author='Luca Vignati',
                 author_email='luca.vignati@vignati.net',
                 description="Template for writing C++ PLC algorithms \
                              that can be used in Python projects",
                 long_description=long_description,
                 long_description_content_type="text/markdown",
                 url="",
                 packages=setuptools.find_packages(),
                 classifiers=[
                     "Programming Language :: Python :: 3",
                     "Programming Language :: C++",
                     # Add License
                 ],
                 install_requires=[
                    'pybind11',
                 ],
                 python_requires='>=3.7',
                 ext_modules=bindings,
                 cmdclass={"build_ext": build_ext}
                 )
