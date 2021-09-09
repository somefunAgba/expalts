# RUN SETUP IN FOLDER BY RUNNING: 
# pip install -e . -vvv

from pathlib import Path
from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

_version_ = "1.0.0"

ext_module = Pybind11Extension(
    'expalts',
    [str(fname) for fname in Path('../src_cpp/').glob('expalts.cpp')],
    include_dirs=['../src_cpp/'],
    extra_compile_args=['/Ox']
)

# '-O3' for gcc, or /Ox for VSBuildtools

setup(
    name='expalts',
    version=_version_,
    author='OAS',
    author_email='oasomefun@futa.edu.ng',
    description='expalts, alternative natural exponential approximations',
    ext_modules=[ext_module]
)