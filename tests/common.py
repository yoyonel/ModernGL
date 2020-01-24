import moderngl

_static = {}


def get_context(require=330) -> moderngl.Context:
    """Caches contexts for each gl version"""

    ctx = _static.get('context')

    if ctx is None:
        try:
            ctx = moderngl.create_context(require=require, standalone=True, size=(100, 100))
            _static['context_{}'.format(require)] = ctx
        except Exception as ex:
            print(ex)
            return None

    return ctx
 