import argparse
from importlib import import_module
import sys


from .base import Example, BaseWindow


def run_example(example_cls: Example, args=None):
    """Run an example entering a blocking main loop"""
    values = parse_args(args)
    window_cls = get_window_cls(values.window)
    window = window_cls(
        title=example_cls.title,
        size=example_cls.window_size,
        gl_version=example_cls.gl_version,
        aspect_ratio=example_cls.aspect_ratio,
        **vars(values)
    )
    window.example = example_cls(ctx=window.ctx, wnd=window)

    while not window.is_closing:
        window.render()
        window.swap_buffers()

    window.destroy()


def get_window_cls(window) -> BaseWindow:
    """Attept to obtain the configured window class"""
    return import_string('window.{}.window.Window'.format(window))


def parse_args(args=None):
    """Parse arguments from sys.argv"""
    parser = argparse.ArgumentParser()
    parser.add_argument("--window", default="glfw", help="Name for the window module to use")
    return parser.parse_args(args or sys.argv[1:])


def find_window_classes():
    """Find existing window classes"""
    pass


def import_string(dotted_path):
    """
    Import a dotted module path and return the attribute/class designated by the
    last name in the path. Raise ImportError if the import failed.
    :param dotted_path: The path to attempt importing
    :return: The object
    """
    try:
        module_path, class_name = dotted_path.rsplit('.', 1)
    except ValueError as err:
        raise ImportError("%s doesn't look like a module path" % dotted_path) from err

    module = import_module(module_path)

    try:
        return getattr(module, class_name)
    except AttributeError as err:
        raise ImportError('Module "%s" does not define a "%s" attribute/class' % (
            module_path, class_name)) from err
