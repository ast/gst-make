# add plugin specific dependencies here, example:
# liquid_dep = cc.find_library('liquid', required : true)

{{r.gstreplace}}_sources = ['{{r.gstreplace}}.c']

{{r.gstreplace}} = library('{{r.gstreplace}}',
  {{r.gstreplace}}_sources,
  c_args : gst_test_args,
  include_directories : [configinc, libsinc],
  dependencies : [gst_dep, gstbase_dep],
  install : true,
  install_dir : plugins_install_dir,
)
