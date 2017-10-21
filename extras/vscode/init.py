import os
import shutil

src = os.path.normpath(os.path.dirname(os.path.abspath(__file__)))
dst = os.path.normpath(os.path.join(src, '..', '..', '.vscode'))
shutil.copytree(src, dst, ignore=shutil.ignore_patterns('*.py'))
