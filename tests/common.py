import ModernGL

_static = {
    'context': None,
}


def get_context() -> ModernGL.Context:
    ctx = _static.get('context')

    if ctx is None:
        ModernGL.mgl.set_default_context_size(100, 100)
        ctx = ModernGL.create_standalone_context()
        _static['context'] = ctx

    return ctx
