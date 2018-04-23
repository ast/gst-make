from os import path

def template_path():
	return path.join(path.dirname(__file__), "templates")

def script_path():
	return path.join(path.dirname(__file__), "scripts")
