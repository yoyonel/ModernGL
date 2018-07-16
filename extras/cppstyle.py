import glob
import re
import subprocess

subprocess.call(['AStyle', '--recursive', '--suffix=none', '--indent-after-parens', '--indent-continuation=1', '--indent=tab', '--indent=force-tab=4', '--indent-switches', '--pad-oper', '--pad-comma', '--pad-header', '--add-braces', '--align-reference=middle', '--align-pointer=middle', 'src\\*'])

for fname in glob.glob('src/*'):
    with open(fname, 'r') as f:
        code = f.read()

    def reindent(match):
        lines = match.group(0).split('\n')
        res = [lines[0]]
        for x in lines[1 : -1]:
            res.append(match.group(1) + '\t' + x.lstrip())
        res.append(match.group(1) + lines[-1].lstrip())
        return '\n'.join(res)

    code = re.sub(r'^(\t+)[^\n]+=[^\n]+\(\n[^;]+[^\n]+$', reindent, code, flags=re.M)

    with open(fname, 'w') as f:
        f.write(code)
