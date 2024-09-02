from setuptools import setup,Extension

from Cython.Build import cythonize

extension = Extension(
    name="pyDate",
    sources=["wrappedDate.pyx","date.cpp"],
    language="c++"
)


setup(name="date",
    ext_modules=cythonize(extension))
