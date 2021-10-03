import sys
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

if sys.platform == "win32":
    cflags = ["/std:c++17", "/permissive-"]
else:
    cflags = ["-std=c++17"]

ext_modules = [
    Pybind11Extension("doxapy",
        ["DoxaPy.cpp"],
        include_dirs=["Doxa/"],
        extra_compile_args=cflags
    ),
]

if __name__ == "__main__":
    setup(
        author="Brandon M. Petty",
        name="doxapy",
        version="1.0",
        ext_modules=ext_modules
    )
