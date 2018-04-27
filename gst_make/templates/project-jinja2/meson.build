project('{{r.gst_project_replace}}', 'c',
  version : '{{version}}',
  meson_version : '>= 0.36.0',
  default_options : [ 'warning_level=1',
                      'buildtype=debugoptimized' ])

gst_version = meson.project_version()
# version_arr = gst_version.split('.')
# gst_version_major = version_arr[0].to_int()
# gst_version_minor = version_arr[1].to_int()
# gst_version_micro = version_arr[2].to_int()
#  if version_arr.length() == 4
#   gst_version_nano = version_arr[3].to_int()
# else
#   gst_version_nano = 0
# endif

have_cxx = add_languages('cpp', required : false)

glib_req = '>= 2.40.0'
gst_req = '>= 1.1.0'

plugins_install_dir = '@0@/gstreamer-1.0'.format(get_option('libdir'))

cc = meson.get_compiler('c')

# Symbol visibility
if cc.has_argument('-fvisibility=hidden')
  add_project_arguments('-fvisibility=hidden', language: 'c')
endif

# Disable strict aliasing
if cc.has_argument('-fno-strict-aliasing')
  add_project_arguments('-fno-strict-aliasing', language: 'c')
endif

cdata = configuration_data()

check_headers = [
  ['HAVE_DLFCN_H', 'dlfcn.h'],
  ['HAVE_FCNTL_H', 'fcntl.h'],
  ['HAVE_INTTYPES_H', 'inttypes.h'],
  ['HAVE_MEMORY_H', 'memory.h'],
#  ['HAVE_PROCESS_H', 'process.h'],
  ['HAVE_STDINT_H', 'stdint.h'],
  ['HAVE_STDLIB_H', 'stdlib.h'],
  ['HAVE_STRINGS_H', 'strings.h'],
  ['HAVE_STRING_H', 'string.h'],
  ['HAVE_SYS_IOCTL_H', 'sys/ioctl.h'],
  ['HAVE_SYS_PARAM_H', 'sys/param.h'],
  ['HAVE_SYS_SOCKET_H', 'sys/socket.h'],
  ['HAVE_SYS_STAT_H', 'sys/stat.h'],
  ['HAVE_SYS_TIME_H', 'sys/time.h'],
  ['HAVE_SYS_TYPES_H', 'sys/types.h'],
  ['HAVE_UNISTD_H', 'unistd.h'],
]

foreach h : check_headers
  if cc.has_header(h.get(1))
    cdata.set(h.get(0), 1)
  endif
endforeach

check_functions = [
['HAVE_ASINH', 'asinh', '#include<math.h>'],
['HAVE_CLOCK_GETTIME', 'clock_gettime', '#include<time.h>'],
['HAVE_COSH', 'cosh', '#include<math.h>'],
# check token HAVE_CPU_ALPHA
# check token HAVE_CPU_ARM
# check token HAVE_CPU_CRIS
# check token HAVE_CPU_CRISV32
# check token HAVE_CPU_HPPA
# check token HAVE_CPU_I386
# check token HAVE_CPU_IA64
# check token HAVE_CPU_M68K
# check token HAVE_CPU_MIPS
# check token HAVE_CPU_PPC
# check token HAVE_CPU_PPC64
# check token HAVE_CPU_S390
# check token HAVE_CPU_SPARC
# check token HAVE_CPU_X86_64
# ['HAVE_DCGETTEXT', 'dcgettext', '#include<libintl.h>'],
# check token HAVE_DIRECTSOUND
# check token HAVE_EXPERIMENTAL
# check token HAVE_EXTERNAL
# check token HAVE_FPCLASS
# check token HAVE_GCC_ASM
['HAVE_GETPAGESIZE', 'getpagesize', '#include<unistd.h>'],
# check token HAVE_GETTEXT
# check token HAVE_GST_V4L2
# check token HAVE_IOS
['HAVE_ISINF', 'isinf', '#include<math.h>'],
# check token HAVE_LIBV4L2
['HAVE_MMAP', 'mmap', '#include<sys/mman.h>'],
# ['HAVE_MMAP64', 'mmap64', '#include<sys/mman.h>'],
# check token HAVE_OSX_AUDIO
# check token HAVE_OSX_VIDEO
# check token HAVE_RDTSC
['HAVE_SINH', 'sinh', '#include<math.h>'],
# check token HAVE_WAVEFORM
]

libm = cc.find_library('m', required : false)

