from os import path
# Convenience imports
from .gst_replace import GstReplace

# def template_path():
# 	return path.join(path.dirname(__file__), "templates")

def script_path():
	return path.join(path.dirname(__file__), "scripts")
