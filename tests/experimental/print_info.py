import json

import moderngl.next as mgl

ctx = mgl.create_context(standalone=True, debug=True)

print('Limits:', json.dumps(ctx.limits.json(), indent=2))
print('Extensions:', json.dumps(mgl.extensions(ctx), indent=2))
print('Hardware Info:', json.dumps(mgl.hwinfo(ctx), indent=2))
print('Version Code:', ctx.version_code)
