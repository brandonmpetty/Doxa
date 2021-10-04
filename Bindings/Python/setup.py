import sys
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

cflags = []
if sys.platform == "win32":
    cflags.append("/permissive-")
    
ext_modules = [
    Pybind11Extension("doxapy",
        ["DoxaPy.cpp"],
        include_dirs=["Doxa/"],
        cxx_std=17,
        extra_compile_args=cflags
    ),
]

if __name__ == "__main__":
    setup(
        author="Brandon M. Petty",
        name="doxapy",
        description="An image binarization library focussing on local adaptive thresholding",
        version="0.9.0",
        url="https://github.com/brandonmpetty/doxa",
        license="CC0-1.0",
        ext_modules=ext_modules
    )
