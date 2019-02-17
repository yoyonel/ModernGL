import argparse
import time
import sys
from importlib import import_module
from pathlib import Path

from .base import Example, BaseWindow


def run_example(example_cls: Example, args=None):
    """
    Run an example entering a blocking main loop

    Args:
        example_cls: The exmaple class to render
        args: Override sys.args
    """
    values = parse_args(args)
    window_cls = get_window_cls(values.window)

    window = window_cls(
        title=example_cls.title,
        size=example_cls.window_size,
        fullscreen=values.fullscreen,
        resizable=example_cls.resizable,
        gl_version=example_cls.gl_version,
        aspect_ratio=example_cls.aspect_ratio,
    )

    window.example = example_cls(ctx=window.ctx, wnd=window)

    start_time = time.time()
    current_time = start_time
    prev_time = start_time
    frame_time = 0

    while not window.is_closing:
        current_time, prev_time = time.time(), current_time
        frame_time = max(current_time - prev_time, 1 / 1000)

        window.render(current_time - start_time, frame_time)
        window.swap_buffers()

    duration = time.time() - start_time
    window.destroy()
    print("Duration: {0:.2f}s @ {1:.2f} FPS".format(duration, window.frames / duration))


def get_window_cls(window: str) -> BaseWindow:
    """Attept to obtain the configured window class"""
    return import_string('window.{}.window.Window'.format(window))


def parse_args(args=None):
    """Parse arguments from sys.argv"""
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '-w', '--window',
        default="pyqt5",
        choices=find_window_classes(),
        help='Name for the window type to use',
    )
    parser.add_argument(
        '-fs', '--fullscreen',
        action="store_true",
        help='Open the window in fullscreen mode',
    )

    return parser.parse_args(args or sys.argv[1:])


def find_window_classes():
    """Find available window packages"""
    return [
        path.parts[-1] for path in Path(__file__).parent.iterdir()
        if path.is_dir() and not path.parts[-1].startswith('__')
    ]


def import_string(dotted_path):
    """
    Import a dotted module path and return the attribute/class designated by the
    last name in the path. Raise ImportError if the import failed.
    
    Args:
        dotted_path: The path to attempt importing

    Returns:
        Imported class/attribute
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