foreach f : check_functions
  if cc.has_function(f.get(1), prefix : f.get(2), dependencies : libm)
    cdata.set(f.get(0), 1)
  endif
endforeach

cdata.set('SIZEOF_CHAR', cc.sizeof('char'))
cdata.set('SIZEOF_INT', cc.sizeof('int'))
cdata.set('SIZEOF_LONG', cc.sizeof('long'))
cdata.set('SIZEOF_SHORT', cc.sizeof('short'))
cdata.set('SIZEOF_VOIDP', cc.sizeof('void*'))
cdata.set('SIZEOF_OFF_T', cc.sizeof('off_t'))

# Here be fixmes.
# FIXME: check if this is correct
cdata.set('HAVE_CPU_X86_64', host_machine.cpu() == 'amd64')
cdata.set('HAVE_GCC_ASM', cc.get_id() != 'msvc')
cdata.set('VERSION', '"@0@"'.format(gst_version))
cdata.set('PACKAGE_VERSION', '"@0@"'.format(gst_version))
cdata.set('GST_LICENSE', '"LGPL"')
cdata.set('PACKAGE', '"{{r.gst_project_replace}}"')
cdata.set('GETTEXT_PACKAGE', '"{{r.gst_project_replace}}"')

warning_flags = [
  '-Wmissing-declarations',
  '-Wredundant-decls',
  '-Wwrite-strings',
  '-Winit-self',
  '-Wmissing-include-dirs',
  '-Wno-multichar',
  '-Wvla',
  '-Wpointer-arith',
]

warning_c_flags = [
  '-Wmissing-prototypes',
  '-Wdeclaration-after-statement',
  '-Wold-style-definition',
  '-Waggregate-return',
]

if have_cxx
  cxx = meson.get_compiler('cpp')
endif

foreach extra_arg : warning_flags
  if cc.has_argument (extra_arg)
    add_project_arguments([extra_arg], language: 'c')
  endif
  if have_cxx and cxx.has_argument (extra_arg)
    add_project_arguments([extra_arg], language: 'cpp')
  endif
endforeach

foreach extra_arg : warning_c_flags
  if cc.has_argument (extra_arg)
    add_project_arguments([extra_arg], language: 'c')
  endif
endforeach

# Mandatory GST deps
gst_dep = dependency('gstreamer-1.0', version : gst_req,
  fallback : ['gstreamer', 'gst_dep'])
gstbase_dep = dependency('gstreamer-base-1.0', version : gst_req,
  fallback : ['gstreamer', 'gst_base_dep'])
gstnet_dep = dependency('gstreamer-net-1.0', version : gst_req,
  fallback : ['gstreamer', 'gst_net_dep'])
if host_machine.system() != 'windows'
  gstcheck_dep = dependency('gstreamer-check-1.0', version : gst_req,
    fallback : ['gstreamer', 'gst_check_dep'])
endif

# gstpbutils_dep = dependency('gstreamer-pbutils-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'pbutils_dep'])
# gstallocators_dep = dependency('gstreamer-allocators-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'allocators_dep'])
# gstapp_dep = dependency('gstreamer-app-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'app_dep'])
# gstaudio_dep = dependency('gstreamer-audio-1.0', version : gst_req,
#      fallback : ['gst-plugins-base', 'audio_dep'])
# gstfft_dep = dependency('gstreamer-fft-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'fft_dep'])
# gstriff_dep = dependency('gstreamer-riff-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'riff_dep'])
# gstrtp_dep = dependency('gstreamer-rtp-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'rtp_dep'])
# gstrtsp_dep = dependency('gstreamer-rtsp-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'rtsp_dep'])
# gstsdp_dep = dependency('gstreamer-sdp-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'sdp_dep'])
# gsttag_dep = dependency('gstreamer-tag-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'tag_dep'])
# gstvideo_dep = dependency('gstreamer-video-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'video_dep'])

# # GStreamer OpenGL
# gstgl_dep = dependency('gstreamer-gl-1.0', version : gst_req,
#     fallback : ['gst-plugins-base', 'gstgl_dep'], required: false)

glib_deps = [dependency('glib-2.0', version : glib_req, fallback: ['glib', 'libglib_dep']),
             dependency('gobject-2.0', fallback: ['glib', 'libgobject_dep'])]

gst_test_args = ['-DHAVE_CONFIG_H']
configinc = include_directories('.')
libsinc = include_directories('gst-libs')

subdir('gst')
subdir('tests')

configure_file(output : 'config.h', configuration : cdata)
