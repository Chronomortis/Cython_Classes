from setuptools import setup,Extension

from Cython.Build import cythonize

extension = Extension(
    name="pyAccount",
    sources=["wrappedAccount.pyx","account.cpp"],
    language="c++"
)


setup(name="account",
    ext_modules=cythonize(extension))
