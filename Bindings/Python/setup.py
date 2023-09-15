import sys
from setuptools import setup
from pathlib import Path
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

# Read contents from the README
this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text()

if __name__ == "__main__":
    setup(
        author="Brandon M. Petty",
        author_email="brandonpetty1981@gmail.com",
        name="doxapy",
        description="An image binarization library focussing on local adaptive thresholding",
        long_description=long_description,
        long_description_content_type="text/markdown",
        version="0.9.3",
        url="https://github.com/brandonmpetty/doxa",
        license="CC0-1.0",
        ext_modules=ext_modules
    )
