from unittest import TestCase
import moderngl


class ContextTests(TestCase):

    def test_create_destroy(self):
        """Create and destroy a context"""
        for _ in range(25):
            ctx = moderngl.create_context(standalone=True)
            ctx.release()

    def test_context_switch(self):
        """Ensure context switching is working"""
        ctx1 = moderngl.create_context(standalone=True)
        ctx2 = moderngl.create_context(standalone=True)

        with ctx1 as ctx:
            buffer1 = ctx.buffer(reserve=1024)
        
        with ctx2 as ctx:
            buffer2 = ctx.buffer(reserve=1024)

        self.assertEqual(buffer1.glo, buffer2.glo)
        ctx1.release()
        ctx2.release()

    def test_exit(self):
        """Ensure the previous context was activated on exit"""
        ctx1 = moderngl.create_context(standalone=True)
        ctx2 = moderngl.create_context(standalone=True)

        with ctx1 as ctx:
            ctx.buffer(reserve=1024)

        # Will error out if no context is active "moderngl.error.Error: cannot create buffer"
        ctx1.buffer(reserve=1024)

        ctx1.release()
        ctx2.release()

    def test_share(self):
        self.skipTest('Context sharing not supported on darwin')
