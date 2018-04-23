#!/usr/bin/env python3

from setuptools import setup

setup(name='gst-make',
      version='0.0.2',
      description='Set of tools for building gstreamer plugins',
      url='https://github.com/ast/gst-make',
      author='Albin Stigo',
      author_email='albin.stigo@gmail.com',
      license='LGPL',
      packages=['gst_make'],
      scripts=['bin/gst-make'],
      zip_safe=False)
