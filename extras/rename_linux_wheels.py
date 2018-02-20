import glob
import shutil

for f in glob.glob('dist/*-linux_*.whl'):
    shutil.move(f, f.replace('-linux_', '-manylinux1_'))
