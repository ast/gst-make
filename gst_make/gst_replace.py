#!/usr/bin/env python3

class GstReplace:
	"""Helper class for naming in templates"""
	def __init__(self, prefix, name):
		# Variations of prefix and name
		self.prefix = prefix.lower()
		self.Prefix = "".join(w.title() for w in prefix.split("_"))
		self.PREFIX = prefix.upper()
		self.name   = name.lower()
		self.Name   = "".join(w.title() for w in name.split("_"))
		self.NAME   = name.upper()
		# Replace patterns
		self.prefixreplace       = self.prefix
		self.replace             = self.name.replace("_", "")
		self.GST_IS_REPLACE      = "{}_IS_{}".format(self.PREFIX, self.NAME)
		self.GST_REPLACE 	     = "{}_{}".format(self.PREFIX, self.NAME)
		self.GST_TYPE_REPLACE    = "{}_TYPE_{}".format(self.PREFIX, self.NAME)
		self.GstReplace          = "{}{}".format(self.Prefix, self.Name)
		self.gst_replace         = "{}_{}".format(self.prefix, self.name)
		self.gstreplace          = "{}{}".format(self.prefix, self.replace)
		self.gst_project_replace = "{}-{}".format(self.prefix, "-".join(self.name.split("_")))

	def printall(self):
		print(self.PREFIX)
		print(self.NAME)
		print(self.Prefix)
		print(self.Name)
		print(self.name)
		print(self.prefixreplace)
		print(self.replace)
		print(self.GST_IS_REPLACE)
		print(self.GST_REPLACE)
		print(self.GST_TYPE_REPLACE)
		print(self.GstReplace)
		print(self.gst_replace)
		print(self.gstreplace)
		print(self.gst_project_replace)
