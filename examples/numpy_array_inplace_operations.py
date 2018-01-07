import ModernGL
import numpy as np


# Standalone context
ctx = ModernGL.create_standalone_context()
# Create a buffer
buf = ctx.buffer(b'\x01\x00\x00\x00' * 4)

# Call frombuffer and setflags
A = np.frombuffer(buf.mglo, dtype='i4')
A.setflags(write=True)
print(A)

# In-place operation
A += 1

print(A)

# This will call glUnmapBuffer
del A

# Result
print(buf.read())
