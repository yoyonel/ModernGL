import os
import re


def inject_trace(source):
    source = re.sub(r'(\*\s*self[^\n]+{)$', r'\1{FILE * f = fopen("trace.log", "ab"); fprintf(f, "%s (%s:%d)\\n", __FUNCTION__, __FILE__, __LINE__); fclose(f);}', source, flags=re.M)
    return source


        # import re; open('_' + src, 'w').write(re.sub(r'(\*\s*self[^\n]+{)$', r'\1{FILE * f = fopen("trace.log", "ab"); fprintf(f, "%s (%s:%d)\\n", __FUNCTION__, __FILE__, __LINE__); fclose(f);}', open(src).read(), flags=re.M)); src = '_' + src
