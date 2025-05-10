import sys
from setuptools import setup
from pathlib import Path
import os
import subprocess

# Read contents from the README
this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text()

# Build the extension module using CMake
def build_cmake():
    build_dir = this_directory / "build"
    if not build_dir.exists():
        build_dir.mkdir()
    
    # Configure CMake
    subprocess.check_call([
        "cmake", 
        "-S", str(this_directory),
        "-B", str(build_dir),
        "-DCMAKE_BUILD_TYPE=Release"
    ])
    
    # Build
    subprocess.check_call([
        "cmake", 
        "--build", str(build_dir),
        "--config", "Release"
    ])
    
    # Install
    subprocess.check_call([
        "cmake", 
        "--install", str(build_dir)
    ])

# Build the extension module
build_cmake()

if __name__ == "__main__":
    setup(
        author="Brandon M. Petty",
        author_email="brandonpetty1981@gmail.com",
        name="doxapy",
        description="An image binarization library focussing on local adaptive thresholding",
        long_description=long_description,
        long_description_content_type="text/markdown",
        version="0.9.4",
        url="https://github.com/brandonmpetty/doxa",
        license="CC0-1.0"
    )
