import os
from distutils.core import setup, Extension
#hardcoded directory, need to be updated
dirs = "/tmp/omi-latest" 

setup(name='PMI_Instance',version = '1.0', ext_modules = [Extension('mi.PMI_Instance',sources=['PMI_Instance.c'],extra_compile_args=['-O0'],runtime_library_dirs=[dirs+'/output/lib/'],
		library_dirs=[dirs+'/output/lib/'],
		libraries=['mi'],
		include_dirs=[dirs+'/output/include'])])

setup(name='PMI_Class',version = '1.0', ext_modules = [Extension('mi.PMI_Class',sources=['PMI_Class.c'],extra_compile_args=['-O0'],runtime_library_dirs=[dirs+'/output/lib/'],
		library_dirs=[dirs+'/output/lib/'],
		libraries=['mi'],
		include_dirs=[dirs+'/output/include'])])


setup(name='PMI_Session',version = '1.0', ext_modules = [Extension('mi.PMI_Session',sources=['PMI_Session.c'],extra_compile_args=['-O0'],runtime_library_dirs=[dirs+'/output/lib/'],
		library_dirs=[dirs+'/output/lib/'],
		libraries=['mi'],
		include_dirs=[dirs+'/output/include'])])


setup(name='mi', version='1.0',
	ext_modules=[Extension('mi', 
		sources=['PythonBinding.c'],
		extra_compile_args=['-O0'],
	 	runtime_library_dirs=[dirs+'/output/lib/'],
		library_dirs=[dirs+'/output/lib/'],
		libraries=['mi'],
		include_dirs=[dirs+'/output/include']
		)])



