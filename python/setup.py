#!/usr/bin/env python


from setuptools import setup, find_packages


setup(name='visp',
      version='0.1',  # TODO: Get the version directly from visp
      packages=find_packages(),

      setup_requires=['setuptools_git >= 0.3',
                      'numpy'],
      )
