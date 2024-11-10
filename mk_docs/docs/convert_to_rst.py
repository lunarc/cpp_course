#!/bin/env python
# -*- coding: utf-8 -*-

import os

def convert_to_rst():
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file.endswith('.md'):
                md_file = os.path.join(root, file)
                rst_file = md_file.replace('.md', '.rst')
                print('Converting {0} to {1}'.format(md_file, rst_file))
                os.system('pandoc -s {0} -o {1}'.format(md_file, rst_file))

if __name__ == '__main__':
    convert_to_rst()