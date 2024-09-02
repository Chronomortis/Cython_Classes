from setuptools import setup,Extension

from Cython.Build import cythonize

extension = Extension(
    name="pyClock",
    sources=["wrappedClock.pyx","clockt.cpp"],
    language="c++"
)


setup(name="Clock",
    ext_modules=cythonize(extension))